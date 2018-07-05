#ifndef CONFIG_H
#define	CONFIG_H	

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

#define CAMPUSCNT 3
#define CLASSROOMTYPECNT 11

string CAMPUSTYPE[3] = {"莲花街校区", "嵩山路校区", "中原路校区" };


string CLASSROOMTYPE[11] = {
	"多媒体教室活动教室",
	"建筑学专业教室",
	"普通教师固定桌椅",
	"普通教室活动桌椅",
	"多媒体教室",
	"语音室",
	"实验室",
	"机房",
	"绘图室",
	"舞蹈室",
	"美术设计教室"
};

#endif // !CONFIG_H