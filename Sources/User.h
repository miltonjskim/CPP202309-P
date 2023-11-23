#include "Schedule.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

class User {

private:
	string user_name; // ���� ��

public :
	vector<Schedule*> user_schd_list; // ������ ���� ���(������)

	User(string user_name); // ���� ������

	string GetUserName(); // ���� ���� ��ȯ�ϴ� �Լ�

	void SortSchedule(); // ������ ������ ���� ��¥ ������ �����ϴ� �Լ�

	void AddSchedule(string schd_name, string schd_date); // ������ ���� �Է��ϴ� �Լ�
	// ��ƾ ������ �Է��ϴ� �Լ�
	void AddRoutineSchedule(string schd_name, string start_date, int interval, int count);
	// ������ ���� ��ġ ���� �Է� �Լ�
	void AddBatchSchedule(string route);

	void PrintMySchedule();
	void PrintMembersSchedule(User &user/*, Group group*/);
	void PrintScheduleToList(User &user, Date start, Date end); // ������ ����Ʈ ���·� ����ϴ� �Լ�
	void PrintScheduleToCalender(User &user, Date start, Date end);
};