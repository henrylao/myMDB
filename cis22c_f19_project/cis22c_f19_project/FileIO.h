#ifndef _UTIL_FILEIO_H
#define _UTIL_FILEIO_H
#include "List.h"
#include <fstream>
#include "StringUtil.h"
#include "HashTable.h"
#include "Movie.h"

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
	void loadMoviesIntoList(std::string path, List<Movie>* movie);
}
#endif // !_UTIL_FILEIO_H
