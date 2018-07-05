
#include "stdafx.h"

//课时时间类
ostream& operator<< (ostream &out, const classTime &rhs)
{
	//out << "(" << rhs.classWeek << " " << rhs.week << " " << rhs.section << ")";
	out << "第" << rhs.classWeek << "周周" << rhs.week << "第" << rhs.section << "大节";
	return out;
}

bool operator== (const classTime &lhs, const classTime &rhs)
{
	if (lhs.classWeek == rhs.classWeek && lhs.week == rhs.week && lhs.section == rhs.section)
		return 1;
	return 0;
}

bool operator!= (const classTime &lhs, const classTime &rhs) { return !(lhs == rhs); }

//预约信息类
ostream& operator<< (ostream &out, const OrderInfo &rhs)
{
	out << " ";
	out << rhs.m_time.classWeek << " " << rhs.m_time.week 
		<< " " << rhs.m_time.section << " "
		<< rhs.m_ID << " " << rhs.m_name << " "
		<< rhs.m_phoneNum;
	return out;
}

classTime OrderInfo::getClassTime() const{ return m_time; }
string OrderInfo::getID() const { return m_ID;  }
string OrderInfo::getName() const{ return m_name; }
string OrderInfo::getPhoneNum() const { return m_phoneNum;  }


//当前教室上课信息类
ostream& operator<< (ostream &out, const ClassInfo &rhs)
{
	out << " ";
	out << rhs.m_teacherName << " " << rhs.m_teacherID << " "
		<< rhs.m_sumClassCnt;
	for (uint i = 0; i < rhs.m_sumClassCnt; i++) {
		out << " ";
		out << rhs.m_classTime[i].classWeek << " " << rhs.m_classTime[i].week << " "
			<< rhs.m_classTime[i].section;
	}
	return out;
}

string ClassInfo::getName() const { return m_teacherName;  }
string ClassInfo::getID() const { return m_teacherID;  }
uint ClassInfo::getSumClassCnt() const { return m_sumClassCnt;  }
vector<classTime> ClassInfo::getClassTime() const { return m_classTime;  }

//Classroom Class
void Classroom::setCampusType(uint campusType)
{
	if (campusType >= 1  && campusType <= CAMPUSCNT)
		m_campusType = campusType;
}

void Classroom::setBuildID(uint buildID)
{
	m_buildID = buildID;
}

void Classroom::setRoomID(uint roomID)
{
	m_roomID = roomID;
}

void Classroom::setRoomType(uint roomType)
{
	if (roomType >= 1 && roomType <= CLASSROOMTYPECNT)
		m_roomType = roomType;
}

void Classroom::setSeats(uint seats)
{
	if (seats >= 0)
		m_seats = seats;
}

void Classroom::setOrderStatus(uint status)
{
	if (status)
		m_orderStatus = 1;
	else
		m_orderStatus = 0;
}

void Classroom::setOrderCnt(uint cnt)
{
	if (cnt >= 0)
		m_orderCnt = cnt;
}

void Classroom::setClassCnt(uint cnt)
{
	if (cnt >= 0)
		m_classCnt = cnt;
}

void Classroom::addOrderInfo(OrderInfo info)
{
	m_orderStatus = 1;
	m_orderCnt++;
	m_orderInfo.push_back(info);
}

void Classroom::addClassInfo(ClassInfo info)
{
	m_classCnt++;
	m_classInfo.push_back(info);
}

uint Classroom::getCampusType() const { return m_campusType; }

uint Classroom::getBuildID() const { return m_buildID;  }

uint Classroom::getRoomID() const { return m_roomID;  }

uint Classroom::getRoomType() const { return m_roomType;  }

uint Classroom::getSeats() const { return m_seats;  }

uint Classroom::getOrderStatus() const { return m_orderStatus;  }

uint Classroom::getOrderCnt() const { return m_orderCnt; }

uint Classroom::getClassCnt() const { return m_classCnt;  }

vector <OrderInfo> Classroom::getOrderInfo() const { return m_orderInfo;  }

vector <ClassInfo> Classroom::getClassInfo() const { return m_classInfo;  }