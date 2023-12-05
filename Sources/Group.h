#include "User.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Group {

public :
	string group_name; // 그룹 명
	vector<User*> member_list; // 멤버 목록

	Group();
	Group(string group_name);
};
