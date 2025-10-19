#include <stdio.h>
#include <string.h>

#include "memory.h"
#include "value.h"
#include "object.h"

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
    case VAL_NULL:
        printf("nil");
        break;
    case VAL_NUMBER:
        printf("%g", AS_NUMBER(value));
        break;

    case VAL_OBJ:
        printObject(value);
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

    case VAL_NULL:
        return true;

    case VAL_NUMBER:
        return AS_NUMBER(a) == AS_NUMBER(b);

    case VAL_OBJ:
    {
        ObjString *aString = AS_STRING(a);
        ObjString *bString = AS_STRING(b);
        return aString->length == bString->length &&
               memcmp(aString->chars, bString->chars,
                      aString->length) == 0;
    }

    default:
        return false; // Unreachable.
    }
}