#pragma once
#include <string>
#include <iostream>
#include "StringUtil.h"
#include <sstream>
class Person
{
	std::string m_month;
	std::string m_day;
	std::string m_year;
	std::string m_name;

	int config;

public:
	Person() {
		m_day = "";
		m_year = "";
		m_month = "";
		config = 0;
	}

	Person(const std::string& t_name, const std::string& t_day, const std::string& t_month, const std::string& t_year, const int& t_config) {
		m_name = t_name;
		m_day = t_day;
		m_year = t_year;
		m_month = t_month;
		config = t_config;
	}

	Person(const std::string& t_full_name, const std::string& t_full_date)
	{
		m_name = t_full_name;
		std::string date = StringUtil::strip(t_full_date);
		std::stringstream ss;
		ss << date;
		getline(ss, m_year, '-');
		getline(ss, m_month, '-');
		getline(ss, m_day);
	}

	Person(const Person& copy)
	{
		m_name = copy.m_name;
		m_month = copy.m_month;
		m_year = copy.m_year;
		m_day = copy.m_day;
	}
	std::string getName() const {
		return m_name;
	}
	std::string getBirthday() const {
		return (m_year + "-" + m_month + "-" + m_day);
	}
	int getConfig() const {
		return config;
	}
	void setName(std::string t_name) {
		m_name = t_name;
	}
	void setMonth(std::string t_month) {
		m_month = t_month;
	}
	void setDay(std::string t_day) {
		m_day = t_day;
	}
	void setYear(std::string t_year) {
		m_year = t_year;
	}
	/*
	1 for comparison operators to operate on name field
	2 for comparison operators to operate on date field
	*/
	void setConfig(const int& t_config) {
		config = t_config;
	}
	//--------------------------------------
	// Operator Overload Section
	//--------------------------------------
	friend std::ostream&  operator<<(std::ostream& t_out, const Person& t_person);
	friend std::istream&  operator>>(std::istream& t_in, Person& t_person);
	bool operator==(const Person& t_person) const;
	bool operator<(const Person& t_rhs) const;
	bool operator>(const Person& t_rhs) const;
};
