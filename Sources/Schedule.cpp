#include "Schedule.h"

Schedule::Schedule(string user_name, string schd_name, Date schd_date) {

	this->user_name = user_name;
	this->schd_name = schd_name;
	this->schd_date = schd_date;
}

bool Schedule::operator < (const Schedule& schd) {
	return this->schd_date < schd.schd_date;
}

bool Schedule::operator > (const Schedule& schd) {
	return this->schd_date > schd.schd_date;
}

bool Schedule::operator == (const Schedule& schd) {
	return this->schd_date == schd.schd_date;
}