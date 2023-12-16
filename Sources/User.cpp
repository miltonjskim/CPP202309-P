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
	ifstream is;
	is.open(route);

	// ���Ͽ��� ���� ��� ��¥�� �о�� ���� ���� �� ��Ͽ� �߰�
	string schd_name;
	string schd_date;

	while (is >> schd_name >> schd_date) {

		Date date(schd_date);
		Schedule* schedule = new Schedule(this->GetUserName(), schd_name, date);
		this->user_schd_list.push_back(schedule);
	}
}

// ������ ����ϴ� �Լ�
void User::PrintSchedule(User& user) {

	while (true) {

		string option; // ���� ��� ���� �ɼ�
		cout << "���� �ɼ��� �����ϼ���(��|��|��|������Է�): ";
		cin >> option;

		if (option == "��") {
			PrintMonthSchedule(user);
			break;
		}
		else if (option == "��") {
			PrintWeekSchedule(user);
			break;
		}
		else if (option == "��") {
			PrintDaySchedule(user);
			break;
		}
		else if (option == "������Է�") {
			PrintRangeSchedule(user);
			break;
		}
		else {
			cout << "�߸��� �Է��Դϴ�. �ٽ� �Է��ϼ���." << endl;
			continue;
		}
	}
}

// ����ڰ� ������ ��¥ ���� �� ������ ����ϴ� �Լ�
void User::PrintRangeSchedule(User &user) {

	string start;
	string end;
	cout << "������ ǥ���� �������� �Է��ϼ���(yyyy-mm-dd): ";
	cin >> start;
	cout << "������ ǥ���� �������� �Է��ϼ���(yyyy-mm-dd): ";
	cin >> end;

	Date start_date(start);
	Date end_date(end);

	cout << "������ ����մϴ�." << endl;
	user.PrintScheduleToList(user, start_date, end_date);
}

// Ư�� ��(��)�� ������ ����ϴ� �Լ�
void User::PrintMonthSchedule(User& user) {

	int month;
	cout << "������ ǥ���� ���� �Է��ϼ���: ";
	cin >> month;

	int days_in_month;	
	// month�� �ش��ϴ� �� �� ����
	switch (month) {
	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		days_in_month = 31;
		break;
	case 4: case 6: case 9: case 11:
		days_in_month = 30;
		break;
	case 2: // ������ ������� ����.
		days_in_month = 28;
		break;
	default:
		break;
	}

	Date start_date(2023, month, 1);
	Date end_date(2023, month, days_in_month);

	user.PrintScheduleToList(user, start_date, end_date);
}

// Ư�� ���� ������ ����ϴ� �Լ�
void User::PrintWeekSchedule(User& user) {

	string day;
	cout << "������ ǥ���� ���� �������� �Է��ϼ���(yyyy-mm-dd): ";
	cin >> day;

	Date start_date(day);
	Date end_date = start_date + 6;

	user.PrintScheduleToList(user, start_date, end_date);
}

// Ư�� ���� ������ ����ϴ� �Լ�
void User::PrintDaySchedule(User& user) {

	string day;
	cout << "������ ǥ���� ��¥�� �Է��ϼ���(yyyy-mm-dd): ";
	cin >> day;

	Date date(day);

	user.PrintScheduleToList(user, date, date);
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

	vector<string> days;
	days.push_back("SUN");
	days.push_back("MON");
	days.push_back("TUE");
	days.push_back("WED");
	days.push_back("THU");
	days.push_back("FRI");
	days.push_back("SAT");

	for (int i = 0; i < days.size(); i++) {
		cout << days[i] << "  "; // ���� 2
	}
	cout << endl;
	cout << "==============================" << endl; // 30ĭ
}