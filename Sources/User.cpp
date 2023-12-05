#include "User.h"

using namespace std;

User::User() {

}

// 유저 생성자
User::User(string user_name) {

	this->user_name = user_name;
}

// 유저 명을 반환하는 함수
string User::GetUserName() {

	return this->user_name;
}

// 유저의 일정을 빠른 날짜 순으로 정렬하는 함수 
void User::SortSchedule() {

	sort(this->user_schd_list.begin(), this->user_schd_list.end());
}

// 일정을 수동 입력하는 함수
void User::AddSchedule(string schd_name, string schd_date) {

	// Schedule 객체 생성 후 일정 목록에 추가
	string user_name = this->GetUserName();

	Date date = Date(schd_date);

	Schedule* schd = new Schedule(user_name, schd_name, date);
	this->user_schd_list.push_back(schd);
}

// 루틴 일정을 입력하는 함수
void User::AddRoutineSchedule(string schd_name, string start_date, int interval, int count) {

	string user_name = this->GetUserName();

	vector<Date*> date_list; // 루틴 일정들의 날짜 목록

	// 루틴이 시작되는 날
	Date* start = new Date(start_date);
	date_list.push_back(start);

	// 반복 횟수만큼 간격을 적용해 날짜 목록에 추가
	for (int i = 0; i < count - 1; i++) {
		start = date_list.back();
		Date* date = new Date(start->year, start->month, start->day + interval);
		date->Arrange();
		date_list.push_back(date);
	}

	// 날짜 목록을 참조해 일정을 생성해 일정 목록에 추가
	for (int i = 0; i < date_list.size(); i++) {
		this->user_schd_list.push_back(new Schedule(user_name, schd_name, *date_list[i]));
	}
}

// 파일을 통한 배치 일정 입력 함수
/* 파일의 형식 -> 두 라인에 하나의 일정을 갖는 .txt 파일
   각 라인(2줄)의 형식 -> schedule_name
                          yyyy-mm-dd  */
void User::AddBatchSchedule(string route) {

	// 경로 route의 파일 읽기
	wifstream ifs;
	ifs.imbue(locale(locale::empty(), new codecvt_utf8<wchar_t>));

	ifs.open(route);

	// 파일에서 일정 명과 날짜를 읽어와 일정 생성 및 목록에 추가
	wstring schd_name;
	wstring schd_date;

	while (!ifs.eof()) {
		getline(ifs, schd_name);
		getline(ifs, schd_date);

		// wstring을 string으로 변환
		wstring_convert<codecvt_utf8<wchar_t>, wchar_t> converter;
		string name_utf8 = converter.to_bytes(schd_name);
		string date_utf8 = converter.to_bytes(schd_date);

		Date date(date_utf8);
		Schedule* schedule = new Schedule(this->GetUserName(), name_utf8, date);
		this->user_schd_list.push_back(schedule);
	}
}

// 사용자가 지정한 날짜 범위 내 일정을 출력하는 함수
void User::PrintRangeSchedule(User &user) {

	string start;
	string end;
	cout << "일정을 표시할 시작일을 입력하세요(yyyy-mm-dd): ";
	cin >> start;
	cout << "일정을 표시할 종료일을 입력하세요(yyyy-mm-dd): ";
	cin >> end;

	Date start_date(start);
	Date end_date(end);

	cout << "일정을 출력합니다." << endl;
	user.PrintScheduleToList(user, start_date, end_date);
}

// 특정 달(월)의 일정을 출력하는 함수
void User::PrintMonthSchedule(User& user) {

	int month;
	cout << "일정을 표시할 달을 입력하세요: ";
	cin >> month;

	int days_in_month;	
	// month에 해당하는 일 수 설정
	switch (month) {
	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		days_in_month = 31;
		break;
	case 4: case 6: case 9: case 11:
		days_in_month = 30;
		break;
	case 2: // 윤년은 고려하지 않음.
		days_in_month = 28;
		break;
	default:
		break;
	}

	Date start_date(2023, month, 1);
	Date end_date(2023, month, days_in_month);

	user.PrintScheduleToList(user, start_date, end_date);
}

// 특정 주의 일정을 출력하는 함수
void User::PrintWeekSchedule(User& user) {

	string day;
	cout << "일정을 표시할 주의 시작일을 입력하세요(yyyy-mm-dd): ";
	cin >> day;

	Date start_date(day);
	Date end_date = start_date + 6;

	user.PrintScheduleToList(user, start_date, end_date);
}

// 특정 일의 일정을 출력하는 함수
void User::PrintDaySchedule(User& user) {

	string day;
	cout << "일정을 표시할 날짜를 입력하세요(yyyy-mm-dd): ";
	cin >> day;

	Date date(day);

	user.PrintScheduleToList(user, date, date);
}

// 일정을 리스트 형태로 출력하는 함수
void User::PrintScheduleToList(User &user, Date start, Date end) {

	// 일정을 빠른 순으로 정렬
	user.SortSchedule();

	// start부터 end까지의 날짜에 존재하는 모든 일정을 출력
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

	// 일정을 빠른 순으로 정렬
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
		cout << days[i] << "  "; // 공백 2
	}
	cout << endl;
	cout << "==============================" << endl; // 30칸
}