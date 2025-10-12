#include <stdio.h>

#include "debug.h"

// klang debug library

void disassemble_chunk(Chunk *chunk, const char *name)
{
    printf("--> %s <--", name);

    for (int u_offset = 0; u_offset < chunk->count;)
    {
        u_offset = disassemble_instruction(chunk, u_offset);
    }
}

int disassemble_instruction(Chunk *chunk, int u_offset)
{
    printf("%04d", u_offset);

    uint8_t instruction = chunk->code[u_offset];
    switch (instruction)
    {
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