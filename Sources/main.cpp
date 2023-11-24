#include <iostream>
#include "Group.h"

using namespace std;

int main() {

	string input; // �Էµ� ��ɾ ����
	User* current_user = nullptr; // ���� ������� ����
	vector<User*> user_list; // ������ �������� ���

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
			// TODO: �׷쿡 ����
		}

		// ��ɾ� �Է�
		cout << "��ɾ �Է��ϼ���(�����߰�|��������|�������ȯ|����): ";
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
			string option;
			while (true) {
				cout << "������ ������ ���ðڽ��ϱ�?(��|���): ";
				cin >> option;
				if (option == "��") {
					string start;
					string end;
					cout << "������ ǥ���� �������� �Է��ϼ���(yyyy-mm-dd): ";
					cin >> start;
					cout << "������ ǥ���� �������� �Է��ϼ���(yyyy-mm-dd): ";
					cin >> end;
					 
					Date start_date(start);
					Date end_date(end);

					cout << "������ ����մϴ�." << endl;
					current_user->PrintScheduleToList(*current_user, start, end);

					break;
				}
				else if (option == "���") {
					// TODO: ����� �����ϰ� �׷쿡 �ִ��� üũ �� ������ �����ִ� ����
				}
				else {
					cout << "�߸��� �ɼ��Դϴ�. �ٽ� �Է����ּ���." << endl;
					continue;
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
					break;
				}
				if (i == user_list.size() - 1) {
					cout << "��ġ�ϴ� ����ڰ� �����ϴ�." << endl;
					string add_user;
					cout << "����ڸ� �����Ͻðڽ��ϱ�?(y/n): ";
					cin >> add_user;
					// �Է��� �̸����� ����� �ű� ����
					if (add_user == "y") {
						current_user = new User(name);
						user_list.push_back(current_user);
						// TODO: �׷쿡 ����
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