#ifndef  TABLE_DB_H
#define TABLE_DB_H

#include <thread>
#include "FileIO.h"
#include "person.h"
#include "HashTable.h"
#include "List.h"
#include "binary_search_tree.h"
#include "Movie.h"
#include "Actor.h"

class TableDatabase
{
private:
	HashTable<Movie*>					__movieDB;
	HashTable<Actor>					__actorDB;
	BinarySearchTree<std::string>		__movieByGenre;
		

	/* Internal functions for managing table populating*/
	void								__loadMovies(List<Movie>* movies);
	/* requires that the movies have been loaded to further map a movie to an actor via
	the list of Movie* stored in an actor value */
	void								__loadActors(List<Actor>* actors);
public:
	bool found(std::string key) const;
	bool foundMovie(std::string key) const;
	// ------------------------------------------
	// Constructor & Destructor Section
	// ------------------------------------------
	TableDatabase() {}
	virtual ~TableDatabase();
	// ------------------------------------------
	// Create Interface Section
	// ------------------------------------------
	void buildDatabase(std::string actorFilePath, std::string movieFilePa);
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
	void displayStats() const;

};

#endif // ! TABLE_DB_H
