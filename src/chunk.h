#ifndef KLANG_CHUNK_H
#define KLANG_CHUNK_H

#include "common.h"

typedef enum
{
    OP_RETURN,
} OpCode;

typedef struct
{
    int count;
    int capacity;

    uint8_t *code;
} Chunk;

// Signatures

void init_chunk(Chunk *chunk);

#endif