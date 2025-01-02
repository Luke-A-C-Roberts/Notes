The Erlang Runtime System and BEAM
===================================

Notes from [theBeamBook](https://blog.stenmans.org/theBeamBook/#CH-Compiler)
Also useful: [cheat_sheets](https://adoptingerlang.org/docs/cheat_sheets/)

# The compiler

The Erlang compiler converts Erlang (.erl) code to native code (.beam) in the Erlang compiler framework.

Framework Layers
1. Network (if running multiple Erlang nodes)
2. Hardware/ VM (Which itself runs on hardware)
3. Operating system (OS)
4. Erlang run-time system (ERTS)
5. BEAM (Virtual machine)
6. OTP (Erang libraries)
7. Elixir (Optional)
8. Application

To compile Erlang code, there are many intermediate stages that have their own file types.

`erlc` is a common command to compile `.erl` code, and `c(file_name).` can be used while in the erlang REPL, as a macro shortcut for `compile:file(file_name).`.

To generate intermediate compiler stages `compile:options().` can be used to change compilation behaviour.

Compilation Stages
1. Scanner/Tokeniser
2. Preprocessor → `.erl`
3. Parse transform → `.Pbeam` → `.pp`
4. Linter → `.P`
5. Save AST (only debug)
6. Expand → `.E`
7. Core Erlang → `.core`
8. Kernel Erlang
9. BEAM Code → `.S`
10. Native Code `.beam`

## Scanner/Tokeniser & Preprocessor

The tokeniser converts raw text into tokenised format, and then the preprocessor expands includes and evaluates macros (similar to C preprocessing).

## Parse Transformation

Parse transformations convert the tokens from the previous stage and parse them into a AST. Optionally, user-defined transformations can be applied to change the AST's structure.

## Linter

The linter generates warnings for syntactically correct but otherwise bad code.

## Save AST

At this stage the AST can be saved if compiled in debug mode. The AST is saved before any optimisation, so their may be a difference between how the program runs in debug/release modes. Custom compier optimisations **can cause problems** for this.

## Expand

Datastructures like records are converted to more fundimental constructs for further compilation and optimisation.

## Core Erlang

Core Erlang is ran on the ERTS and is purely functional, so more ideal for optimisation transformations. For example `let` and `letrec` are introduced to make scoping explicit.

## Kernel Erlang

Similar to core Erlang but all variables are given unique IDs and global scope becomes a function. At this stage pattern matching is expanded to lower level operations.

## BEAM

Conversion from previos stage to the beam code format. Most optimisation happens here.

## Native Code

BEAM code is converted to a much more compact binary representation.


# Processes

Also see: [elixir processes](https://hexdocs.pm/elixir/processes.html)

Process: isolated entity where code execution occurs.

Processes can protect the system from erros by isolating faultty code. Erlang provides a lot of services to inspect processes, and problems related to them like bottleknecks and resource overuse. To inspect all running commands, `i()` can be run in the shell.

To inspect one specific process for example one at `<0.36.0>`, in the shell run `i(0, 36, 0).`, an alias for `erlang:process_info(0, 36, 0).`.

## Breakdown of process items

`registered_name`, the given name of the process.
`current_function`, the current function being ran/ suspended on the process.
`initial call`, the first function executed when the process began.
`status`, the current process of the process, either running or waiting.
`message_queue_len`, the number of process messages currently in the process mailbox.
`messages`, list of the messages in the process mailbox.
`priority`, `reductions`, `links`, `trap_exit`, `error_handler`, `group_leader`, all process execution information.
`dictionary`, `total_heap_size`, `heap_size`, `stack_size`, `garbage_collection`, all memory usage information. The starting `heap_size` of a process is 233 for some reason.

See link for more information: [process_info](https://www.erlang.org/doc/apps/erts/erlang.html#process_info/1)

Since process information results are themselves data, this means tools can be created for inspecting processes.

## Process Memory

Their are 4 memory blocks in processes:
1. The stack: local variables, scope and process returns
2. The heap: large structures (lists, tuples etc.)
3. Message memory: stores messages from other processes
4. Process controll block (PCB): state of the entire process

Dynamically allocated: 1-3. Grows and shrinks as needed.
Statically allocated: 4. Keeps the same consistent size.

### Inspecting memory through HiPE built-in functions (BIFs)

HiPE BIFs are used to print out memory content of stacks, heaps, and the PCB. They are not part of OTP and so are **not to be relied upon** for critical services, and examine ERTS internals potentially unsafely. **Use HiPE BIFs with care!**

`hipe_bifs:show_estack(self()).` is used to show stack contents of a process. Similarly, `hipe_bifs:show_heap(spawn(fun() -> ok end)).` show the heap contents of an example process. The PCB can also be shown using `hipe_bifs:show_pcb(self()).`

### PCB fields

The PCB contains fields that show process behaviour. Processes are implemented as a C struct in the file [erl_process.h:935](https://github.com/erlang/otp/blob/a748cafdc7063d9f181ba12088db6458793ced2f/erts/emulator/beam/erl_process.h#L935).

Some important PCB fields:
1. `id`: the process ID (PID). The 4 least significant bits are a tag.: 
2. `htop`: pointer to the top of the heap.: 
3. `stop`: pointer to the top of the stack.: 
4. `heap`: pointer to the start of the heap.: 
5. `hend`: pointer to the end of the heap.: 
6. `heap_sz`: gives the size of the heap in words. (hend - heap) * 8 == heap_sz (on 64 bit): 
7. `min_heap_size `the smallest size (in words) the heap will shrink to (default is 233): 

In reality the heap and stack of a process share the same memory pool the "Heap". The Heap contains heap allocated memory, stack allocated memory, and free memory all together in one place. Heap addresses move to higher memory as they are allocated, while stack addresses move to lower memory. When the htop and stop meet due to memory usage, the garbage collector tries to free memory wherever it can. To free and reallocate memory the garbage collector allocates memory to *the space* and goes through each stack pointer to the heap, to copy the data to a new Heap. Then it copies all the stack data to the Heap and frees the old Heap. Reallocating memory like this is called "generational garbage collecation". The place where the heap and stack meet is the `high_water` pointer.

### Mailboxes

When a process sends a message to another, it coppies data from it's own heap to the mailbox of the recieving process. In old versions of Erlang this was not the case, as there was only ever one running process, and heap memory of one process was simply copied to another process's heap. When Erlang was paralellised, it was necessary to copy the data to a safe fragment of the heap in the recieving process (called m-buf or heap fragmanets). Once all data was copied, the pointer associated with the copied data is added to the message queue of it's mailbox. After, the garbage collector copies the m-buf data to the main process heap to reduce the need to reallocate the m-buf. It should be noted their is a variable number of m-buffers depending on the resources a process will need.

Syntax: to send a message from Y to X the Erlang syntax is `X ! Y`.

The mailbox contains two lists, the "seen" list and the "new" list. Only "seen" data is copied as it may be deallocated, "new" data is not yet read and so guaranteed to survive.

Copying directly to the heap of a process has seen a comeback since Erlang 19, since the mailbox method includes steps that are unnecessary, and writing to the m-heap means that memory will need to be allocated for the message data, which is expensive. Having a `main lock` means that the recieving process is a guaranteed to not accidentally do something with the message data while it is being copied. This is done through the variable `message_queue_data` which can be `on_heap` or `off_heap`, where `on_heap` means that the sending process will first check the `main_lock`, and `off_heap` means that this won't happen and the usual mailbox method is automatically used.

PCB Message fields
1. `msg.first`: ptr to first message
2. `msg.last`: ptr to last message
3. `msg.save`: ptr to saved? message
4. `msg.len`: number of messages
5. `msg_inq.first`: ptr to first message in the queue
6. `msg_inq.last`: ptr to last message in the queue
7. `msg_inq.len`: number of messages in queue
8. `mbuf`: ptr of the current m-buf
9. `mbuf_sz`: size of the m-buf

# Erlang type system

Erlang is strongly and dynamically typed. This means that a variable can store any kind of data; types are only checked at runtime and once assigned the type's data can't be coerced to a different type (like it can with `void *` in C). The dynamic typing of the language means that a variable's type is stored alongside the value, through a scheme called *tagging*.

Types in Erlang are are orginised hierarchically, so a type may have sub types existing on a level below. Types on the same level are also ordered by "value", so types can be compared for values. For example `tuple() < map()`.

## The hierarchy

Ordered first by inheritence (higher up the list is a parent type to those further down). Ordered second by value lower type value comes before higher values.

1. `any()`

2. from `any()`
  1.  `number()`
  2.  `atom()`
  3.  `reference`
  4.  `fun()`
  5.  `port()`
  6.  `pid()`
  7.  `tuple()`
  8.  `map()`
  9.  `list()`
  10. `binary()`

3. from `number()` (no particular ordering on this level)
  - `integer()` (strings are encoded as types of integer)
  - `float()`

3. from `atom()`
  - `boolean()`

3. from `list()` (no particular ordering on this level)
  - `nil()`
  - `cons()`

4. from `boolean()`
  1. `false()`
  2. `true()`
  
5. from all types
  - `none()`

## Intra-type ordering

### Numbers

Both integers and floats can be converted before comparison. This results in the peculiarity where both `(1 < 1.0)` and `(1.0 < 1)` result in `false`. The number of less precision is converted to the number of higher precision (typically `int()` → `float()`). 

### Maps (since Erlang 18)

Maps are compared in this series of steps:

1. If one map has fewer elements than the other it is smaller, `||m1|| < ||m2||`.
2. If both maps have the same number of elements then each key is compared as is.
3. If both maps are still equal, try comparing them by first converting to a higher precision.

## Tagging

Tagging determines an allocation stratergy for a group of different variable types. A tag is represented by the two least significant bits of an address.

### Immediates

Immediate comprise of exactly one word of data on the stack, either 32 or 64 bits depending on the system. Least significant bits determine a tag type. There are 12 immediate tag types, the first 4 have tag bits `xy` where `x` and `y` are bits. The second 4 are represented by `xy11` where the `1` values are constant. The last 4 are represented by `xy1011`, where `0` is also a constant.

The List of possible tags are as follows:
1.  `00`:     Header on heap, return adress on stack
2.  `01`:     List (cons)
3.  `10`:     Boxed
4.  `11`:     Immediate -> leads to all further tags
5.  `0011`:   PID
6.  `0111`:   Port
7.  `1011`:   Immediate 2 -> leads to all further tags (post small integer)
8.  `1111`:   Small integer (big integers are boxed on the heap)
9.  `001011`: Atom
10. `011011`: Catch
11. `101011`: Unused
12. `111011`: Nil

## Atoms

Atoms comprise of an index in the atom table and the atom tag. Two atom immediates can be compared by immediate representation `ord0` without needing to compare the atom names, as long as atoms don't start with the same first 4 characters.

[atoms.h:48](https://github.com/erlang/otp/blob/master/erts/emulator/beam/atom.h)

Type definition of atom struct:
```c
typedef struct atom {
    IndexSlot slot;       /* MUST BE LOCATED AT TOP OF STRUCT!!! */
    Sint16 len;           /* length of atom name (UTF-8 encoded) */
    Sint16 latin1_chars;  /* 0-255 if atom can be encoded in latin1; otherwise, -1 */
    int ord0;             /* ordinal value of first 3 bytes + 7 bits */
    union {
        byte* name;      /* name of atom, used by templates */
        Eterm bin;       /* name of atom, used when atom is in table*/
    } u;
} Atom;
```

Expanded (Not yet flattened):
```c
typedef struct atom {
    struct {
        struct {
            void *next;           // 64
            unsigned long hvalue; // 64
        } bucket;
        int index;                // 32
    } slot;
    short len;                    // 16
    short latin1_chars;           // 16
    int ord0;                     // 32
    union {
        char *name;
        Eterm *bin; // (Eterm could be a variety of different ptr types)
    } u;                          // both 64
} Atom;
// 64 + 64 + 32 + 16 + 16 + 64 = 4 * 64 (4 words) = 16 * 8 (16 bytes)
```

OPTIMISATION: Never generate atom names because the atom table is limited! Prefer dissimilar atom names.

## Boxed terms

### Lists

Lists (cons cells) are two words on the heap for a head (aka *car*) and tail (aka *cdr*).

### Strings

In erlang a string is list of integers representing characters, since OTP R14 they are Unicode strings. Prior to this Latin-1 was used. Latin-1 ⊂ Unicode.

### Other boxed terms

All other boxed terms on the heap start with a header word to specify what it is. The header tag `00` and a four bit header and an arity (in this case meaning how many words the boxed term comprises of).

List of boxed tags.
1.  0000:	ARITYVAL (Tuples)
2.  0001: BINARY_AGGREGATE                |
3.  001s:	BIGNUM with sign bit            |
4.  0100:	REF                             |
5.  0101:	FUN                             | THINGS
6.  0110:	FLONUM                          |
7.  0111: EXPORT                          |
8.  1000:	REFC_BINARY   |                 |
9.  1001:	HEAP_BINARY   | BINARIES        |
10. 1010:	SUB_BINARY    |                 |
11. 1011: UNUSED
12. 1100: EXTERNAL_PID  |                 |
13. 1101: EXTERNAL_PORT | EXTERNAL THINGS |
14. 1110: EXTERNAL_REF  |                 |
15. 1111: MAP

### Tuples

Tupples are stored with the arity and then each element in the following words.

NOTE: the empty tupple `{}` is stored as the word `0` (header tag `0`, tuple tag `0000` and arity `0`).

### Binaries

A binary is an immutable array of bytes. There are 4 types of binary: *heap*, *refc*, *sub binaries* and *match contexts*. Heap and refc binaries contain data while sub binaries and match contexts are references to data in the other two.

### Bignums

Integers that are not fittable in a single word (minus the 4 tag bits) are assigned to big ints on the heap. The header contains the number of bytes that the bigint is stored in, and then the the number itself is stored contiguously after the header.

### Refs

Refs implements a channel over a process mailbox, they are an 82-bit counter.

