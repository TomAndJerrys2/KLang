#include <stdio.h>
#include <string.h>

#include "table.h"
#include "memory.h"
#include "object.h"
#include "value.h"

#include "vm/machine.h"

#define ALLOCATE_OBJ(type, objectType) \
    (type *)allocate_object(sizeof(type), objectType)

// random number hash for now will refactor
static uint32_t hashString(const char* key, int length) {
	uint32_t hash = 21375794903u;

	for(size_t i = 0; i < length; i++) {
		hash ^= (uint32_t)key[i];
		hash *= 168810;
	}

	return hash;
}

static Obj *allocate_object(size_t size, ObjType type)
{
    Obj *object = (Obj *)ralloc(NULL, 0, size);
    object->type = type;

    object->next = vm.objects;
    vm.objects = object;
    return object;
}

// str operations

ObjString *copy_string(const char *chars, int length)
{
    char *heapChars = ALLOCATE(char, length + 1);
    uint32_t hash = hashString(chars, length);

    memcpy(heapChars, chars, length);
    heapChars[length] = '\0';
    
    return allocateString(heapChars, length, hash);
}

void printObject(Value value)
{
    switch (OBJ_TYPE(value))
    {
    case OBJ_STRING:
        printf("%s", AS_CSTRING(value));
        break;
    }
}

static ObjString *allocate_string(char *chars, 
		int length, uint32_t hash)
{
    ObjString *string = ALLOCATE_OBJ(ObjString, OBJ_STRING);

    string->length = length;
    string->chars = chars;
    string->hash = hash;

    return string;
}

ObjString *takeString(char *chars, int length)
{
    uint32_t hash = hashString(chars, length);
    return allocateString(chars, length, hash);
}
