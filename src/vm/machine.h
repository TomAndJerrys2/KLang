
// KLang/virtual_machine

#ifndef KLANG_VM_H
#define KLANG_VM_H

#include "../chunk.h"
#include "../value.h"

// stack size will be dynamic to scale
#define STACK_MAX 256

typedef struct
{
    Chunk *chunk;
    uint8_t *ip;

    Value stack[STACK_MAX];
    Value *stack_top;
} VM;

typedef enum
{
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR
} InterpretResult;

// VM operations
void init_machine();
void free_machine();

InterpretResult interpret(const char *src);

// VM Stack operations
void push(Value value);
Value pop();

#endif