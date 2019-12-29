#ifndef _HASH_H
#define _HASH_H

#include <iostream>
#include <cmath>
#include <cstring>
#include "AddList.h"

#define MAXCAPACITY 1 << 30
#define LOADFACTOR 0.75f
#define MAXKEYLEN 255

typedef AddList ElemType;

struct Node
{
    char key[MAXKEYLEN];
    ElemType value;
    Node *next;
};

struct HashTable
{
    int capacity;
    int size;
    Node *table;
};

int NextPrime(int n);
void InitHashTable(HashTable &hash_table, int init_capacity);
unsigned int SumHash(const char *key, int table_size);
unsigned int ShiftHash(const char *key, int table_size);
unsigned int ELFHash(const char *key, int table_size);
bool Put(HashTable &hash_table, const char *key, ElemType value, ElemType &old_value, unsigned int (*Hash)(const char *key, int table_size));
bool Get(HashTable &hash_table, const char *key,  ElemType &value, unsigned int (*Hash)(const char *key, int table_size));
bool Remove(HashTable &hash_table, const char *key, ElemType &value, unsigned int (*Hash)(const char *key, int table_size));
void DelHashTable(HashTable &hash_table);
void TraverseHashTable(HashTable &hash_table, void (*visit)(ElemType v));
double GetASL(HashTable &hash_table, unsigned int (*Hash)(const char *key, int table_size));

#endif