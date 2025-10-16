#include <stdio.h>

#include "memory.h"
#include "value.h"

void init_value_arr(ValueArray *arr)
{
    arr->values = NULL;
    arr->capacity = 0;
    arr->count = 0;
}

void write_value_arr(ValueArray *arr, Value value)
{
    if (arr->capacity < arr->count + 1)
    {
        int old_capacity = arr->capacity;
        arr->capacity = GrowCapacity(old_capacity);
        arr->values = GrowArray(Value, arr->values, old_capacity, arr->capacity);
    }

    arr->values[arr->count] = value;
    arr->count++;
}

void free_value_arr(ValueArray *arr)
{
    FreeArray(Value, arr->values, arr->capacity);
    init_value_arr(arr);
}

void printValue(Value value)
{
    printf("%g", AS_NUMBER(value));
}