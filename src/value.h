#ifndef KLANG_VALUE_H
#define KLANG_VALUE_H

#include "common.h"

typedef double Value;

typedef struct
{
    int capacity;
    int count;
    Value *values;
} ValueArray;

void init_value_arr(ValueArray *arr);
void write_value_arr(ValueArray *arr, Value value);
void free_value_arr(ValueArray *arr);

void printValue(Value value);

#endif