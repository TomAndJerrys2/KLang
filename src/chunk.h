#ifndef KLANG_CHUNK_H
#define KLANG_CHUNK_H

// internal libraries
#include "common.h"
#include "value.h"

// Operation Codes
typedef enum
{
    OP_CONSTANT,

    OP_ADD,
    OP_SUBTRACT,
    OP_MULTIPLY,
    OP_DIVIDE,
    OP_NOT,
    OP_NEGATE,

    OP_NULL,
    OP_TRUE,
    OP_FALSE,
    OP_GREATER,
    OP_LESS,
    OP_EQUAL,

    OP_RETURN,
} OpCode;

typedef struct
{
    int count;
    int capacity;

    ValueArray constants;

    int *lines;

    uint8_t *code;
} Chunk;

// allocate a chunk in memory
void init_chunk(Chunk *chunk);

// append a byte to the end of a chunk
void write_chunk(Chunk *chunk, uint8_t byte, int line);

// free the space (chunk) allocated in memory
void free_chunk(Chunk *chunk);

// ...

int add_constant(Chunk *chunk, Value value);

#endif