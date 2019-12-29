#ifndef _ARRAYHASH_H
#define _ARRAYHASH_H

#include <iostream>
#include <cstdio>
#include <cmath>
#include "Hash.h"

using namespace std;

typedef AddList ArrElemType;
/* 散列单元状态类型，分别对应：有合法元素、空单元、有已删除元素 */
typedef enum { Legitimate, Empty, Deleted } NodeType;

struct HashNode {
    char key[MAXKEYLEN];
    ArrElemType value;
    NodeType type;
};

struct ArrayHashTable {
    int size;
    int capacity;
    HashNode *table;
};


void InitArrayHashTable(ArrayHashTable &hash_table, int init_capacity);
void DelArrayHashTable(ArrayHashTable &hash_table);
bool IsFull(ArrayHashTable &hash_table);
bool LinearDelete(ArrayHashTable &hash_table, const char *key);
bool LinearGet(ArrayHashTable &hash_table, const char *key, ArrElemType &value);
bool LinearGetNum(ArrayHashTable &hash_table, const char *key, ArrElemType &value, int &num);
int LinearPut(ArrayHashTable &hash_table, const char *key, ArrElemType value, ArrElemType &old_value);

#endif