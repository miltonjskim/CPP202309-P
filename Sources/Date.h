#include <string>
#include <vector>
#include <sstream>

using namespace std;

static class Date {

public:
	int year; // ��
	int month; // ��
	int day; // ��

	Date(); // �⺻ ������

	Date(int year, int month, int day); // ��, ��, ���� ���� �����ϴ� ������ 

	Date(string schd_date); // ���ڿ��� �Է¹޴� ������

	// �� ������ �������̵�
	bool operator < (const Date& date) const;
	bool operator > (const Date& date) const;
	bool operator == (const Date& date) const;

	// �ʰ��� ��¥�� ������ ���� ��/���� �Ѱ��ִ� �Լ�
	void Arrange(void);
};