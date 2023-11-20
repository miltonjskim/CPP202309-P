#include "User.h"

using namespace std;

User::User(string user_name) {

	this->user_name = user_name;
}

string User::GetUserName() {

	return this->user_name;
}

void User::AddSchedule(string schd_name, string schd_date) {

	string user_name = this->GetUserName();

	Schedule* schd = new Schedule(user_name, schd_name, schd_date);
	this->user_schd_list.push_back(schd);
}