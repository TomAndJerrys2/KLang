#include <stdio.h>
#include <stdarg.h>

#include "../common.h"
#include "../debug.h"
#include "machine.h"
#include "compiler.h"

// <--
VM vm;

// -------------------------------------------------------------

// static void vm_info();

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

// -------------------------------------------------------------

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

static bool is_falsey(Value value)
{
    return IS_NIL(value) || (IS_BOOL(value) && !AS_BOOL(value));
}

// -------------------------------------------------------------

static InterpretResult run()
{
#define ReadByte() (*vm.ip++)
#define ReadConstant() (vm.chunk->constants.values[ReadByte()])

    // -------------------------------------------------------------

#define BinaryOP(value_type, op)                        \
    do                                                  \
    {                                                   \
        if (!IS_NUMBER(peek(0)) || !IS_NUMBER(peek(1))) \
        {                                               \
            runtime_error("Operands must be numbers."); \
            return INTERPRET_RUNTIME_ERROR;             \
        }                                               \
        double b = AS_NUMBER(pop());                    \
        double a = AS_NUMBER(pop());                    \
        push(value_type(a op b));                       \
    } while (false)

    /*    #define BINARY_OP(operation) \
        do                       \
        {                        \
            double b = pop();    \
            double a = pop();    \
            push(a operation b); \
        } while (false)*/

    // -------------------------------------------------------------

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

        // -------------------------------------------------------------

        uint8_t instruction;
        switch (instruction = ReadByte())
        {
        case OP_CONSTANT:
            Value constant = ReadConstant();
            push(constant);
            break;

        case OP_GREATER:
            BinaryOP(BOOL_VAL, >);
            break;

        case OP_LESS:
            BinaryOP(BOOL_VAL, <);
            break;

        case OP_NULL:
            push(NIL_VAL);
            break;
        case OP_FALSE:
            push(BOOL_VAL(false));
            break;

        case OP_TRUE:
            push(BOOL_VAL(true));
            break;

        case OP_EQUAL:
        {
            Value b = pop();
            Value a = pop();
            push(BOOL_VAL(valuesEqual(a, b)));
            break;
        }

        case OP_ADD:
            BinaryOP(NUMBER_VAL, +);
            break;

        case OP_SUBTRACT:
            BinaryOP(NUMBER_VAL, -);
            break;

        case OP_MULTIPLY:
            BinaryOP(NUMBER_VAL, *);
            break;

        case OP_DIVIDE:
            BinaryOP(NUMBER_VAL, /);
            break;

        case OP_NOT:
            push(BOOL_VAL(is_falsey(pop())));
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
#undef BINARY_OP
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