#include <stdio.h>

#include "../common.h"
#include "../debug.h"
#include "machine.h"

// object-like pattern
VM vm;

static void reset_stack()
{
    vm.stack_top = vm.stack;
}

void init_machine()
{
    reset_stack();
}

void free_machine() {}

void push(Value value)
{
    *vm.stack_top = value;
    vm.stack_top++;
}

Value pop()
{
    vm.stack_top--;
    return *vm.stack_top--;
}

static InterpretResult run()
{
#define ReadByte() (*vm.ip++)
#define ReadConstant() (vm.chunk->constants.values[ReadByte()])

#define BinaryOp(operation)  \
    do                       \
    {                        \
        double b = pop();    \
        double a = pop();    \
        push(a operation b); \
    } while (false)

    for (;;)
    {
#ifndef DEBUG_TRACE_EXECUTION
        printf("      ");

        for (Value *slot = vm.stack; slot < vm.stack_top; slot++)
        {
            printf("[ ");
            printValue(*slot);
            printf(" ]");
        }
        printf("\n");

        disassemble_instruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
#endif
        uint8_t instruction;
        switch (instruction = ReadByte())
        {
        case OP_CONSTANT:
            Value constant = ReadConstant();
            push(constant);
            break;

        case OP_NEGATE:
            push(-pop());
            break;

        case OP_ADD:
            BinaryOp(+);
            break;

        case OP_SUBTRACT:
            BinaryOp(-);
            break;

        case OP_MULTIPLY:
            BinaryOp(*);
            break;

        case OP_DIVIDE:
            BinaryOp(/);
            break;

        case OP_RETURN:
            printValue(pop());
            printf("\n");
            return INTERPRET_OK;
        }
    }

#undef ReadByte
#undef ReadConstant
#undef BinaryOp
}

InterpretResult interpret(Chunk *chunk)
{
    vm.chunk = chunk;
    vm.ip = vm.chunk->code;
    return run();
}