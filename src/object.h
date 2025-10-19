#ifndef KLANG_OBJECT_H
#define KLANG_OBJECT_H

#include "common.h"
#include "value.h"

#define OBJ_TYPE(value) (AS_OBJ(value)->type)

ObjString *copy_string(const char *chars, int length);

void printObject(Value value);

ObjString *takeString(char *chars, int length);

static inline bool is_obj_type(Value value, ObjType type)
{
    return IS_OBJ(value) && (AS_OBJ(value)->type) == type;
}

// Type Check Allocations
#define IS_STRING(value) is_obj_type(value, OBJ_STRING)

#define AS_STRING(value) ((ObjString *)AS_OBJ(value))
#define AS_CSTRING(value) (((ObjString *)AS_OBJ(value))->chars)

// Object Types
typedef enum
{
    OBJ_STRING,

    // Structures -- for later -- TBD
    // OBJ_VECTOR
    // OBJ_HASHMAP
    // OBJ_DICT
    // OBJ_LLIST // Linked List
    // OBJ_STACK
    // OBJ_QUEUE
    // OBJ_MINHEAP
    // OBJ_MAXHEAP
    // OBJ_BTREE // Binary Tree
    // OBJ_GRAPH

    // SMART POINTERS TBD

    // OBJ_WEAK_PTR
    // OBJ_SHRD_PTR
    // OBJ_UNQ_PTR
} ObjType;

// Type Definitions

typedef enum
{
    OBJ_STRING,
} ObjType;

struct Obj
{
    ObjType type;

    struct Obj *next;
};

struct ObjString
{
    Obj obj;
    int length;
    char *chars;
};

#endif