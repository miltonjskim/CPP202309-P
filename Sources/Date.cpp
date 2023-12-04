#include "Date.h"

// 기본 생성자
Date::Date() {

	this->year = 2023;
	this->month = 1;
	this->day = 1;
}

// 문자열을 입력받는 생성자
// 입력 형식 -> yyyy-mm-dd
Date::Date(string schd_date) {

	string buf = ""; // 문자열 임시 저장 변수
	
	// 입력 문자열에서 년(year)만 추출해 멤버 변수에 저장
	while (true) {
		if (schd_date[0] == '-') {
			schd_date.erase(schd_date.begin());
			break;
		}
		buf += schd_date[0];
		schd_date.erase(schd_date.begin());
	}
	this->year = stoi(buf);

	// 입력 문자열에서 월(month)만 추출해 멤버 변수에 저장
	buf = "";
	while (true) {
		if (schd_date[0] == '-') {
			schd_date.erase(schd_date.begin());
			break;
		}
		buf += schd_date[0];
		schd_date.erase(schd_date.begin());
	}
	this->month = stoi(buf);

	// 입력 문자열에서 일(day)만 추출해 멤버 변수에 저장
	buf = "";
	while (true) {
		buf += schd_date[0];
		schd_date.erase(schd_date.begin());
		if (schd_date.empty()) {
			break;
		}
	}
	this->day = stoi(buf);
}

// 연, 월, 일을 직접 주입하는 생성자
Date::Date(int year, int month, int day) {

	this->year = year;
	this->month = month;
	this->day = day;
}

// Date 클래스 연산자 오버라이딩
bool Date::operator<(const Date& date) const {
	if (this->year != date.year) {
		return this->year < date.year;
	}
	if (this->month != date.month) {
		return this->month < date.month;
	}
	return this->day < date.day;
}

bool Date::operator>(const Date& date) const {
	if (this->year != date.year) {
		return this->year > date.year;
	}
	if (this->month != date.month) {
		return this->month > date.month;
	}
	return this->day > date.day;
}

bool Date::operator==(const Date& date) const {
	return this->year == date.year && this->month == date.month && this->day == date.day;
}

Date Date::operator+(int day_to_add) {

	int added_day = this->day + day_to_add;
	Date added_date(this->year, this->month, added_day);
	Arrange();

	return added_date;
}


// 초과한 날짜를 정리해 다음 연/월로 넘겨주는 함수
void Date::Arrange() {

	int days_in_month = 0; // 해당 월의 일 수

	// month에 해당하는 일 수 설정
	switch (this->month) {
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

	// 날짜 정리
	if (this->day > days_in_month) {
		this->month++;
		this->day -= days_in_month;
	}
	if (this->month > 12) {
		this->month -= 12;
		this->year++;
	}
}