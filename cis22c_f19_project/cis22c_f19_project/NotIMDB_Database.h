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
	// ------------------------------------------
	// Internal Helper Method Section
	// ------------------------------------------
	/* Internal functions for managing table populating*/
	void								__loadMovies(List<Movie>* movies);
	/* requires that the movies have been loaded to further map a movie to an actor via
	the list of Movie* stored in an actor value */
	void								__loadActors(List<Actor>* actors);
	void								__buildMovieNamesBST_byID(std::string path);
	void								__buildMovieNamesBST_byGenre(std::string path);
	void								__buildMovieNamesBST_byYear(std::string path);
	void								__clear();
public:
	
	// ------------------------------------------
	// Constructor & Destructor Section
	// ------------------------------------------
	NotIMDB_Database() {}
	virtual ~NotIMDB_Database();
	// ------------------------------------------
	// Create/FileIO Section
	// ------------------------------------------
	bool  				loadFromFile(std::string actorFilePath, std::string movieFilePath);
	// save to a default path or a custom path/name
	bool  				saveToFile(string t_name = "");

	// ------------------------------------------
	// Delete Section
	// ------------------------------------------
	
	// ------------------------------------------
	// Update Section
	// ------------------------------------------
	// find movie by oldName, hold a copy of the movie delete movie of old name, update copy to newName, finally 
	// add back into table
	bool				updateMovieName(std::string oldMovieName, std::string newMovieName);
	bool				updateMovieYear(std::string key, std::string newYearReleased);
	bool				updateMovieID(std::string key, std::string newID);
	bool				updateMovieRuntime(std::string key, std::string newRuntime);
	// op 0 appends to the genre string, op 1 sets the genre to newGenreName
	bool				updateMovieGenre(std::string key, std::string newGenreName, int op);
	bool 				updateMovieRating(std::string key, std::string newKey);

	bool 				updateActorName(std::string oldActorName, std::string newActorName) :
	bool  				updateActorBirthYear(std::string key, std::string newBirthYear);
	bool  				updateActorDeathYear(std::string key, std::string newDeathYear);
	// 0 to append to old string, 1 to set
	bool  				updateActorRoles(std::string key, std::string newRoleName, int op);
	bool  				updateActorID(std::string key, std::string newID);

	
	// ------------------------------------------
	// Search Section
	// ------------------------------------------
	/* Verify movie and actor existence */
	/* can either verify via BST or movieDB */
	bool  				foundMovie(std::string movieName) const;
	/* verify using actorDB */
	bool  				foundActor(std::string actorName) const;

	// ------------------------------------------
	// Read Section
	// ------------------------------------------
	void 				 displayActorTableStats() const;
	void  				displayMovieTableStats() const;

};

#endif // ! TABLE_DB_H
