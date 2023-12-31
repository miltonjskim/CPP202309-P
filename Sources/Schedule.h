#pragma once
#include "Date.h"
#include <iostream>
#include <string>

using namespace std;

class Schedule {

public :
	string user_name; // 일정 소유자
	string schd_name; // 일정 명
	Date schd_date; // 일정 날짜

	Schedule();

	Schedule(string user, string schd_name, Date schd_date);

	// 비교 연산자 오버라이딩
	bool operator < (const Schedule& schd);
	bool operator > (const Schedule& schd);
	bool operator == (const Schedule& schd);
};