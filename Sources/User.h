#pragma once
#include "Schedule.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <locale>
#include <codecvt>

using namespace std;

class User {

private:
	string user_name; // ���� ��

public :
	vector<Schedule*> user_schd_list; // ������ ���� ���(������)

	User();
	User(string user_name); // ���� ������

	string GetUserName(); // ���� ���� ��ȯ�ϴ� �Լ�

	void SortSchedule(); // ������ ������ ���� ��¥ ������ �����ϴ� �Լ�

	void AddSchedule(string schd_name, string schd_date); // ������ ���� �Է��ϴ� �Լ�
	// ��ƾ ������ �Է��ϴ� �Լ�
	void AddRoutineSchedule(string schd_name, string start_date, int interval, int count);
	// ������ ���� ��ġ ���� �Է� �Լ�
	void AddBatchSchedule(string route);

	/* ������ ���ڷ� �ѱ��, ���� -> ������ ������ ���� ȣ��
	   (Range|Month|Week|Day) -> (List|Calendar) */
	void PrintSchedule(User &user); // ������ ������ ������ ����ϴ� �Լ�

	void PrintRangeSchedule(User &user); // ����ڰ� ������ ��¥ ���� �� ������ ����ϴ� �Լ�
	void PrintMonthSchedule(User &user); // Ư�� ��(��)�� ������ ����ϴ� �Լ�
	void PrintWeekSchedule(User &user); // Ư�� ���� ������ ����ϴ� �Լ�
	void PrintDaySchedule(User &user); // Ư�� ���� ������ ����ϴ� �Լ�

	void PrintScheduleToList(User &user, Date start, Date end); // ������ ����Ʈ ���·� ����ϴ� �Լ�
	void PrintScheduleToCalendar(User &user, int month); // ������ �� ������ �޷� ���·� ����ϴ� �Լ�
};