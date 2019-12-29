#include "ArrayHash.h"
using namespace std;

void InitArrayHashTable(ArrayHashTable &hash_table, int init_capacity) {
    if (init_capacity > 0 && init_capacity < MAXCAPACITY) 
        hash_table.capacity = NextPrime(init_capacity);
    else 
        hash_table.capacity = NextPrime(32);
    hash_table.table = new HashNode[hash_table.capacity];
    hash_table.size = 0;

    for (int i = 0; i < hash_table.capacity; i++)
        hash_table.table[i].type = Empty;
}

void DelArrayHashTable(ArrayHashTable &hash_table) {
    hash_table.size = hash_table.capacity = 0;
    delete[] hash_table.table;
}

bool IsFull(ArrayHashTable &hash_table) {
    return hash_table.size == hash_table.capacity;
}

bool LinearDelete(ArrayHashTable &hash_table, const char *key) {
    unsigned int curpos, newpos;
    curpos = newpos = ShiftHash(key, hash_table.capacity);

    int cnt = 1;
    while (!(hash_table.table[newpos].type == Empty || (strcmp(hash_table.table[newpos].key, key)  == 0
                                                && hash_table.table[newpos].type == Legitimate))) {
        newpos = (newpos + 1) % hash_table.capacity;
        if (++cnt == hash_table.capacity) return false;
    }

    if (hash_table.table[newpos].type == Empty)
        return false;

    hash_table.table[newpos].type = Deleted;
    
    return true;
}

bool LinearGet(ArrayHashTable &hash_table, const char *key, ArrElemType &value) {
    unsigned int curpos, newpos;
    curpos = newpos = ShiftHash(key, hash_table.capacity);

    int cnt = 1;
    while (!(hash_table.table[newpos].type == Empty || (strcmp(hash_table.table[newpos].key, key) == 0
                                                && hash_table.table[newpos].type == Legitimate))) {
        newpos = (newpos + 1) % hash_table.capacity;
        if (++cnt == hash_table.capacity) return false;
    }

    if (hash_table.table[newpos].type == Empty)
        return false;

    value = hash_table.table[newpos].value;
    return true;
}

bool LinearGetNum(ArrayHashTable &hash_table, const char *key, ArrElemType &value, int &num) {
    unsigned int curpos, newpos;
    curpos = newpos = ShiftHash(key, hash_table.capacity);

    int cnt = 1;
    while (!(hash_table.table[newpos].type == Empty || (strcmp(hash_table.table[newpos].key, key) == 0
                                                && hash_table.table[newpos].type == Legitimate))) {
        newpos = (newpos + 1) % hash_table.capacity;
        if (++cnt == hash_table.capacity) {
            return false;
        }
    }

    if (hash_table.table[newpos].type == Empty)
        return false;

    num = cnt;
    return true;
}

//返回值：哈希表已满：-1   存在key相同元素，替换：1   新元素插入哈希表：0
int LinearPut(ArrayHashTable &hash_table, const char *key, ArrElemType value, ArrElemType &old_value) {
    if (IsFull(hash_table)) return -1;
    unsigned int curpos, newpos;
    curpos = newpos = ShiftHash(key, hash_table.capacity);
    
    while (!(hash_table.table[newpos].type == Empty || (!strcmp(hash_table.table[newpos].key, key) 
                                                && hash_table.table[newpos].type == Legitimate))) {
        newpos = (newpos + 1) % hash_table.capacity;
    }

    if (hash_table.table[newpos].type != Empty) {
        old_value = hash_table.table[newpos].value;
        hash_table.table[newpos].value = value;
        return 1;
    }

    strcpy(hash_table.table[newpos].key, key);
    hash_table.table[newpos].type = Legitimate;
    hash_table.table[newpos].value = value;
    hash_table.size++;
    return 0;
}

void int2string(int n, char *str) {
    if (n <= 0) {
        strcpy(str, "0");
        return ;
    }

    int b = log10(n) + 1;
    str[b] = '\0';
    while (n) {
        str[--b] = (n % 10) + '0';
        n /= 10;
    }
}
