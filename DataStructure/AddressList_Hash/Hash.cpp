#include "Hash.h"

using namespace std;

//对字符串进行散列，使用链地址法解决冲突


//返回大于n的下一个素数
int NextPrime(int n) { 
    int i; 
    int p = (n % 2) ? n + 2 : n + 1; //从大于n的第一个奇数开始

    while (p <= MAXCAPACITY) {
        for (i = (int)sqrt(p); i > 2; i--) 
            if (!(p % i))
                break;
        if (i == 2)
            break;
        else 
            p += 2;
    }
    return p;
}

void InitHashTable(HashTable &hash_table, int init_capacity) {
    if (init_capacity > 0 && init_capacity < MAXCAPACITY) 
        hash_table.capacity = NextPrime(init_capacity);
    else 
        hash_table.capacity = NextPrime(32);
    hash_table.table = new Node[hash_table.capacity];
    hash_table.size = 0;
    
    for (int i = 0; i < hash_table.capacity; i++) {
        hash_table.table[i].next = NULL;
    }
}

unsigned int SumHash(const char *key, int table_size) {
    unsigned int h = 0;

    while (*key)
        h += *key++;
    
    return h % table_size;
}

unsigned int ShiftHash(const char *key, int table_size) {
    unsigned int h = 0;
    while (*key)
        h = (h << 5) + *key++;
    return h % table_size;
}

unsigned int ELFHash(const char *key, int table_size) {
    unsigned long h = 0;
    unsigned long x = 0;

    while (*key) {
        h = (h << 4) + (*key++); //h左移4位，当前字符ASCII存入h的低四位
        if ((x = h & 0xF0000000L) != 0) { 
            //如果最高位不为0，则说明字符多余7个，如果不处理，再加第九个字符时，第一个字符会被移出
            //因此要有如下处理
            h ^= (x >> 24);
            //清空28~31位
            h &= ~x;
        }
    }
    return h % table_size;
}

void ReCapacity(HashTable &hash_table, unsigned int (*Hash)(const char *key, int table_size)) {
    const int ori_capacity = hash_table.capacity;
    
    hash_table.capacity = NextPrime(hash_table.capacity * 2);
    Node *ori_table = hash_table.table;
    hash_table.table = new Node[hash_table.capacity];
    for (int i = 0; i < hash_table.capacity; i++) {
        hash_table.table[i].next = NULL;
    }
    
    for (int i = 0; i < ori_capacity; i++) {
        Node *p = ori_table[i].next, *q;
        while (p) {
            q = p;
            p = p->next;
            int new_pos = Hash(q->key, hash_table.capacity);
            q->next = hash_table.table[new_pos].next;
            hash_table.table[new_pos].next = q;
        }
    }

    delete[] ori_table;
}

//将以key为键的元素value放入Hash表，返回是否有旧元素，有返回true，使用value进行替换，否则返回false，old_value为旧元素
bool Put(HashTable &hash_table, const char *key, ElemType value, ElemType &old_value, unsigned int (*Hash)(const char *key, int table_size)) {
    //若添加新元素后使得元素个数等于哈希表容量*装填因子，进行扩容
    if (hash_table.size + 1 >= hash_table.capacity * LOADFACTOR) 
       ReCapacity(hash_table, Hash);

    unsigned int pos = Hash(key, hash_table.capacity);

    Node *p = hash_table.table[pos].next;
    while (p) {
        if (!strcmp(p->key, key)) {
            old_value = p->value;
            p->value = value;

            return true;
        }
        p = p->next;
    }

    Node *node = new Node;
    strcpy(node->key, key);
    node->value = value;
    node->next = hash_table.table[pos].next;
    hash_table.table[pos].next = node;
    hash_table.size++;

    return false;
}

bool Get(HashTable &hash_table, const char *key,  ElemType &value, unsigned int (*Hash)(const char *key, int table_size)) {
    int pos = Hash(key, hash_table.capacity);

    Node *p = hash_table.table[pos].next;
    while (p) {
        if (!strcmp(key, p->key)) {
            value = p->value;
            return true;
        }
        p = p->next;
    }

    return false;    
}

double GetASL(HashTable &hash_table, unsigned int (*Hash)(const char *key, int table_size)) {
    double asl = 0.0;
    for (int i = 0; i < hash_table.capacity; i++) {
        int n = 0;
        Node *p = hash_table.table[i].next;
        while (p) {
            asl += (++n);
            p = p->next;
        }
    }

    return asl / hash_table.size;
}

bool Remove(HashTable &hash_table, const char *key, ElemType &value, unsigned int (*Hash)(const char *key, int table_size)) {
    int pos = Hash(key, hash_table.capacity);

    Node *p = &hash_table.table[pos];
    while (p ->next) {
        if (!strcmp(p->next->key, key)) {
            value = p->next->value;
            Node *t = p->next;
            p->next = t->next;
            delete t;
            return true;
        }
        p = p->next;
    }

    return false;
}

void DelHashTable(HashTable &hash_table) {
    for (int i = 0; i < hash_table.capacity; i++) {
        Node *p = hash_table.table[i].next;
        while (p) {
            Node *t = p;
            p = p->next;
            delete t;
        }
    }

    delete[] hash_table.table;
}

void TraverseHashTable(HashTable &hash_table, void (*visit)(ElemType v)) {
    for (int i = 0; i < hash_table.capacity; i++) {
        Node *p = hash_table.table[i].next;
        while (p) {
            visit(p->value);
            p = p->next;
        }
    }
}

