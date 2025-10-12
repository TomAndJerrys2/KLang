#ifndef KLANG_DEBUG_H
#define KLANG_DEBUG_H

#include "chunk.h"

void disassemble_chunk(Chunk *chunk, const char *name);
int disassemble_instruction(Chunk *chunk, int u_offset);

#endif