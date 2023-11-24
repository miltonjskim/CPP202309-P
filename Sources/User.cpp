#include "User.h"

using namespace std;

User::User() {

}

// ���� ������
User::User(string user_name) {

	this->user_name = user_name;
}

// ���� ���� ��ȯ�ϴ� �Լ�
string User::GetUserName() {

	return this->user_name;
}

// ������ ������ ���� ��¥ ������ �����ϴ� �Լ� 
void User::SortSchedule() {

	sort(this->user_schd_list.begin(), this->user_schd_list.end());
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

// ������ ���� ��ġ ���� �Է� �Լ�
/* ������ ���� -> �� ���ο� �ϳ��� ������ ���� .txt ����
   �� ����(2��)�� ���� -> schedule_name
                          yyyy-mm-dd  */
void User::AddBatchSchedule(string route) {

	// ��� route�� ���� �б�
	wifstream ifs;
	ifs.imbue(locale(locale::empty(), new codecvt_utf8<wchar_t>));

	ifs.open(route);

	// ���Ͽ��� ���� ��� ��¥�� �о�� ���� ���� �� ��Ͽ� �߰�
	wstring schd_name;
	wstring schd_date;

	while (!ifs.eof()) {
		getline(ifs, schd_name);
		getline(ifs, schd_date);

		// wstring�� string���� ��ȯ
		wstring_convert<codecvt_utf8<wchar_t>, wchar_t> converter;
		string name_utf8 = converter.to_bytes(schd_name);
		string date_utf8 = converter.to_bytes(schd_date);

		Date date(date_utf8);
		Schedule* schedule = new Schedule(this->GetUserName(), name_utf8, date);
		this->user_schd_list.push_back(schedule);
	}
}

// ������ ����Ʈ ���·� ����ϴ� �Լ�
void User::PrintScheduleToList(User &user, Date start, Date end) {

	// ������ ���� ������ ����
	user.SortSchedule();

	// start���� end������ ��¥�� �����ϴ� ��� ������ ���
	for (int i = 0; i < user.user_schd_list.size(); i++) {
		if (user.user_schd_list[i]->schd_date > start || user.user_schd_list[i]->schd_date == start) {
			if (user.user_schd_list[i]->schd_date > end) {
				break;
			}

			int year = user.user_schd_list[i]->schd_date.year;
			int month = user.user_schd_list[i]->schd_date.month;
			int day = user.user_schd_list[i]->schd_date.day;
			string schd_name = user.user_schd_list[i]->schd_name;
			
			cout << year << "-" << month << "-" << day << " " << schd_name << endl;
		}
	}
}

void User::PrintScheduleToCalendar(User& user, int month) {

	// ������ ���� ������ ����
	user.SortSchedule();

	/*
	for (int i = 0; i < user.user_schd_list.size(); i++) {
		if(user.)
	}
	*/
}