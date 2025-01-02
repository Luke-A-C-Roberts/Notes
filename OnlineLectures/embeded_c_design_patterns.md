[embeded design patterns](https://www.youtube.com/watch?v=_lv5hin6eiM&list=WL&index=31)

# Design patterns

Info of design patterns is sparse for C. Often studying code bases is the only option.

High level data structures is key to understanding design patterns:
- Arrays
- Memory allocation
- Structs
- Pointers
- Unions

## ELF files

The highest level is the application. We are trying to create a **binary image** to run on our processor. The binary image is basically 4 arrays:
- The code (.text)
- The data (.data)
- The uninitialised variables (.bss)
- The interupt table (.isr_vectors)

Some of these sections is used for less important data like debug information. (remember debug info is compiled `-g`).

**ELF** - Executable, Linkable file contains this data. The program or highest form of our application. This can be loaded by a **boot loader** or the data could be **extracted** and **flashed** into a chip (like in microcontrollers).

We want to structure our program better to keep track of all the moving parts of our program.

## Bootloader

**Bootloader**: loads the main program from one of the supported locations (flash, uart, usb or network).
**Main program**: (a.k.a the RTOS or kernel) is either the only program that runs or loads other programs from data storage.
**Application**: is a program loaded or started after the main program has started.

The **firmware** is a collection of programs or applications that are either linked together into an image or combined togerther as a combination of code and data. It is similar to a program container except that it contains many different programs and often (a) filesystem(s).

On a desktop system, program entery point is found in the ELF file. Meanwhile on a microcontroller the entrypoint is fixed to the first bytes of the flash memory. To get ELF file information, the `readelf` command can be useful.

## Why C

C maps well to what is expected in the ELF file after compilation and linking. Its not enough to know the language, structure is important to help facilitate translation.

High level design patterns make the code easier to read and expand.
Some C design patterns are:
- Struct pattern
- Multilevel struct pattern (containment)
- Opaque objects (implementation hidden)
- Data abstraction using `container_of`
- Abstract interface using `container_of` and virtual methods.

## Struct Pattern

Struct pattern principles.
- Keep the data grouped together.
- All data should be stored in structs and passed as arguments.
- Struct variables are **never** declared global.
- All functions accept pointer to struct where they can find the data that they need.
- Data flow is always through the code and not outside of it.
 
In C you have design your own OOP experience. You can use a parameter `self` to a pointer of a struct as a method for example. This is much better than using bare globally accessable variables to manipulate because it minimises unintended data mutation. If there is no globally manipulated state, then functions are **reentrant** which simplifies multithreading and allows for more agressive compiler optimisation. It also simplifies testing because code can be isolated and fed mock data.

## Hierarchical Containment

Enables functionality of all instances of a type. Makes code much more readable by packaging related variables (and other structs). Multiple instance behaviour can be easily created when you use this pattern. Nested structs can even be declared inline and used for grouping things together.

```c
// example of inline struct 
struct A {
  struct B {
    int a;
    int b;
  };

  char *c;
};
```

## Opaque Objects

Enables hiding an implementation. The object structure is hidden from all other code in the project, typically heap-allocated as a pointer. The public interface only contains methods that operate on the opaque object.

```c
// example of a opaque struct in console.c
struct console {
  struct console_device dev;
  serial_port_t serial;
  struct list_head commands;
  size_t ncommands;
};

// in .c the struct is defined locally
struct console *self = malloc(sizeof(struct console));

// Then the object is registered as an interface using pointers.
console_device_init(&self->dev, fdt, fdt_node, &_console_ops);
console_device_register(&self->dev);
console_add_command(&self->dev.ops, self, "ps", "show list of processes", "", _cmd_ps);
console_add_command(&self->dev.ops, self, "md", "Dump raw memory location", "", _cmd_md);
```

## The "Container Of" Pattern

Very useful macro definition that writes gemeric code to implement algorithms. Operate on collections without caring what data they contain. Reusable lists, avl trees, hash tables and other structures.

How does it work?
- Aggregate item like a struct is embedded in an enclisomg struct.
- Pointer to item is passed around and used for organisation
- pointer to main struct is retrieved using container_of macro to get the actual data.

```c
// the definition of container_of
#define container_of(ptr, type, member) ({ \
  const typeof( ((type* )0)->member ) *__mptr = (ptr);\
  (type *)( (char *)__mptr - offsetof(type, member) );}) 
```

This macro finds the pointer to the struct or other object, given a member.

```c
// example, find the pointer of A from A.y
struct A {
  int x;
  int y;
};

int main(void) {
  struct A a = {10, 20};
  int *y_ptr = &A.y;
  A *a_ptr = container_of(y_ptr, struct A, y);
} 
```

```c
// expansion of container_of(y_ptr, A, y);
({
  const typeof( ((struct A*)0)->y) *__mptr = (y_ptr);
  (struct A*)( (char *)__mptr - offsetof(struct A, y) );
})

// the internal functions then retrieve the correct values
({
  const int *__mptr = y_ptr;         // this is the same as y_ptr but given a type
  (struct A*)( (char *)__mptr - 4 ); // this is because A.x is type int so offsets y by 4 bytes
})
```

This can be used for creating abstract interfaces.

