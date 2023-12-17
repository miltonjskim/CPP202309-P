#pragma once
#include "Date.h"
#include <iostream>
#include <string>

using namespace std;

class Schedule {

public :
	string user_name; // ���� ������
	string schd_name; // ���� ��
	Date schd_date; // ���� ��¥

	Schedule();

	Schedule(string user, string schd_name, Date schd_date);

	// �� ������ �������̵�
	bool operator < (const Schedule& schd);
	bool operator > (const Schedule& schd);
	bool operator == (const Schedule& schd);
};