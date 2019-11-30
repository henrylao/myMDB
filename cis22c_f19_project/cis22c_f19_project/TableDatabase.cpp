#include "TableDatabase.h"

bool TableDatabase::found(std::string key)  const
{
	try {
		Person found = __tableDB[key];
		return true;
	} 
	catch (const CustomException& e)
	{
		return false;
	}
	return false;
}

bool TableDatabase::found(const Person & person) const
{
	try {
		Person found = __tableDB[person.getBirthday()];
		return true;
	}
	catch (const CustomException& e)
	{
		return false;
	}
	return false;
}

TableDatabase::~TableDatabase()
{
}

void TableDatabase::buildDatabase(std::string path)
{
	// use FileIO pkg to build list of unknown quantity of people objs
	List<Person>* people = FileIO::buildPersonListFromFile(path);
	// populate into database
	for (int i = 0; i < people->getLength(); i++)
	{
		__tableDB.add(people->getEntry(i).getBirthday(), people->getEntry(i));
	}
}

bool TableDatabase::deletePerson(std::string key)
{
	if (found(key))
	{
		__tableDB.remove(key);
		return true;
	}
	return false;
}

bool TableDatabase::deletePerson(const Person & toDelete)
{
	if (found(toDelete.getBirthday()))
	{
		std::string key = toDelete.getBirthday();

		__tableDB.remove(key);
		return true;
	}
	return false;
}

bool TableDatabase::updateName(std::string key, std::string oldName, std::string newName)
{
	// check if person exists via key == date
	if (found(key))
	{
		__tableDB[key].setName(newName);
		return true;
	}
	return false;
}

bool TableDatabase::updateDate(std::string key, std::string oldDate, std::string newDate)
{
	// check if person exists via key == date
	if (found(key))
	{
		// hold copy 
		Person found = __tableDB[key];
		// delete from table
		__tableDB.remove(key);
		// create an editted version 
		Person editted(found.getName(), newDate);
		__tableDB.add(newDate, editted);
		return true;
	}
	return false;
}

void TableDatabase::displayPerson(std::string date) const
{
	if (found(date))
	{
		std::cout << __tableDB[date] << std::endl;
	}
	else
		std::cout << "Not found in the database" << std::endl;
}

void TableDatabase::displayDatabase() const
{
	List<std::string> keys = __tableDB.keys();
	if (__tableDB.size() > 0)
	{
		size_t SIZE = __tableDB.size();
		for (int i = 0; i < SIZE; i++)
		{
			std::cout << __tableDB[keys.getEntry(i)] << std::endl;
		}
	}
	else {
		std::cout << "Database is empty" << std::endl;
	}
}

void TableDatabase::displayPerson(const Person & target) const
{
	if (found(target.getBirthday()))
	{
		std::cout << __tableDB[target.getBirthday()] << std::endl;
	}
	else
		std::cout << target.getName() << " does not exist in the database" << std::endl;
}

void TableDatabase::displayStats() const
{
	std::cout << "Quantity Loaded: " << __tableDB.size() << std::endl;
	std::cout << "Max Capacity: " << __tableDB.capacity() << std::endl;
	std::cout << "Load factor: " << __tableDB.loadFactor() << std::endl;
	std::cout << "Collisions: " << __tableDB.collisions() << std::endl;
}
