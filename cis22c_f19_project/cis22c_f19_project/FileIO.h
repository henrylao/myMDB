#ifndef _UTIL_FILEIO_H
#define _UTIL_FILEIO_H
#include "List.h"
#include <fstream>
#include "StringUtil.h"
#include "HashTable.h"
#include "Movie.h"
#include "Actor.h"

namespace FileIO
{
	static const std::string BAR_DELIM = "|";
	/* Reads a .tsv file following the format:
	tconst | primaryTitle | startYear | runtimeMinutes | genre1, genre2, ... , genre-n 
	The list is sorted in accordance to tconst, a tag for building the list
	of associated movies contained in an Actor object */
	List<Movie>* buildMovieList(std::string path);
	/* Reads from a .tsv file following the format:
	nconst | primaryName | birthYear | deathYear | primaryProfession | knownForTitles */
	List<Actor>* buildActorList(std::string path);
	/* Multithread safe function to construct a list of movieTitles from
	a file containing movieTitles sorted by their IDs */
	void buildMovieTitles_sortedByID(std::string path, List<std::string>* movieTitles);
}
#endif // !_UTIL_FILEIO_H
