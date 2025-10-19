#ifndef KLANG_COMPILER_H
#define KLANG_COMPILER_H

#include "vm/machine.h"
#include "object.h"

bool compile(const char *source, Chunk *chunk);

#endif