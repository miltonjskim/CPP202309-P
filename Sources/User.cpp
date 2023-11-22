#include "User.h"

using namespace std;

// ���� ������
User::User(string user_name) {

	this->user_name = user_name;
}

// ���� ���� ��ȯ�ϴ� �Լ�
string User::GetUserName() {

	return this->user_name;
}

// ������ ���� �Է��ϴ� �Լ�
void User::AddSchedule(string schd_name, string schd_date) {

	// Schedule ��ü ���� �� ���� ��Ͽ� �߰�
	string user_name = this->GetUserName();

	Date date = Date(schd_date);

	Schedule* schd = new Schedule(user_name, schd_name, date);
	this->user_schd_list.push_back(schd);
}

// ��ƾ ������ �Է��ϴ� �Լ�
void User::AddRoutineSchedule(string schd_name, string start_date, int interval, int count) {

	string user_name = this->GetUserName();

	vector<Date*> date_list; // ��ƾ �������� ��¥ ���

	// ��ƾ�� ���۵Ǵ� ��
	Date* start = new Date(start_date);
	date_list.push_back(start);

	// �ݺ� Ƚ����ŭ ������ ������ ��¥ ��Ͽ� �߰�
	for (int i = 0; i < count - 1; i++) {
		start = date_list.back();
		Date* date = new Date(start->year, start->month, start->day + interval);
		date->Arrange();
		date_list.push_back(date);
	}

	// ��¥ ����� ������ ������ ������ ���� ��Ͽ� �߰�
	for (int i = 0; i < date_list.size(); i++) {
		this->user_schd_list.push_back(new Schedule(user_name, schd_name, *date_list[i]));
	}
}
