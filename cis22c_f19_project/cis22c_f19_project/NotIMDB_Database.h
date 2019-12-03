#ifndef  TABLE_DB_H
#define TABLE_DB_H

#include "FileIO.h"
#include "person.h"
#include "HashTable.h"
#include "List.h"
#include "Movie.h"
#include "stack.h"
#include "BST_KVpair.h"
#include "CustomException.h"


class NotIMDB_Database
{
private:
	// used for managing keyword searches and tokenizing search queries
	// such that each keyword maps to a movie
	// movies are given weight from keywords 
	HashTable<BinarySearchTree<std::string, Movie>>		__searchEngineBST;	
	HashTable<Movie>									__movieDB;
	Stack<Movie>										__deletedMovies;
	// ------------------------------------------
	// Internal Helper Method Section
	// ------------------------------------------
	void				__loadMovies(List<Movie>* movies);
	/* tokenizes movie attributes ie movie name */
	void				__buildMovieBST(List<Movie>* movies);
	/* to be called during updates to a specific movie where either the year or
	the name of the movie is changed 
	update the search engine bst when edits are made to movies via removal 
	op == 1 : editted title 
	op == 2 : editted year  */
	void				__updateSearchEngineBST(const std::string edittedAttribute, const Movie& movieToEdit, int op);
public:

	// ------------------------------------------
	// Constructor & Destructor Section
	// ------------------------------------------
	NotIMDB_Database()  {}
	virtual ~NotIMDB_Database();
	// ------------------------------------------
	// Create/FileIO Section
	// ------------------------------------------
	bool  				loadFromFile(std::string path = "title_basics_cleaned_final_trimmed_setA.tsv");
	// save to a default path or a custom path/name
	void  				saveToFile(string path );
	bool				createMovie(const Movie& newMovie) { return __movieDB.add(newMovie.getTitle(), newMovie); }

	// ------------------------------------------
	// Delete Section
	// ------------------------------------------
	// add the deleted movie to the stack
	bool				deleteMovie(std::string key);
	// undoes the most recent delete using a stack
	bool				undoMostRecentDelete();
	void				showMostRecentDelete() const;
	// ------------------------------------------
	// Update Section
	// ------------------------------------------
	/* call internal bst search engine update before actually updating the table
	find movie by oldName, hold a copy of the movie delete movie of old name, update copy to newName, finally
	add back into table 
	
	*/
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
	bool				foundMovie(std::string key);
	/* verify using actorDB */
	bool  				foundActor(std::string actorName) const;
	/* A search will generate a list of entries to be displayed, if the list 
	has a length of 0 then return false ie nothing found from the user input
	else if found, find the movie with the most.. */
	bool				search(std::string keyword) const;
	// ------------------------------------------
	// Read Section
	// ------------------------------------------
	void				displayMovieTableStats() const;
	bool				readMovie(std::string key) const;

	void				unitTest();
};

#endif // ! TABLE_DB_H
