#include "FileIo.h"

List<Person>* FileUtil::buildListFromFile(std::string path)
{
	std::ifstream infile;
	List<Person>* people = new List<Person>();
	infile.open(path, std::ios::in);

	if (!infile.good())
		return nullptr;
	// build PersonDatabase
	while (infile.good())
	{
		Person new_person;
		infile >> new_person;
		people->append(new_person);
	}
	return people;
}

List<std::string>* FileUtil::buildNameListFromFile(std::string path)
{
	std::ifstream infile;
	List<std::string>* names = new List<std::string>();
	infile.open(path, std::ios::in);

	if (!infile.good())
		return nullptr;

	std::string name;
	while (infile.good())
	{
		infile >> name;
		name = StringUtil::strip(name);
		names->append(name);
		name = "";
	}
	return names;
}
List<std::string>* FileUtil::buildDateListFromFile(std::string path)
{

	std::ifstream infile;
	List<std::string>* dates = new List<std::string>();
	infile.open(path, std::ios::in);
	if (!infile.good())
		return nullptr;

	std::string date;
	while (infile.good())
	{
		infile >> date;
		date = StringUtil::strip(date);
		date = StringUtil::replace(date, "-", "");
		dates->append(date);
		date = "";
	}
	return dates;
}
