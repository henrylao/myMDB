#ifndef  TABLE_DB_H
#define TABLE_DB_H

#include "FileIO.h"
#include "person.h"
#include "HashTable.h"
#include "List.h"

class TableDatabase
{
public:
	bool found(std::string key) const;
	bool found(const Person& person) const;

	// ------------------------------------------
	// Constructor & Destructor Section
	// ------------------------------------------
	TableDatabase() {}
	virtual ~TableDatabase();
	// ------------------------------------------
	// Create Interface Section
	// ------------------------------------------
	void buildDatabase(std::string path);
	bool addPerson(const Person& entry);
	bool addPerson(std::string name, std::string date);
	// ------------------------------------------
	// Delete Interface Section
	// ------------------------------------------
	bool deletePerson(std::string key);
	bool deletePerson(const Person& toDelete);
	// ------------------------------------------
	// Update Interface Section
	// ------------------------------------------
	bool updateName(std::string key, std::string oldName, std::string newName);
	bool updateDate(std::string key, std::string oldDate, std::string newDate);
	// ------------------------------------------
	// Read Interface Section
	// ------------------------------------------
	void displayPerson(std::string date) const;
	void displayDatabase() const;
	void displayPerson(const Person& target) const;
	void displayStats() const;

private:
	HashTable<Person>		__tableDB;
};

#endif // ! TABLE_DB_H
