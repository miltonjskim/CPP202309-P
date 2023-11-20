#include "Schedule.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class User {

private:
	string user_name; // 유저 명

public :
	User(string user_name); // 유저 생성자
	vector<Schedule*> user_schd_list; // 유저의 일정 목록(포인터)

	string GetUserName();
	void AddSchedule(string schd_name, string schd_date);
};