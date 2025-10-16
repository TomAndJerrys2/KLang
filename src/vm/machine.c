#include <stdio.h>
#include <stdarg.h>

#include "../common.h"
#include "../debug.h"
#include "machine.h"
#include "compiler.h"

// object-like pattern
VM vm;

static void reset_stack()
{
    vm.stack_top = vm.stack;
}

static void runtime_error(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    fputs("\n", stderr);

    size_t instruction = vm.ip - vm.chunk->code - 1;
    int line = vm.chunk->lines[instruction];

    fprintf(stderr, "[line %d] in script\n", line);
    reset_stack();
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

static Value peek(int distance)
{
    return vm.stack_top[-1 - distance];
}

static InterpretResult run()
{
#define ReadByte() (*vm.ip++)
#define ReadConstant() (vm.chunk->constants.values[ReadByte()])

#define BINARY_OP(valueType, op)                        \
    do                                                  \
    {                                                   \
        if (!IS_NUMBER(peek(0)) || !IS_NUMBER(peek(1))) \
        {                                               \
            runtimeError("Operands must be numbers.");  \
            return INTERPRET_RUNTIME_ERROR;             \
        }                                               \
        double b = AS_NUMBER(pop());                    \
        double a = AS_NUMBER(pop());                    \
        push(value_type(a op b));                       \
    } while (false)

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

        case OP_NEGATE:
            if (!IS_NUMBER(peek(0)))
            {
                runtimeError("Operand must be a number.");
                return INTERPRET_RUNTIME_ERROR;
            }
            push(NUMBER_VAL(-AS_NUMBER(pop())));
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

InterpretResult interpret(const char *src)
{
    Chunk chunk;
    initChunk(&chunk);

    if (!compile(src, &chunk))
    {
        freeChunk(&chunk);
        return INTERPRET_COMPILE_ERROR;
    }

    vm.chunk = &chunk;
    vm.ip = vm.chunk->code;

    InterpretResult result = run();

    freeChunk(&chunk);
    return result;
}