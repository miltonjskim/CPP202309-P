#include <iostream>
#include "Group.h"

using namespace std;

int main() {

	string input; // 입력된 명령어를 저장
	User* current_user = nullptr; // 현재 사용중인 유저
	vector<User*> user_list; // 생성된 유저들의 목록

	while (true) {

		// 최초 실행 시 사용자 생성
		if (current_user == nullptr) {
			cout << "사용자를 생성합니다." << endl;
			string user_name; // 생성할 사용자 명
			cout << "이름을 입력하세요: ";
			cin >> user_name;
			current_user = new User(user_name);
			user_list.push_back(current_user);
			cout << "사용자가 생성되었습니다. ";
			cout << current_user->GetUserName() << "님, 환영합니다." << endl;
			// TODO: 그룹에 가입
		}

		// 명령어 입력
		cout << "명령어를 입력하세요(일정추가|일정보기|사용자전환|종료): ";
		cin >> input;

		// 일정 추가
		if (input == "일정추가") {
			string option;
			while (true) {
				cout << "일정을 추가합니다. 옵션을 입력하세요(수동|루틴|파일): ";
				cin >> option;
				// 수동 입력
				if (option == "수동") {
					string schd_name;
					string schd_date;
					cout << "수동으로 일정을 추가합니다." << endl;
					cout << "일정 명: ";
					cin >> schd_name;
					cout << "일정 날짜(yyyy-mm-dd): ";
					cin >> schd_date;

					current_user->AddSchedule(schd_name, schd_date);
					cout << "일정이 추가되었습니다!" << endl;

					break;
				}
				// 루틴 입력
				else if (option == "루틴") {
					string schd_name;
					string start_date;
					int interval;
					int count;
					cout << "루틴 일정을 추가합니다." << endl;
					cout << "일정 명: ";
					cin >> schd_name;
					cout << "루틴 시작 날짜(yyyy-mm-dd): ";
					cin >> start_date;
					cout << "루틴 날짜 간격: ";
					cin >> interval;
					cout << "반복 횟수: ";
					cin >> count;

					current_user->AddRoutineSchedule(schd_name, start_date, interval, count);
					cout << "루틴 일정이 추가되었습니다!" << endl;

					break;
				}
				// 배치 입력
				else if (option == "파일") {
					string route;

					cout << "파일을 통해 일정을 추가합니다." << endl;
					cout << "파일 경로: ";
					cin >> route;

					current_user->AddBatchSchedule(route);
					cout << "일정이 추가되었습니다!" << endl;

					break;
				}
				else {
					cout << "잘못된 옵션입니다. 다시 입력해주세요." << endl;
					continue;
				}
			}
		}
		// 일정 보기
		else if (input == "일정보기") {
			string option;
			while (true) {
				cout << "누구의 일정을 보시겠습니까?(나|멤버): ";
				cin >> option;
				if (option == "나") {
					string start;
					string end;
					cout << "일정을 표시할 시작일을 입력하세요(yyyy-mm-dd): ";
					cin >> start;
					cout << "일정을 표시할 종료일을 입력하세요(yyyy-mm-dd): ";
					cin >> end;
					 
					Date start_date(start);
					Date end_date(end);

					cout << "일정을 출력합니다." << endl;
					current_user->PrintScheduleToList(*current_user, start_date, end_date);

					break;
				}
				else if (option == "멤버") {
					// TODO: 멤버를 선택하고 그룹에 있는지 체크 후 일정을 보여주는 로직
				}
				else {
					cout << "잘못된 옵션입니다. 다시 입력해주세요." << endl;
					continue;
				}
			}
			
		} 
		// 사용자 전환
		else if (input == "사용자전환") {
			string name;
			cout << "전환할 사용자의 이름을 입력하세요: ";
			cin >> name;
			for (int i = 0; i < user_list.size(); i++) {
				// 일치하는 사용자를 찾았다면 사용자 전환
				if (user_list[i]->GetUserName() == name) {
					current_user = user_list[i];
					break;
				}
				if (i == user_list.size() - 1) {
					cout << "일치하는 사용자가 없습니다." << endl;
					string add_user;
					cout << "사용자를 생성하시겠습니까?(y/n): ";
					cin >> add_user;
					// 입력한 이름으로 사용자 신규 생성
					if (add_user == "y") {
						current_user = new User(name);
						user_list.push_back(current_user);
						// TODO: 그룹에 가입
					}
				}
			}
		}
		else if (input == "종료") {
			cout << "프로그램을 종료합니다...";
			break;
		}
		else {
			cout << "잘못된 명령어입니다. 다시 입력해주세요." << endl;
			continue;
		}
	}

	return 0;
}