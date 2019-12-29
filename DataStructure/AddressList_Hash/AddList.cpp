#include <iostream>
#include "AddList.h"
#include "Hash.h"
#include "ArrayHash.h"

using namespace std;

typedef enum {Phone, Name} HashType;
HashType hash_type;
HashTable hash_table;

bool PutRecord(HashTable &hash_tabe, const char *key, AddList add, AddList &old_add, unsigned int (*Hash)(const char *key, int table_size) = ShiftHash) {
    return Put(hash_tabe, key, add, old_add, Hash);
}

bool GetRecord(HashTable &hash_table, const char *key, AddList &add, unsigned int (*Hash)(const char *key, int table_size) = ShiftHash) {
    return Get(hash_table, key, add, Hash);
}

bool RemoveRecord(HashTable &hash_table, const char *key, AddList &add, unsigned int (*Hash)(const char *key, int table_size) = ShiftHash) {
    return Remove(hash_table, key, add, Hash);
}

void PrintLine() {
    cout << "----------------------------------------------------" << endl;
}

void ClearTerminal() {
    system("clear");
}

void PrintRecord(AddList add) {
    cout << "---------------------------------------" << endl;
    cout << "电话：" << add.phone_num << endl;
    cout << "姓名：" << add.name << endl;
    cout << "地址：" << add.address << endl;
    cout << "---------------------------------------" << endl;
}

void AddRecordForm() {
    ClearTerminal();
    cout << "\n添加通讯录\n" << endl;

    char phone_num[MAXPHONENUM];
    char name[MAXNAME];
    char address[MAXADDRESS];
    char right[10];

    cout << "\n电话号码：";
    cin >> phone_num;
    cout << "\n姓名：";
    cin >> name;
    cout << "\n通讯住址：";
    cin >> address;
    cout << "\n是否添加(Y 或 N)：";
    cin >> right;

    if (right[0] == 'Y' || right[0] == 'y') {
        AddList add(phone_num, name, address);
        AddList old_add;
        if (hash_type == Phone)
            PutRecord(hash_table, add.phone_num, add, old_add);
        else
            PutRecord(hash_table, add.name, add, old_add);
        
        cout << "\n已添加新记录：\n" << endl;
        PrintRecord(add);

        char continue_add[10];
        cout << "\n是否继续添加(Y 或 N)：";
        cin >> continue_add;

        if (continue_add[0] == 'Y' || continue_add[0] == 'y')
            AddRecordForm();
        else 
            MainForm();
    } else 
        MainForm();
}

void QueryRecordForm() {
    ClearTerminal();
    cout << "\n查询通讯录\n" << endl;

    cout << "1)   搜索电话\n" << endl;
    cout << "2)   搜索姓名\n" << endl;
    cout << "q)   返回\n" << endl;
    cout << "\n> ";

    char choose[10];
    cin >> choose;

    if (choose[0] == '1')
        QueryRecordByPhoneNum();
    else if (choose[0] == '2')
        QueryRecordByName();
    else 
        MainForm();
}

char g_phone[MAXNAME];
bool has_phone = false;
void TraverseFindPhone(AddList add) {
    if (!strcmp(g_phone, add.phone_num)) {
        PrintRecord(add);
        has_phone = true;
    }
}

void QueryRecordByPhoneNum() {
    ClearTerminal();
    cout << "\n输入电话号码查询记录\n" << endl;
    char phone_num[MAXPHONENUM];
    AddList add;

    cout << "电话号码：";
    cin >> phone_num;

    if (hash_type == Phone) {
        if (GetRecord(hash_table, phone_num, add)) {
            cout << endl;
            PrintRecord(add);
            cout << endl;
        } else {
            cout << "\n该电话不存在\n" << endl;
        }
    } else {
        strcpy(g_phone, phone_num);
        TraverseHashTable(hash_table, TraverseFindPhone);
        if (!has_phone)
            cout << "\n该电话不存在\n" << endl;
    }

    char choose[10];
    cout << "是否继续查询(Y 或 N)：";
    cin >> choose;

    if (choose[0] == 'Y' || choose[0] == 'y')
        QueryRecordByPhoneNum();
    else
        QueryRecordForm();
}

char g_name[MAXNAME];
bool has_name = false;
void TraverseFindName(AddList add) {
    if (!strcmp(g_name, add.name)) {
        PrintRecord(add);
        has_name = true;
    }
}

void QueryRecordByName()
{
    ClearTerminal();
    cout << "\n输入姓名查询记录\n" << endl;

    char name[MAXPHONENUM];
    AddList add;

    cout << "姓名：";
    cin >> name;

    if (hash_type == Name) {
        if (GetRecord(hash_table, name, add)) {
            cout << endl;
            PrintRecord(add);
            cout << endl;
        } else {
            cout << "\n该姓名不存在\n" << endl;
        }
    } else {
        strcpy(g_name, name);
        TraverseHashTable(hash_table, TraverseFindName);
        if (!has_name)
            cout << "\n该姓名不存在\n" << endl;
    }

    char choose[10];
    cout << "是否继续查询(Y 或 N)：";
    cin >> choose;

    if (choose[0] == 'Y' || choose[0] == 'y')
        QueryRecordByName();
    else
        QueryRecordForm();
}

void VisitRecord(AddList add) {
    printf("  %-15s%-20s%-30s\n", add.phone_num, add.name, add.address);
}

void DisplayAllRecord() {
    ClearTerminal();
    PrintLine();
    printf("  %-15s   %-20s%-30s\n\n", "电话号码", "姓名", "通讯地址");
    TraverseHashTable(hash_table, VisitRecord);
    PrintLine();

    cout << "\n\n按任意键返回..." << endl;
    getchar();
    getchar();
    MainForm();
}

void ImportRecordsFromFile() {
    ClearTerminal();
    FILE* file = fopen("./records.txt", "r");
    if (file) {
        while (!feof(file)) {
            AddList record, old_record;
            fscanf(file, "%s%s%s", record.phone_num, record.name, record.address);
            if (hash_type == Phone)
                PutRecord(hash_table, record.phone_num, record, old_record);
            else
                PutRecord(hash_table, record.name, record, old_record);
        }

        cout << "\n导入成功" << endl;
        fclose(file);
    } else {
        cout << "\n导入失败..." << endl;
    }

    cout << "\n\n按任意键返回..." << endl;
    getchar();
    getchar();
    MainForm();
}

void GenerateRandomRecords(int total_num, AddList Records[]) {
    const char char_set[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
        'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2',
        '3', '4', '5', '6', '7', '8', '9', '\0'};
    int char_set_len = strlen(char_set);
    
    srand(time(NULL));

    for (int i = 0; i < total_num; i++) {
        char key[MAXKEYLEN] = {'\0'};
        int len = rand() % MAX_RANDOM_STR_SIZE + 1;

        for (int i = 0; i < len; i++) {
            int ci = rand() % char_set_len;
            key[i] = char_set[ci];
        }
        AddList add(key, key, key);
        Records[i] = add;
    }
}

void HashFuncCompare() {
    ClearTerminal();
    cout << "\n不同哈希函数性能对比\n" << endl;

    int total_num;

    double sum_asl = 0, shift_asl = 0, elf_asl = 0;
    double sum_size = 0, shift_size = 0, elf_size = 0;
    cout << "输入随机生成数据个数：";
    cin >> total_num;

    if (total_num <= 0)
        total_num = 100;

    AddList *Records = new AddList[total_num], old_add;
    GenerateRandomRecords(total_num, Records);

    HashTable sum_hash, shift_hash, elf_hash;
    InitHashTable(sum_hash, 32);
    InitHashTable(shift_hash, 32);
    InitHashTable(elf_hash, 32);
    
    for (int i = 0; i < total_num; i++) {
        Put(sum_hash, Records[i].phone_num, Records[i], old_add, SumHash);
        Put(shift_hash, Records[i].phone_num, Records[i], old_add, ShiftHash);
        Put(elf_hash, Records[i].phone_num, Records[i], old_add, ELFHash);
    }

    sum_size = sum_hash.size;
    shift_size = shift_hash.size;
    elf_size = elf_hash.size;

    sum_asl = GetASL(sum_hash, SumHash);
    shift_asl = GetASL(shift_hash, ShiftHash);
    elf_asl = GetASL(elf_hash, ELFHash);

    DelHashTable(sum_hash);
    DelHashTable(shift_hash);
    DelHashTable(elf_hash);

    cout << "\n统计结果：\n" << endl;
    PrintLine();
    printf("%10s\t%10s\t%10s\n", "Hash Fun", "Size", "ASL");
    PrintLine();
    printf("%10s\t%10.2f\t%10.2f\n", "SumHash", sum_size, sum_asl);
    printf("%10s\t%10.2f\t%10.2f\n", "ShiftHash", shift_size, shift_asl);
    printf("%10s\t%10.2f\t%10.2f\n", "ELFHash", elf_size, elf_asl);
    PrintLine();

    cout << "\n\n按任意键返回..." << endl;
    getchar();
    getchar();
    MainForm();
}

void ConflictMethodCompare() {
    ClearTerminal();
    cout << "\n不同哈希函数性能对比\n" << endl;

    int total_num;

    double list_asl = 0, array_asl = 0;
    double list_size = 0, array_size = 0;
    cout << "输入随机生成数据个数：";
    cin >> total_num;

    if (total_num <= 0)
        total_num = 100;

    AddList *Records = new AddList[total_num], old_add;
    GenerateRandomRecords(total_num, Records);

    HashTable list_hash;
    ArrayHashTable array_hash;
    InitHashTable(list_hash, 32);
    InitArrayHashTable(array_hash, total_num);
    
    for (int i = 0; i < total_num; i++) {
        Put(list_hash, Records[i].phone_num, Records[i], old_add, ShiftHash);
        LinearPut(array_hash, Records[i].phone_num, Records[i], old_add);
    }

    list_size = list_hash.size;
    array_size = array_hash.size;

    list_asl = GetASL(list_hash, ShiftHash);

    int sum = 0;
    for (int i = 0; i < total_num; i++) {
        int num;
        AddList add;
        LinearGetNum(array_hash, Records[i].phone_num, add, num);
        sum += num;
    }
    array_asl = 1.0*sum / total_num;

    DelHashTable(list_hash);
    DelArrayHashTable(array_hash);

    cout << "\n统计结果：\n" << endl;
    PrintLine();
    printf("%10s\t%10s\t%10s\n", "Conflict Method", "Size", "ASL");
    PrintLine();
    printf("%10s\t%10.2f\t%10.2f\n", "List Hash", list_size, list_asl);
    printf("%10s\t%10.2f\t%10.2f\n", "Linear Hash", array_size, array_asl);
    PrintLine();

    cout << "\n\n按任意键返回..." << endl;
    getchar();
    getchar();
    MainForm();
}

void MainForm() {    
    ClearTerminal();
    PrintLine();

    cout << "\n\n1)   添加通讯录\n" << endl;
    cout << "2)   查询通讯录\n" << endl;
    cout << "3)   查看全部通讯录\n" << endl;
    cout << "4)   批量导入通讯录\n" << endl;
    cout << "5)   不同哈希函数比较\n" << endl;
    cout << "6)   不同冲突解决方法比较\n" << endl;
    cout << "q)   退出\n\n" << endl;

    PrintLine();
    cout << "\n> ";

    char op[10];
    cin >> op;

    if (op[0] == '1')
        AddRecordForm();
    else if (op[0] == '2')
        QueryRecordForm();
    else if (op[0] == '3')
        DisplayAllRecord();
    else if (op[0] == '4')
        ImportRecordsFromFile();
    else if (op[0] == '5')
        HashFuncCompare();
    else if (op[0] == '6')
        ConflictMethodCompare();
    else
        return;
}

void ChooseHashType() {
    ClearTerminal();
    PrintLine();

    cout << "\n\n选择建立哈希索引类型\n" << endl;
    cout << "1) 以 电话号码 建立\n" << endl;
    cout << "2) 以 姓名 建立\n" << endl;
    cout << "q) 退出\n\n" << endl;

    PrintLine();
    cout << "\n> ";

    char op[10];
    cin >> op;

    if (op[0] == '1') 
        hash_type = Phone;
    else if (op[0] == '2')
        hash_type = Name;
    else
        return;

    InitHashTable(hash_table, 30);
    MainForm();
}

void WelcomeForm() {
    ClearTerminal();
    PrintLine();
    cout << "\n\n             哈希电话号码查找系统 \n\n";
    cout << "                     高天      \n\n";
    cout << "                   软件1601      \n\n";
    cout << "                 201616030213     \n\n";
    PrintLine();
    getchar();
    ChooseHashType();
}


int main()
{
    WelcomeForm();

    return 0;
}
