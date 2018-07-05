#ifndef CLASSROOM_H
#define CLASSROOM_H

#define CAMPUSCNT 3
#define CLASSROOMTYPECNT 11
#define ONEBUILDMAXROOMS 500
#define CLASSWEEKCNT 20
#define ONEDAYCLASSCNT 6
#define BUILDCNT 50

const string CAMPUSTYPE[4]= {"", "莲花街校区", "嵩山路校区", "中原路校区" };
 
const string CLASSROOMTYPE[12] = {
	"",
	"多媒体教室",
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

#define uint unsigned int

//课时时间类
struct classTime
{
	friend ostream& operator<< (ostream &, const classTime &);
	friend bool operator== (const classTime &, const classTime &);
	friend bool operator!= (const classTime &, const classTime &);
	classTime() = default;
	classTime(uint c, uint w, uint s) : classWeek(c), week(w), section(s) { }
	uint classWeek = 0;
	uint week = 0;
	uint section = 0;
	void display() const {
		cout << "(" << classWeek << " " << week << " " << section << ")";
		//cout << "第" << classWeek << "周周" << week << "第" << section << "大节";
	}
};

//预约信息类
class OrderInfo
{
	friend ostream& operator<< (ostream &, const OrderInfo&);
public:
	OrderInfo() = default;
	OrderInfo(const classTime &time, const string &ID,
		const string &name, const string &phoneNum) : m_time(time),
		m_ID(ID), m_name(name), m_phoneNum(phoneNum) { }

	string getID() const;
	classTime getClassTime() const;
	string getName() const;
	string getPhoneNum() const;

private:
	classTime m_time;
	string m_ID = "";
	string m_name = "";
	string m_phoneNum = "";
};

//当前教室上课信息类
class ClassInfo
{
	friend ostream& operator<< (ostream &, const ClassInfo &);
public:
	ClassInfo() = default;
	ClassInfo(const string &teacherName, const string &teacherID, uint sumClassCnt, vector< classTime > &classTime)
		: m_teacherName(teacherName), m_teacherID(teacherID), m_sumClassCnt(sumClassCnt),  m_classTime(classTime) {}

	string getName() const;
	string getID() const;
	uint getSumClassCnt() const;
	vector<classTime> getClassTime() const;

private:
	string m_teacherName = "";
	string m_teacherID = "";
	uint m_sumClassCnt = 0;
	vector< classTime > m_classTime;  //三元组 （课时周，周，节）
};



//教室信息类
class Classroom
{
public:
	Classroom() = default;  //默认构造函数

	void setCampusType(uint);  //设置函数
	void setBuildID(uint);
	void setRoomID(uint);
	void setRoomType(uint);
	void setSeats(uint);
	void setOrderStatus(uint);
	void setOrderCnt(uint);
	void setClassCnt(uint);
	void addOrderInfo(OrderInfo);
	void addClassInfo(ClassInfo);

	uint getCampusType() const;  //获取函数
	uint getBuildID() const;
	uint getRoomID() const;
	uint getRoomType() const;
	uint getSeats() const;
	uint getOrderStatus() const;
	uint getOrderCnt() const;
	uint getClassCnt() const;
	vector <OrderInfo> getOrderInfo() const;
	vector <ClassInfo> getClassInfo() const;

private:
	uint m_campusType = 0;  //校区
	uint m_buildID = 0;  //楼号
	uint m_roomID = 0;  //教室号
	uint m_roomType = 0;  //教室类型
	uint m_seats = 0;  //座位数
	uint m_orderStatus = 0;  //预约状态
	uint m_orderCnt = 0;  //预约数
	uint m_classCnt = 0;  //课堂数
	vector <OrderInfo> m_orderInfo;  //预约信息数组
	vector <ClassInfo> m_classInfo;  //课堂信息数组
};

#endif