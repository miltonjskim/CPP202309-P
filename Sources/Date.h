#include <string>
#include <vector>
#include <sstream>

using namespace std;

static class Date {

public:
	int year; // 연
	int month; // 월
	int day; // 일

	Date(); // 기본 생성자

	Date(int year, int month, int day); // 연, 월, 일을 직접 주입하는 생성자 

	Date(string schd_date); // 문자열을 입력받는 생성자

	// 비교 연산자 오버라이딩
	bool operator < (const Date& date);
	bool operator > (const Date& date);
	bool operator == (const Date& date);

	// 초과한 날짜를 정리해 다음 연/월로 넘겨주는 함수
	void Arrange(void);
};