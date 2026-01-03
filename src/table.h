#ifndef KLANG_TABLE_H
#define KLANG_TABLE_H

#include "common.h"
#include "value.h"

// Maps key value pairs in hash table for quicker lookup
typedef struct {
	ObjString* key;
	Value value;
} Entry;

typedef struct {
	int count;
	int capacity;
	Entry* entries;
} Table;

void initTable(Table* table);
void freeTable(Table* table);
bool tableSet(Table* table, ObjString* key, Value value);

#endif
