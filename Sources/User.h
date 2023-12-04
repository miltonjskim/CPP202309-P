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
	string user_name; // 유저 명

public :
	vector<Schedule*> user_schd_list; // 유저의 일정 목록(포인터)

	User();
	User(string user_name); // 유저 생성자

	string GetUserName(); // 유저 명을 반환하는 함수

	void SortSchedule(); // 유저의 일정을 빠른 날짜 순으로 정렬하는 함수

	void AddSchedule(string schd_name, string schd_date); // 일정을 수동 입력하는 함수
	// 루틴 일정을 입력하는 함수
	void AddRoutineSchedule(string schd_name, string start_date, int interval, int count);
	// 파일을 통한 배치 일정 입력 함수
	void AddBatchSchedule(string route);

	/* 유저 -> 범위 -> 형태의 순으로 내부 호출하는 형태로 리팩토링할 것임.
	   (My|Members) -> (Range|Month|Week|Day) -> (List|Calendar) */
	void PrintMySchedule(); // 나의 일정을 출력하는 함수
	void PrintMembersSchedule(User &user/*, Group group*/); // 멤버의 일정을 출력하는 함수

	void PrintRangeSchedule(User &user); // 사용자가 지정한 날짜 범위 내 일정을 출력하는 함수
	void PrintMonthSchedule(User &user); // 특정 달(월)의 일정을 출력하는 함수
	void PrintWeekSchedule(User &user); // 특정 주의 일정을 출력하는 함수
	void PrintDaySchedule(User &user); // 특정 일의 일정을 출력하는 함수

	void PrintScheduleToList(User &user, Date start, Date end); // 일정을 리스트 형태로 출력하는 함수
	void PrintScheduleToCalendar(User &user, int month); // 일정을 월 단위로 달력 형태로 출력하는 함수
};