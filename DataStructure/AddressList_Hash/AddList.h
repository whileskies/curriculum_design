#ifndef _ADDLIST_H
#define _ADDLIST_H

#include <cstring>
#include <ctime>

#define MAXPHONENUM 20
#define MAXNAME 50
#define MAXADDRESS 255
#define MAX_RANDOM_STR_SIZE 100

struct AddList {
    char phone_num[MAXPHONENUM];
    char name[MAXNAME];
    char address[MAXADDRESS];

    AddList() {}

    AddList(const char *phone_num, const char *name, const char *address) {
        strcpy(this->phone_num, phone_num);
        strcpy(this->name, name);
        strcpy(this->address, address);      
    }
};

void InitSys();
void AddRecordForm();
void MainForm();
void WelcomeForm();
void QueryRecordByPhoneNum();
void QueryRecordByName();

#endif