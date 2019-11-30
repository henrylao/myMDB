#include "FileIO.h"

List<Person>* FileIO::buildPersonListFromFile(std::string path)
{
	std::ifstream infile;
	List<Person>* people = new List<Person>();
	infile.open(path, std::ios::in);
	List<std::string>* date_tokens;
	Person* new_person = new Person();
	if (!infile.good())
		return nullptr;
	std::string data;
	// build PersonDatabase
	while (infile.good())
	{
		getline(infile, data, '\n');
		data = StringUtil::strip(data);
		// date found case
		if (isdigit(data[0]))
		{
			date_tokens = StringUtil::split(data, "-");
			new_person->setYear(date_tokens->getEntry(0));
			new_person->setMonth(date_tokens->getEntry(1));
			new_person->setDay(date_tokens->getEntry(2));
			date_tokens->clear();
			delete date_tokens;
		}
		// name found case
		else if (isalpha(data[0]))
		{
			new_person->setName(data);
		}
		
		if (new_person->getBirthday().length() != 2 && new_person->getName().length() != 0)
		{
			people->append(*new_person);
			delete new_person;
			new_person = new Person();
		}
		// reset the date string for next line
		data = "";
	}
	// memory clean up
	if (new_person->getBirthday().length() == 0 || new_person->getName().length() == 0)
	{
		delete new_person;
	}
	return people;
}


List<std::string>* FileIO::buildNameListFromFile(std::string path)
{
	std::ifstream infile;
	List<std::string>* names = new List<std::string>();
	infile.open(path, std::ios::in);

	if (!infile.good())
		return nullptr;

	std::string name;
	while (infile.good())
	{
		if (getline(infile, name, '\n'))
		{
			name = StringUtil::strip(name);
			if (name.length() != 0)
			{
				names->append(name);
			}
			// reset after appending or a whitespace has been read
			name = "";
		}
	}
	return names;
}
List<std::string>* FileIO::buildDateListFromFile(std::string path)
{
	std::ifstream infile;
	List<std::string>* dates = new List<std::string>();
	infile.open(path, std::ios::in);
	if (!infile.good())
		return nullptr;

	std::string date;
	while (infile.good())
	{
		if (getline(infile, date, '\n'))
		{
			date = StringUtil::strip(date);
			if (date.length() != 0)
			{
				dates->append(date);
			}
			// reset after appending or a whitespace has been read
			date = "";
		}
	}
	return dates;
}

void FileIO::writeTableToFile(std::string path,
	const List<std::string>& keys,  HashTable<Person>& table)
{
	std::ofstream outfile;
	outfile.open(path, std::ios::out);

	for (int i = 0; i < keys.getLength(); i++)
	{
		outfile << table[keys.getEntry(i)].getName() << std::endl << keys.getEntry(i) << std::endl;
	}
	outfile.close();
}