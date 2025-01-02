# Hot Code Reloading in C

[how_reloading](https://www.youtube.com/watch?v=Y57ruDOwH1g)

Recomiling and stopping the program kinda sucks for rapid development.

being able to dynamically load a library is a OS functionality. for example dlls dynamically link library or shared object files (linux).

we need to create a dynamic library that is loaded into the main project. (Header and C file are needed).

```
     [ otherlib.o ]
     ^            ^
[ main.o ] -> [ plugin.so ]
```
build can be done by:
`clang -o ./build/Plugin.so -fPIC -shared ./src/Plugin.c ...`
-fPIC = posision independant code (can be anywhere in memory)

the whole project can then be built:
`clang -o ./build/main ./src/main.c -L./build/ -lplug ...`

C uses the library `dlfcn` (.h) to import shared functions from a .so file. 

`void *dlopen(const char *filename, int flags);` can be used to open a so file.  make sure to use `-ldl` in build. 

`void *dlsym(void *handle, const char *sym)` get a function pointer using the name of the function. The function pointer must be cast to function return type.

`int dlclose(void *handle);` closes the function. 

the macros `RTLD_LAZY` and `RTLD_NOW` are used as flags to determine if a function should be called immediately or only when required.

it is conventional to create a typedefinition of a function you will import.

`dlerror` can get the string of a error in importing a function

```c
// in plugin.h

typedef void (*print_hello_t)(const char*);

```
```c
// in plugin.c
#include <stdio.h>
#include "plugin.h"

void print_hello_name(const char *name) {
  printf("Hello %s\n", name);
}

```
```c
// in main.c
#include <dlfcn.h>
#include <stdlib.h>
#include "plugin.h"

plug_hello_t *plug_hello_name = NULL;

int main(void) {
  const char *libplug_file_name = "plugin.so";
  void *libplug = *dlopen(libplug_file_name, RTLD_NOW);

  // error handling
  if (libplug == NULL) {
    fprintf(stderr, "ERROR: could not load %s: %s", libplug_file_name, dlerror());
    return EXIT_FAILURE;
  }

  const char *plug_hello_func_name = "plug_hello_name";
  plug_hello_name = dlsym(plug_hello_func_name);

  if (plug_hello == NULL) {
    fprintf(stderr, "ERROR: could not find %s symbol in %s: %s", plug_hello_func_name, libplug_fild_name, dlerror());

    return EXIT_FAILURE;
  }

  print_hello_name("Link");

  return EXIT_SUCCESS;
}

```
