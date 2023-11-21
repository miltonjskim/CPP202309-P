#include "Date.h"

Date::Date() {

	this->year = 0;
	this->month = 0;
	this->day = 0;
}

Date::Date(string schd_date) {

	string buf = ""; // ���ڿ� �ӽ� ���� ����
	
	// �Է� ���ڿ����� ��(year)�� ������ ��� ������ ����
	while (true) {
		if (schd_date[0] == '-') {
			schd_date.erase(schd_date.begin());
			break;
		}
		buf += schd_date[0];
		schd_date.erase(schd_date.begin());
	}
	this->year = stoi(buf);

	// �Է� ���ڿ����� ��(year)�� ������ ��� ������ ����
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