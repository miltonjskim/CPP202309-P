#include "Date.h"

// �⺻ ������
Date::Date() {

	this->year = 2023;
	this->month = 1;
	this->day = 1;
}

// ���ڿ��� �Է¹޴� ������
// �Է� ���� -> yyyy-mm-dd
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

	// �Է� ���ڿ����� ��(month)�� ������ ��� ������ ����
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

	// �Է� ���ڿ����� ��(day)�� ������ ��� ������ ����
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

// ��, ��, ���� ���� �����ϴ� ������
Date::Date(int year, int month, int day) {

	this->year = year;
	this->month = month;
	this->day = day;
}

// Date Ŭ���� ������ �������̵�
bool Date::operator < (const Date& date) {
	if (this->year != date.year) {
		return this->year < date.year;
	}
	else {
		if (this->month != date.month) {
			return this->month < date.month;
		}
		else {
			if (this->day != date.day) {
				return this->day < date.day;
			}
			else {
				return false;
			}
		}
	}
}

bool Date::operator > (const Date& date) {
	if (this->year != date.year) {
		return this->year > date.year;
	}
	else {
		if (this->month != date.month) {
			return this->month > date.month;
		}
		else {
			if (this->day != date.day) {
				return this->day > date.day;
			}
			else {
				return false;
			}
		}
	}
}

bool Date::operator == (const Date& date) {
	if (this->year != date.year) {
		return false;
	}
	else {
		if (this->month != date.month) {
			return false;
		}
		else {
			if (this->day != date.day) {
				return false;
			}
			else {
				return true;
			}
		}
	}

}

// �ʰ��� ��¥�� ������ ���� ��/���� �Ѱ��ִ� �Լ�
void Date::Arrange() {

	int days_in_month = 0; // �ش� ���� �� ��

	// month�� �ش��ϴ� �� �� ����
	switch (this->month) {
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

	// ��¥ ����
	if (this->day > days_in_month) {
		this->month++;
		this->day -= days_in_month;
	}
	if (this->month > 12) {
		this->month -= 12;
		this->year++;
	}
}