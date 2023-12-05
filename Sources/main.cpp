#include <iostream>
#include "Group.h"

using namespace std;

int main() {

	string input; // 입력된 명령어를 저장
	User* current_user = nullptr; // 현재 사용중인 유저
	Group* current_group = nullptr; // 현재 사용중인 유저가 속한 그룹
	vector<User*> user_list; // 생성된 유저들의 목록
	vector<Group*> group_list; // 생성된 그룹들의 목록

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
			
			cout << "그룹에 가입하시겠습니까?(y/n): ";
			cin >> input;
			if (input == "y") {
				string group_name;
				cout << "가입 또는 생성할 그룹의 이름을 입력하세요: ";
				cin >> group_name;
				for (int i = 0; i < group_list.size(); i++) {
					// 이미 존재하는 그룹이면 가입
					if (group_list[i]->group_name == group_name) {
						group_list[i]->member_list.push_back(current_user);
						cout << "그룹에 가입되었습니다." << endl;
						current_group = group_list[i];
						break;
					}
					// 존재하지 않는 그룹이면 생성 후 가입
					if (i == group_list.size() - 1) {
						group_list.push_back(new Group(group_name));
						cout << "그룹이 생성되었습니다." << endl;
						group_list[group_list.size() - 1]->member_list.push_back(current_user);
						cout << "그룹에 가입되었습니다." << endl;
						current_group = group_list[group_list.size() - 1];
						break;
					}
				}
			}
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
					string members_name;
					cout << "일정을 볼 대상 멤버의 이름을 입력하세요: ";
					cin >> members_name;

					for (int i = 0; i < current_group->member_list.size(); i++) {
						// 입력한 멤버가 존재
						if (current_group->member_list[i]->GetUserName() == members_name) {
							current_user->PrintMembersSchedule(*current_group->member_list[i]);
							break;
						}
						// 입력한 멤버가 없음
						if (i == current_group->member_list.size() - 1) {
							cout << "입력한 멤버가 그룹에 존재하지 않습니다.";
						}
					}
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
					cout << "사용자가 전환되었습니다!" << endl;
					// 전환된 사용자가 그룹이 있는지 확인
					current_group = nullptr;
					for (int i = 0; i < group_list.size(); i++) {
						for (int j = 0; j < group_list[i]->member_list.size(); j++) {
							if (current_user->GetUserName() == group_list[i]->member_list[j]->GetUserName()) {
								current_group = group_list[i];
								break;
							}
						}
						if (current_group != nullptr) {
							break;
						}
					}
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