#include <stdlib.h>

// internal libraries
#include "chunk.h"
#include "memory.h"

void init_chunk(Chunk *chunk)
{
    chunk->count = 0;
    chunk->capacity = 0;
    chunk->code = NULL;
    chunk->lines = NULL;

    init_value_arr(&chunk->constants);
}

void write_chunk(Chunk *chunk, uint8_t byte)
{
    if (chunk->capacity < chunk->count + 1)
    {
        int old_capacity = chunk->capacity;
        chunk->capacity = GrowCapacity(old_capacity);
        chunk->code = GrowArray(uint8_t, chunk->code, old_capacity, chunk->capacity);
    }

    chunk->code[chunk->count] = byte;
    chunk->count++;
}

void free_chunk(Chunk *chunk)
{
    FreeArray(uint8_t, chunk->code, chunk->capacity);
    FreeArray(int, chunk->lines, chunk->capacity);

    free_value_arr(&chunk->constants);

    init_chunk(chunk);
}

int add_constant(Chunk *chunk, Value value)
{
    write_value_arr(&chunk->constants, value);
    return chunk->constants.count - 1;
}