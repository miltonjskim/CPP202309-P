#include "Schedule.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class User {

public :
	User(string user_name); // 유저 생성자

	string user_name; // 유저 명
	vector<Schedule> user_schd_list; // 유저의 일정 목록
};