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

	Date date = Date(start_date);

	/* TODO: count번 interval만큼의 간격으로 일정 생성하는 로직
	for (int i = 0; i < count; i++) {
		
		Schedule* schd = new Schedule(user_name, schd_name, start_date + )
	}
	*/
}
