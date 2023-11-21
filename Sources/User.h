#include "Schedule.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class User {

private:
	string user_name; // 유저 명

public :
	vector<Schedule*> user_schd_list; // 유저의 일정 목록(포인터)

	User(string user_name); // 유저 생성자

	string GetUserName(); // 유저 명을 반환하는 함수
	void AddSchedule(string schd_name, string schd_date); // 일정을 수동 입력하는 함수
	// 루틴 일정을 입력하는 함수
	void AddRoutineSchedule(string schd_name, string start_date, int interval, int count);
};