#include "person.h"

std::ostream & operator<<(std::ostream & t_out, const Person & t_person)
{
	t_out << t_person.m_name << "\t" 
		<< t_person.m_year << '-' << t_person.m_month << '-' << t_person.m_day;
	return t_out;
}

std::istream & operator>>(std::istream & t_in, Person & t_person)
{
	getline(t_in, t_person.m_name, '\n');
	getline(t_in, t_person.m_year, '-');
	getline(t_in, t_person.m_month, '-');
	getline(t_in, t_person.m_day, '\n');
	return t_in;
}
bool Person::operator==(const Person& t_rhs) const
{
	if (this->config == 1)
	{
		return (this->m_name == t_rhs.m_name ? true : false);
	}
	else if (this->config == 2)
		return ((this->m_year == t_rhs.m_year &&
			this->m_month == t_rhs.m_month &&
			this->m_day == t_rhs.m_day) ? true : false);
	else
		throw 3;	
}
bool Person::operator<(const Person & t_rhs) const
{
	if (t_rhs.getConfig() == 1) {
		if (this->getName() < t_rhs.getName()) {
			return true;
		}
		else
			return false;
	}
	else if (t_rhs.getConfig() == 2) {
		if (this->m_year < t_rhs.m_year) {
			return true;
		}
		else if (this->m_year == t_rhs.m_year) {
			if (this->m_month < t_rhs.m_month) {
				return true;
			}
			else if (this->m_month == t_rhs.m_month) {
				if (this->m_day < t_rhs.m_day) {
					return true;
				}
				else if (this->m_day == t_rhs.m_day) {
					return false;
				}
				else if (this->m_day > t_rhs.m_day) {
					return false;
				}
			}
			else if (this->m_month > t_rhs.m_month) {
				return false;
			}
		}
		else if (this->m_year > t_rhs.m_year) {
			return false;
		}
	}
	return false;
}

bool Person::operator>(const Person & t_rhs) const
{
	if (t_rhs.getConfig() == 1) {
		if (this->getName() > t_rhs.getName()) {
			return true;
		}
		else
			return false;
	}
	else if (t_rhs.getConfig() == 2) {
		if (this->m_year > t_rhs.m_year) {
			return true;
		}
		else if (this->m_year == t_rhs.m_year) {
			if (this->m_month > t_rhs.m_month) {
				return true;
			}
			else if (this->m_month == t_rhs.m_month) {
				if (this->m_day > t_rhs.m_day) {
					return true;
				}
				else if (this->m_day == t_rhs.m_day) {
					return false;
				}
				else if (this->m_day < t_rhs.m_day) {
					return false;
				}
			}
			else if (this->m_month < t_rhs.m_month) {
				return false;
			}
		}
		else if (this->m_year < t_rhs.m_year) {
			return false;
		}
	}
	return false;
}
