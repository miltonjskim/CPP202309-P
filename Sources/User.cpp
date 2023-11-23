#include "User.h"

using namespace std;

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
	ifstream ifs;
	ifs.open(route);

	// 파일에서 일정 명과 날짜를 읽어와 일정 생성 및 목록에 추가
	string schd_name;
	string schd_date;

	while (!ifs.eof()) {
		getline(ifs, schd_name);
		getline(ifs, schd_date);

		Date date(schd_date);
		Schedule* schedule = new Schedule(this->GetUserName(), schd_name, date);
		this->user_schd_list.push_back(schedule);
	}
}

// 일정을 리스트 형태로 출력하는 함수
void User::PrintScheduleToList(User &user, Date start, Date end) {

	user.SortSchedule();
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