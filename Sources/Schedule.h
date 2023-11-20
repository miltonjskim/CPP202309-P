#include <iostream>
#include <string>

using namespace std;

class Schedule {

public :
	string user_name; // 일정 소유자
	string schd_name; // 일정 명
	string schd_date; // 일정 시간

	Schedule(string user, string schd_name, string schd_date);
};