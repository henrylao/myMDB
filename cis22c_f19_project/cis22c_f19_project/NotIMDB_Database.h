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
#include "stack.h"

// genres to iterate through when check if movie contains the genre
static const std::string GENRES[29] = {
		"action", "adult", "adventure",
		"animation", "biography", "comedy", "crime", "documentary",
		"drama", "family", "fantasy", "film-noir", 
		"game-show", "history", "horror",
		"music", "musical", "mystery", "news", "reality-tv",
		"romance", "sci-fi", "short", "sport", 
		"talk-show", "thriller", "unavailable", 
		"war", "western"
};
class NotIMDB_Database
{
	
private:
	// movie titles & actor names are keys for accessing the table
	HashTable<Movie*>					__movieDB;
	//HashTable<Actor>					__actorDB;
	Stack<Movie*>*						__deletedMovies;
	
	/* Array of binary trees storing movie names of various genres */
	BinarySearchTree<std::string>*		__movieNamesBST_byGenre[29];

	BinarySearchTree<std::string>*		__movieNamesBST_byYear;
	// BST can be created from movieDB, used for storing movieDB keys
	BinarySearchTree<std::string>		__movieNames;
	// ------------------------------------------
	// Internal Helper Method Section
	// ------------------------------------------
	/* Utilizes StringUtil::contains to verify id */

	int __binarySearchList(List<std::string>* list, int l, int r, std::string targetString) const;

	/* Internal functions for managing table populating*/
	void								__loadMovies(List<Movie>* movies);
	/* requires that the movies have been loaded to further map a movie to an actor via
	the list of Movie* stored in an actor value */
	void								__clear();
public:
	int									__binarySearch_byMovieName(List<std::string>* moviesSortedByID,
													int l, int r, std::string targetString) const;
	
	// ------------------------------------------
	// Constructor & Destructor Section
	// ------------------------------------------
	NotIMDB_Database() {}
	virtual ~NotIMDB_Database();
	// ------------------------------------------
	// Create/FileIO Section
	// ------------------------------------------
	bool  				loadFromFile(std::string movieFilePath);
	// save to a default path or a custom path/name
	bool  				saveToFile(string t_name = "");

	// ------------------------------------------
	// Delete Section
	// ------------------------------------------
	// add the deleted movie to the stack
	bool				deleteMovie(std::string key);
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

	
	// ------------------------------------------
	// Search Section
	// ------------------------------------------
	/* Verify movie and actor existence */
	/* can either verify via BST or movieDB */
	bool  				foundMovie(std::string movieName) const;
	/* verify using actorDB */

	// ------------------------------------------
	// Read Section
	// ------------------------------------------
	void  				displayMovieTableStats() const;

};

#endif // ! TABLE_DB_H
