typedef enum Instructions {
    STOP,
    ADD,
    MUL,
    PUSH
} Instructions;

#define STACK_SZ 1024U

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

int run(char *code) {
  int stack[STACK_SZ];
  int sp = 0, size = 0, val = 0;
  char *ip = code;

  while (*ip != STOP) {
    switch (*ip++) {
    case ADD: push(pop(stack, &sp) + pop(stack, &sp), stack, &sp); break;
    case MUL: push(pop(stack, &sp) * pop(stack, &sp), stack, &sp); break;
    case PUSH:
      size = *ip++;
      val = 0;
      while (size--) { val = val * 256 + *ip++; }
      push(val, stack, &sp);
      break;
    }
  }
  return pop(stack, &sp);
}
