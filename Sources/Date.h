#include <string>
#include <vector>
#include <sstream>

using namespace std;

static class Date {

public:
	int year;
	int month;
	int day;

	Date();

	Date(int year, int month, int day);

	Date(string schd_date);

	void Arrange(void);
};