#ifndef  TABLE_DB_H
#define TABLE_DB_H

#include "FileIO.h"
#include "person.h"
#include "HashTable.h"
#include "List.h"
#include "binary_search_tree.h"

class TableDatabase
{
private:
	HashTable<Person>					__tableDB;
	BinarySearchTree<std::string>		__
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
	// ------------------------------------------
	// Delete Interface Section
	// ------------------------------------------
	// ------------------------------------------
	// Update Interface Section
	// ------------------------------------------
	bool updateName(std::string key, std::string oldName, std::string newName);
	bool updateDate(std::string key, std::string oldDate, std::string newDate);
	// ------------------------------------------
	// Read Interface Section
	// ------------------------------------------
	void displayPerson(const Person& target) const;
	void displayStats() const;

};

#endif // ! TABLE_DB_H
