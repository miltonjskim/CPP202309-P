#include <iostream>
#include "Group.h"
#include "User.h"

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
			
			string group_option;
			cout << "그룹에 가입하시겠습니까?(y/n): ";
			cin >> group_option;
			if (group_option == "y") {
				string group_name;
				cout << "가입 또는 생성할 그룹의 이름을 입력하세요: ";
				cin >> group_name;
				// 그룹 생성
				group_list.push_back(new Group(group_name));
				cout << "그룹이 생성되었습니다." << endl;
				// 그룹 가입
				group_list[group_list.size() - 1]->member_list.push_back(current_user);
				cout << "그룹에 가입되었습니다." << endl;
				current_group = group_list[group_list.size() - 1];
			}
		}

		// 명령어 입력
		cout << "명령어를 입력하세요(일정추가|일정동참|일정보기|멤버조회|사용자전환|종료): ";
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
					cout << "주의: txt파일의 인코딩 방식은 ANSI여야 합니다!" << endl;
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
		// 일정 동참
		else if (input == "일정동참") {
			if (current_group == nullptr) {
				cout << "가입된 그룹이 없습니다!" << endl;
			}
			else {
				string members_name; // 대상 멤버의 이믈
				cout << "일정에 동참하고 싶은 멤버의 이름을 입력하세요: ";
				cin >> members_name;
				for (int i = 0; i < current_group->member_list.size(); i++) {
					if (current_group->member_list[i]->GetUserName() == members_name) {
						User* member = current_group->member_list[i];
						// 일정 날짜 입력
						string date;
						cout << "동참하고 싶은 일정의 날짜를 입력하세요(yyyy-mm-dd): ";
						cin >> date;
						Date schd_date(date);
						cout << "해당 날짜의 멤버의 일정은 아래와 같습니다." << endl;
						member->PrintScheduleToList(*member, schd_date, schd_date);
						
						// 일정 이름 입력
						string schd_name;
						cout << "동참하고 싶은 일정의 이름을 입력하세요: ";
						cin >> schd_name;
						// 일정 동참
						current_user->JoinShedule(*member, schd_date, schd_name);
						break;
					}
					if (i == current_group->member_list.size() - 1) {
						cout << "입력한 멤버가 존재하지 않습니다." << endl;
					}
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

					current_user->PrintSchedule(*current_user);
					break;
				}
				else if (option == "멤버") {

					string members_name;
					cout << "일정을 볼 대상 멤버의 이름을 입력하세요: ";
					cin >> members_name;

					if (current_group != nullptr) {
						for (int i = 0; i < current_group->member_list.size(); i++) {
							// 입력한 멤버가 존재
							if (current_group->member_list[i]->GetUserName() == members_name) {
								current_user->PrintSchedule(*current_group->member_list[i]);
								break;
							}
							// 입력한 멤버가 없음
							if (i == current_group->member_list.size() - 1) {
								cout << "입력한 멤버가 그룹에 존재하지 않습니다." << endl;
								break;
							}
						}
						break;
					}
					else {
						cout << "현재 소속된 그룹이 없습니다." << endl;
						continue;
					}
				}
				else {
					cout << "잘못된 옵션입니다. 다시 입력해주세요." << endl;
					continue;
				}
			}
			
		} 
		// 멤버 조회
		else if (input == "멤버조회") {
			if (current_group == nullptr) {
				cout << "현재 소속된 그룹이 없습니다." << endl;
			}
			else {
				string date;
				cout << "일정이 있는 멤버를 조회할 날짜를 입력하세요(yyyy-mm-dd): ";
				cin >> date;
				Date schd_date(date);

				cout << date << "에 일정이 있는 멤버를 출력합니다." << endl;
				vector<string> output_buffer; // 멤버 이름 출력 버퍼
				// 그룹 내 멤버 탐색
				for (int i = 0; i < current_group->member_list.size(); i++) {
					// 멤버의 일정 탐색
					for (int j = 0; j < current_group->member_list[i]->user_schd_list.size(); j++) {
						if (current_group->member_list[i]->user_schd_list[j]->schd_date == schd_date) {
							// 출력 버퍼에 추가
							output_buffer.push_back(current_group->member_list[i]->GetUserName());
							break;
						}
					}
				}
				// 버퍼 출력
				if (output_buffer.size() < 1) {
					cout << "일정이 있는 멤버가 없습니다!" << endl;
				}
				else {
					for (int i = 0; i < output_buffer.size(); i++) {
						cout << output_buffer[i] << endl;
					}
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
				// 일치하는 사용자가 없는 경우
				if (i == user_list.size() - 1) {
					cout << "일치하는 사용자가 없습니다." << endl;
					string add_user;
					cout << "사용자를 생성하시겠습니까?(y/n): ";
					cin >> add_user;
					// 입력한 이름으로 사용자 신규 생성
					if (add_user == "y") {
						current_user = new User(name);
						user_list.push_back(current_user);
						cout << "사용자가 생성되었습니다!" << endl;
						// 그룹에 가입
						string group_option;
						cout << "그룹에 가입하시겠습니까?(y/n): ";
						cin >> group_option;
						if (group_option == "y") {
							string group_name;
							cout << "가입할 그룹의 이름을 입력하세요: ";
							cin >> group_name;
							for (int i = 0; i < group_list.size(); i++) {
								if (group_list[i]->group_name == group_name) {
									// 현재 유저를 그룹에 추가
									group_list[i]->member_list.push_back(current_user);
									cout << "그룹에 가입되었습니다." << endl;
									// 현재 그룹을 해당 그룹으로 변경
									current_group = group_list[i];
									break;
								}
								// 일치하는 그룹이 없는 경우
								if (i == group_list.size() - 1) {
									cout << "입력한 그룹이 존재하지 않습니다." << endl;
									string add_group;
									cout << "입력한 그룹을 생성하시겠습니까?(y/n): ";
									cin >> add_group;
									// 그룹 생성
									if (add_group == "y") {
										group_list.push_back(new Group(group_name));
										cout << "그룹이 생성되었습니다." << endl;
										group_list[group_list.size() - 1]->member_list.push_back(current_user);
										cout << "그룹에 가입되었습니다." << endl;
										current_group = group_list[group_list.size() - 1];
										break;
									}
								}
							}
							break;
						}
						else {
							break;
						}
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