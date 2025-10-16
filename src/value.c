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
    switch (value.type)
    {
    case VAL_BOOL:
        printf(AS_BOOL(value) ? "true" : "false");
        break;
    case VAL_NIL:
        printf("nil");
        break;
    case VAL_NUMBER:
        printf("%g", AS_NUMBER(value));
        break;
    }
}

bool values_equal(Value a, Value b)
{
    if (a.type != b.type)
        return false;
    switch (a.type)
    {
    case VAL_BOOL:
        return AS_BOOL(a) == AS_BOOL(b);

    case VAL_NIL:
        return true;

    case VAL_NUMBER:
        return AS_NUMBER(a) == AS_NUMBER(b);

    default:
        return false; // Unreachable.
    }
}