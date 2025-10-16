#include <stdio.h>

#include "debug.h"
#include "value.h"

// klang debug library

void disassemble_chunk(Chunk *chunk, const char *name)
{
    printf("--> %s <--", name);

    for (int u_offset = 0; u_offset < chunk->count;)
    {
        u_offset = disassemble_instruction(chunk, u_offset);
    }
}

// has opposite but constant offset
static int constantInstruction(const char *name, Chunk *chunk, int offset)
{
    uint8_t constant = chunk->code[offset + 1];
    printf("%-16s %4d", name, constant);
    printValue(chunk->constants.values[constant]);
    printf("'\n");

    return offset + 2;
}

int disassemble_instruction(Chunk *chunk, int u_offset)
{
    printf("%04d", u_offset);

    if (u_offset > 0 &&
        chunk->lines[u_offset] == chunk->lines[u_offset - 1])
    {
        printf("   |");
    }
    else
    {
        printf("%4d ", chunk->lines[u_offset]);
    }

    uint8_t instruction = chunk->code[u_offset];
    switch (instruction)
    {
    case OP_CONSTANT:
        return constantInstruction("OP_CONSTANT", chunk, u_offset);

        // Integral Operations
    case OP_NOT:
        return simple_istruction("OP_NOT", u_offset);

    case OP_NEGATE:
        return simple_instruction("OP_NEGATE", u_offset);

    case OP_NULL:
        return simple_instruction("OP_NIL", u_offset);

    case OP_TRUE:
        return simple_instruction("OP_TRUE", u_offset);

    case OP_FALSE:
        return simple_instruction("OP_FALSE", u_offset);

    case OP_EQUAL:
        return simple_instruction("OP_EQUAL", u_offset);

    case OP_GREATER:
        return simple_instruction("OP_GREATER", u_offset);

    case OP_LESS:
        return simple_instruction("OP_LESS", u_offset);

    case OP_ADD:
        return simple_instruction("OP_ADDt", u_offset);

    case OP_SUBTRACT:
        return simple_instruction("OP_SUBTRACT", u_offset);

    case OP_MULTIPLY:
        return simple_instruction("OP_MULTIPLY", u_offset);

    case OP_DIVIDE:
        return simple_instruction("OP_DIVIDE", u_offset);

    case OP_RETURN:
        return simple_instruction("OP_RETURN", u_offset);

    default:
        printf("Unkown OpCode %d\n", instruction);
        return u_offset + 1;
    }
}

// can have an opposte offset
static int simple_instruction(const char *name, int offset)
{
    printf("%s\n", name);
    return offset + 1;
}