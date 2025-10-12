#ifndef KLANG_CHUNK_H
#define KLANG_CHUNK_H

// internal libraries
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

// allocate a chunk in memory
void init_chunk(Chunk *chunk);

// append a byte to the end of a chunk
void write_chunk(Chunk *chunk, uint8_t byte);

// free the space (chunk) allocated in memory
void free_chunk(Chunk *chunk);

#endif