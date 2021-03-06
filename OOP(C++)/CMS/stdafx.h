// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"
#include <stdio.h>
#include <tchar.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <cstring>
#include <fstream>

using namespace std;



// TODO: 在此处引用程序需要的其他头文件
#include"Classroom.h"

//功能函数
Classroom* importInfo(uint &n);
uint chooseCampus();
void printLine();
void disOneBuildRoomsInfo(uint campus, uint buildID, uint n, Classroom *rooms);
uint chooseBuildID();
void displayClassType();
void addClassRooms(uint n, Classroom *rooms);
void outputInfo(int n, Classroom *rooms, int delRoom = -1);
void modifyRoomType(uint n, Classroom *rooms);
void chooseRoom(uint &campus, uint &buildID, uint &roomID);
int findRoomIndex(uint n, Classroom *rooms, uint campus, uint buildID, uint roomID);
void displyRoomDetailInfo(uint n, Classroom *rooms);
int isVancant(const Classroom &room, const classTime &time);
void orderVancantRooms(uint n, Classroom *rooms, uint campus, uint buildID, uint roomID, const classTime &time);
void statistics(uint n, Classroom *rooms, uint campus);
void start();
void choosePermission();
void enterAdminSystem();
void regularSystem();
void adminSystem();
void exitSystem();