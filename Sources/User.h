#include "Schedule.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class User {

public :
	User(string user_name); // ���� ������

	string user_name; // ���� ��
	vector<Schedule> user_schd_list; // ������ ���� ���
};