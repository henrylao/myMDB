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

class NotIMDB_Database
{
private:
	// movie titles & actor names are keys for accessing the table
	HashTable<Movie*>					__movieDB;
	HashTable<Actor>					__actorDB;
	BinarySearchTree<std::string>		__movieNamesBST_byGenre;
	BinarySearchTree<std::string>		__movieNamesBST_byYear;
	BinarySearchTree<std::string>		__movieNamesBST_byID;

	/* Internal functions for managing table populating*/
	void								__loadMovies(List<Movie>* movies);
	/* requires that the movies have been loaded to further map a movie to an actor via
	the list of Movie* stored in an actor value */
	void								__loadActors(List<Actor>* actors);
	void								__buildMovieNamesBST_byID(std::string path);
	void								__buildMovieNamesBST_byGenre(std::string path);
	void								__buildMovieNamesBST_byYear(std::string path);
public:
	/* Verify movie and actor existence */
	/* can either verify via BST or movieDB */
	bool foundMovie(std::string movieName) const;
	/* verify using actorDB */
	bool foundActor(std::string actorName) const; 
	// ------------------------------------------
	// Constructor & Destructor Section
	// ------------------------------------------
	NotIMDB_Database() {}
	virtual ~NotIMDB_Database();
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
	void displayActorTableStats() const;
	void displayMovieTableStats() const;

};

#endif // ! TABLE_DB_H
