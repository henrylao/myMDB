#ifndef _UTIL_FILEIO_H
#define _UTIL_FILEIO_H
#include "List.h"
#include "person.h"
#include <fstream>
#include "StringUtil.h"
#include "HashTable.h"
#include "Movie.h"
#include "Actor.h"

namespace FileIO
{
	static const std::string BAR_DELIM = "|";
	/* Builds a list of people from a .txt file. White spaces are 
	accounted for an do not affect list creation. Order
	of names and dates must follow the following format:
	person1_name
	YYYY-MM-DD
	person2_name
	YYYY-MM-DD
	person3_name
	YYYY-MM-DD
	@return pointer to a list of people constructed */
	List<Person>* buildPersonListFromFile(std::string);
	/* Builds a list of people from a .txt file of names. 
	@return pointer to a list of names 
	@param path is the full path to the target file */
	List<std::string>* buildNameListFromFile(std::string path);
	/* Builds a list of dates from a .txt file of dates of
	the following format:
	YYYY-MM-DD
	@return pointer to a list of names
	@param path is the full path to the target file */
	List<std::string>* buildDateListFromFile(std::string path);
	void writeTableToFile(std::string path,
		const List<std::string>& keys,   HashTable<Person>& table);	
	/* Reads a .tsv file following the format:
	tconst | primaryTitle | startYear | runtimeMinutes | genre1, genre2, ... , genre-n 
	The list is sorted in accordance to tconst, a tag for building the list
	of associated movies contained in an Actor object */
	List<Movie>* buildMovieList(std::string path);
	/* Reads from a .tsv file following the format:
	nconst | primaryName | birthYear | deathYear | primaryProfession | knownForTitles */
	List<Actor>* buildActorList(std::string path);
	/* Function used for multhreading */
	void loadActorsIntoList(std::string path, List<Actor>* actors);
	void loadMoviesIntoList(std::string path, List<Movie>* movie);
	/* Multithread safe function to construct a list of movieTitles from
	a file containing movieTitles sorted by their IDs */
	void buildMovieTitles_sortedByID(std::string path, List<std::string>* movieTitles);
}
#endif // !_UTIL_FILEIO_H
