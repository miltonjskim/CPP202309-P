#include <iostream>
#include "Group.h"
#include "User.h"

using namespace std;

int main() {

	string input; // �Էµ� ��ɾ ����
	User* current_user = nullptr; // ���� ������� ����
	Group* current_group = nullptr; // ���� ������� ������ ���� �׷�
	vector<User*> user_list; // ������ �������� ���
	vector<Group*> group_list; // ������ �׷���� ���

	while (true) {

		// ���� ���� �� ����� ����
		if (current_user == nullptr) {
			cout << "����ڸ� �����մϴ�." << endl;
			string user_name; // ������ ����� ��
			cout << "�̸��� �Է��ϼ���: ";
			cin >> user_name;
			current_user = new User(user_name);
			user_list.push_back(current_user);
			cout << "����ڰ� �����Ǿ����ϴ�. ";
			cout << current_user->GetUserName() << "��, ȯ���մϴ�." << endl;
			
			string group_option;
			cout << "�׷쿡 �����Ͻðڽ��ϱ�?(y/n): ";
			cin >> group_option;
			if (group_option == "y") {
				string group_name;
				cout << "���� �Ǵ� ������ �׷��� �̸��� �Է��ϼ���: ";
				cin >> group_name;
				// �׷� ����
				group_list.push_back(new Group(group_name));
				cout << "�׷��� �����Ǿ����ϴ�." << endl;
				// �׷� ����
				group_list[group_list.size() - 1]->member_list.push_back(current_user);
				cout << "�׷쿡 ���ԵǾ����ϴ�." << endl;
				current_group = group_list[group_list.size() - 1];
			}
		}

		// ��ɾ� �Է�
		cout << "��ɾ �Է��ϼ���(�����߰�|��������|��������|�����ȸ|�������ȯ|����): ";
		cin >> input;

		// ���� �߰�
		if (input == "�����߰�") {
			string option;
			while (true) {
				cout << "������ �߰��մϴ�. �ɼ��� �Է��ϼ���(����|��ƾ|����): ";
				cin >> option;
				// ���� �Է�
				if (option == "����") {
					string schd_name;
					string schd_date;
					cout << "�������� ������ �߰��մϴ�." << endl;
					cout << "���� ��: ";
					cin >> schd_name;
					cout << "���� ��¥(yyyy-mm-dd): ";
					cin >> schd_date;

					current_user->AddSchedule(schd_name, schd_date);
					cout << "������ �߰��Ǿ����ϴ�!" << endl;

					break;
				}
				// ��ƾ �Է�
				else if (option == "��ƾ") {
					string schd_name;
					string start_date;
					int interval;
					int count;
					cout << "��ƾ ������ �߰��մϴ�." << endl;
					cout << "���� ��: ";
					cin >> schd_name;
					cout << "��ƾ ���� ��¥(yyyy-mm-dd): ";
					cin >> start_date;
					cout << "��ƾ ��¥ ����: ";
					cin >> interval;
					cout << "�ݺ� Ƚ��: ";
					cin >> count;

					current_user->AddRoutineSchedule(schd_name, start_date, interval, count);
					cout << "��ƾ ������ �߰��Ǿ����ϴ�!" << endl;

					break;
				}
				// ��ġ �Է�
				else if (option == "����") {
					string route;

					cout << "������ ���� ������ �߰��մϴ�." << endl;
					cout << "����: txt������ ���ڵ� ����� ANSI���� �մϴ�!" << endl;
					cout << "���� ���: ";
					cin >> route;

					current_user->AddBatchSchedule(route);
					cout << "������ �߰��Ǿ����ϴ�!" << endl;

					break;
				}
				else {
					cout << "�߸��� �ɼ��Դϴ�. �ٽ� �Է����ּ���." << endl;
					continue;
				}
			}
		}
		// ���� ����
		else if (input == "��������") {
			if (current_group == nullptr) {
				cout << "���Ե� �׷��� �����ϴ�!" << endl;
			}
			else {
				string members_name; // ��� ����� �̹�
				cout << "������ �����ϰ� ���� ����� �̸��� �Է��ϼ���: ";
				cin >> members_name;
				for (int i = 0; i < current_group->member_list.size(); i++) {
					if (current_group->member_list[i]->GetUserName() == members_name) {
						User* member = current_group->member_list[i];
						// ���� ��¥ �Է�
						string date;
						cout << "�����ϰ� ���� ������ ��¥�� �Է��ϼ���(yyyy-mm-dd): ";
						cin >> date;
						Date schd_date(date);
						cout << "�ش� ��¥�� ����� ������ �Ʒ��� �����ϴ�." << endl;
						member->PrintScheduleToList(*member, schd_date, schd_date);
						
						// ���� �̸� �Է�
						string schd_name;
						cout << "�����ϰ� ���� ������ �̸��� �Է��ϼ���: ";
						cin >> schd_name;
						// ���� ����
						current_user->JoinShedule(*member, schd_date, schd_name);
						break;
					}
					if (i == current_group->member_list.size() - 1) {
						cout << "�Է��� ����� �������� �ʽ��ϴ�." << endl;
					}
				}
			}
		}
		// ���� ����
		else if (input == "��������") {
			string option;
			while (true) {
				cout << "������ ������ ���ðڽ��ϱ�?(��|���): ";
				cin >> option;
				if (option == "��") {

					current_user->PrintSchedule(*current_user);
					break;
				}
				else if (option == "���") {

					string members_name;
					cout << "������ �� ��� ����� �̸��� �Է��ϼ���: ";
					cin >> members_name;

					if (current_group != nullptr) {
						for (int i = 0; i < current_group->member_list.size(); i++) {
							// �Է��� ����� ����
							if (current_group->member_list[i]->GetUserName() == members_name) {
								current_user->PrintSchedule(*current_group->member_list[i]);
								break;
							}
							// �Է��� ����� ����
							if (i == current_group->member_list.size() - 1) {
								cout << "�Է��� ����� �׷쿡 �������� �ʽ��ϴ�." << endl;
								break;
							}
						}
						break;
					}
					else {
						cout << "���� �Ҽӵ� �׷��� �����ϴ�." << endl;
						continue;
					}
				}
				else {
					cout << "�߸��� �ɼ��Դϴ�. �ٽ� �Է����ּ���." << endl;
					continue;
				}
			}
			
		} 
		// ��� ��ȸ
		else if (input == "�����ȸ") {
			if (current_group == nullptr) {
				cout << "���� �Ҽӵ� �׷��� �����ϴ�." << endl;
			}
			else {
				string date;
				cout << "������ �ִ� ����� ��ȸ�� ��¥�� �Է��ϼ���(yyyy-mm-dd): ";
				cin >> date;
				Date schd_date(date);

				cout << date << "�� ������ �ִ� ����� ����մϴ�." << endl;
				vector<string> output_buffer; // ��� �̸� ��� ����
				// �׷� �� ��� Ž��
				for (int i = 0; i < current_group->member_list.size(); i++) {
					// ����� ���� Ž��
					for (int j = 0; j < current_group->member_list[i]->user_schd_list.size(); j++) {
						if (current_group->member_list[i]->user_schd_list[j]->schd_date == schd_date) {
							// ��� ���ۿ� �߰�
							output_buffer.push_back(current_group->member_list[i]->GetUserName());
							break;
						}
					}
				}
				// ���� ���
				if (output_buffer.size() < 1) {
					cout << "������ �ִ� ����� �����ϴ�!" << endl;
				}
				else {
					for (int i = 0; i < output_buffer.size(); i++) {
						cout << output_buffer[i] << endl;
					}
				}
			}
		}
		// ����� ��ȯ
		else if (input == "�������ȯ") {
			string name;
			cout << "��ȯ�� ������� �̸��� �Է��ϼ���: ";
			cin >> name;
			for (int i = 0; i < user_list.size(); i++) {
				// ��ġ�ϴ� ����ڸ� ã�Ҵٸ� ����� ��ȯ
				if (user_list[i]->GetUserName() == name) {
					current_user = user_list[i];
					cout << "����ڰ� ��ȯ�Ǿ����ϴ�!" << endl;
					// ��ȯ�� ����ڰ� �׷��� �ִ��� Ȯ��
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
				// ��ġ�ϴ� ����ڰ� ���� ���
				if (i == user_list.size() - 1) {
					cout << "��ġ�ϴ� ����ڰ� �����ϴ�." << endl;
					string add_user;
					cout << "����ڸ� �����Ͻðڽ��ϱ�?(y/n): ";
					cin >> add_user;
					// �Է��� �̸����� ����� �ű� ����
					if (add_user == "y") {
						current_user = new User(name);
						user_list.push_back(current_user);
						cout << "����ڰ� �����Ǿ����ϴ�!" << endl;
						// �׷쿡 ����
						string group_option;
						cout << "�׷쿡 �����Ͻðڽ��ϱ�?(y/n): ";
						cin >> group_option;
						if (group_option == "y") {
							string group_name;
							cout << "������ �׷��� �̸��� �Է��ϼ���: ";
							cin >> group_name;
							for (int i = 0; i < group_list.size(); i++) {
								if (group_list[i]->group_name == group_name) {
									// ���� ������ �׷쿡 �߰�
									group_list[i]->member_list.push_back(current_user);
									cout << "�׷쿡 ���ԵǾ����ϴ�." << endl;
									// ���� �׷��� �ش� �׷����� ����
									current_group = group_list[i];
									break;
								}
								// ��ġ�ϴ� �׷��� ���� ���
								if (i == group_list.size() - 1) {
									cout << "�Է��� �׷��� �������� �ʽ��ϴ�." << endl;
									string add_group;
									cout << "�Է��� �׷��� �����Ͻðڽ��ϱ�?(y/n): ";
									cin >> add_group;
									// �׷� ����
									if (add_group == "y") {
										group_list.push_back(new Group(group_name));
										cout << "�׷��� �����Ǿ����ϴ�." << endl;
										group_list[group_list.size() - 1]->member_list.push_back(current_user);
										cout << "�׷쿡 ���ԵǾ����ϴ�." << endl;
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
		else if (input == "����") {
			cout << "���α׷��� �����մϴ�...";
			break;
		}
		else {
			cout << "�߸��� ��ɾ��Դϴ�. �ٽ� �Է����ּ���." << endl;
			continue;
		}
	}

	return 0;
}