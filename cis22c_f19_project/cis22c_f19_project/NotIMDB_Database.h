#pragma once

#include "FileIO.h"
//#include "person.h"
#include "HashTable.h"
#include "List.h"
//#include "binary_search_tree.h"
#include "Movie.h"
#include "stack.h"
#include "BST_pair.h"
#include "CustomException.h"
#include "NotFoundException.h"

class NotIMDB_Database
{
private:
	// movie titles & actor names are keys for accessing the table
	HashTable<Movie>					__movieDB;
	Stack<Movie>						__deletedMovies;
	HashTable<BinarySearchTree<std::string, Movie>>		__searchEngineBST;
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
	std::string			__processSearchEntry(const std::string& searchEntry);
	Movie				__updateSearchEngineBST(const std::string edittedAttribute, const Movie& movieToEdit, int op);
public:

	// ------------------------------------------
	// Constructor & Destructor Section
	// ------------------------------------------
	NotIMDB_Database() {}
	virtual ~NotIMDB_Database();
	// ------------------------------------------
	// Create/FileIO Section
	// ------------------------------------------
	bool  				loadFromFile(std::string path);
	// save to a default path or a custom path/name
	void  				saveToFile(string path = "data//output.tsv");
	bool				createMovie(const Movie& newMovie)
	{
		return __movieDB.add(newMovie.getTitle(), newMovie);
	}

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
	bool				foundMovie(std::string key);
	/* verify using actorDB */
	//bool  				foundActor(std::string actorName) const;

	// ------------------------------------------
	// Read Section
	// ------------------------------------------
	void				displayMovieTableStats() const;
	bool				readMovie(std::string key) const;
	void				displaySearchEngineState() const;
	void				unitTest();
};
