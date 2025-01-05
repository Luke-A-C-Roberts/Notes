#include <stdio.h>
#include <stdlib.h>

#define STACK_SZ 1024U

typedef enum { STOP, ADD, MUL, PUSH } instruction_t;
typedef void (*instructionp_t)(void);

static int stack[STACK_SZ];
static int sp;
static instructionp_t *ip;
static int running;

static inline int pop(
    int const stack[static const restrict STACK_SZ],
    int *const restrict stack_ptr
) {
    (*stack_ptr)--;
    return stack[*stack_ptr];
}

static inline void push(
    int const val,
    int stack[static const restrict STACK_SZ],
    int *const restrict stack_ptr
) {
    stack[*stack_ptr] = val;
    (*stack_ptr)++;
}

static void add()  {
    int x,y;
    x = pop(stack, &sp);
    y = pop(stack, &sp);
    push(x + y, stack, &sp);
}

static void mul()  {
    int x,y;
    x = pop(stack, &sp);
    y = pop(stack, &sp);
    push(x * y, stack, &sp);
}

static void pushi() {
    int x;
    x = (int)((*ip)++);
    push(x, stack, &sp);
}

void stop() { running = 0; }

static instructionp_t *read_file(char *name) {
  FILE *file;
  instructionp_t *code;
  instructionp_t *cp;
  long  size;
  char ch;
  unsigned int val;

  file = fopen(name, "r");

  if(file == (void *)0) exit(EXIT_FAILURE);

  fseek(file, 0L, SEEK_END);
  size = ftell(file);
  code = calloc(size, sizeof(instructionp_t));
  if(code == (void *)0) exit(EXIT_FAILURE);
  cp = code;

  fseek(file, 0L, SEEK_SET);
  while ( ( ch = fgetc(file) ) != EOF )
    {
      switch (ch) {
      case ADD: *cp++ = &add; break;
      case MUL: *cp++ = &mul; break;
      case PUSH:
	*cp++ = &pushi;
	ch = fgetc(file);
	val = 0;
	while (ch--) { val = val * 256 + fgetc(file); }
	*cp++ = (instructionp_t)val;
	break;
      }
    }
  *cp = &stop;

  fclose(file);
  return code;
}

int run() {
  sp = 0;
  running = 1;

  while (running) (*ip++)();

  return pop(stack, &sp);
}
  

int main(int argc, char *argv[]) {
  if (argc > 1) {
    ip = read_file(argv[1]);
    printf("The value is: %i\n", run());
    return 0;
  } else {
    printf("Give the file name of a byte code program as argument\n");
    return -1;
  }
}
