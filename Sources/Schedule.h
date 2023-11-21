#include "Date.h"
#include <iostream>
#include <string>

using namespace std;

class Schedule {

public :
	string user_name; // 일정 소유자
	string schd_name; // 일정 명
	Date schd_date; // 일정 날짜

	Schedule(string user, string schd_name, Date schd_date);
};