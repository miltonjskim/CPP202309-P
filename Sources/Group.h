#include "User.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Group {

public :
	string group_name; // �׷� ��
	vector<User*> member_list; // ��� ���

	Group();
	Group(string group_name);
};
