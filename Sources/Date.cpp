#include "Date.h"

Date::Date() {

	this->year = 0;
	this->month = 0;
	this->day = 0;
}

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

	// 입력 문자열에서 월(year)만 추출해 멤버 변수에 저장
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