#include "Schedule.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class User {

private:
	string user_name; // ���� ��

public :
	User(string user_name); // ���� ������
	vector<Schedule*> user_schd_list; // ������ ���� ���(������)

	string GetUserName();
	void AddSchedule(string schd_name, string schd_date);
};