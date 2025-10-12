#ifndef KLANG_MEMORY_H
#define KLANG_MEMORY_H

#include "common.h"

#define GrowCapacity(capacity) \
    ((capacity) < 8 ? 8 : (capacity) * 2)

#define GrowArray(type, ptr, old_count, new_count)  \
    (type *)ralloc(ptr, sizeof(type) * (old_count), \
                   sizeof(type) * (new_count))

#define FreeArray(type, ptr, old_count) \
    ralloc(ptr, sizeof(type) * (old_count), 0)

void *ralloc(void *ptr, size_t old_size, size_t new_size);

// Memory Management Signatures

// allocated a space in memory
void *k_alloc(unsigned int size);

// reallocated a space in memory for dynamic scaling
void *k_ralloc(void *ptr, unsigned int new_size);

/* free an allocated space in memory
 *  NOTE: Cleanup is called as an automatic process
 *  for chunks and fragmented memory
 */
void k_dealloc(void *ptr);

#endif