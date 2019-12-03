#include "NotIMDB_Database.h"

void NotIMDB_Database::__loadMovies(List<Movie>* movies)
{
	Movie newMovie;
	int MSIZE;
	MSIZE = movies->getLength();
	for (int i = 0; i < MSIZE; i++)
	{
		newMovie = movies->getEntry(i);
		// preprocess the key
		std::string key = newMovie.getTitle() + " " + newMovie.getYearReleased();
		key = StringUtil::lowercase(StringUtil::strip(key));	// remove whitespace and turn into lowercase
		key = StringUtil::replace(key, " ", "_");
		// add to the table
		__movieDB.add(key, newMovie);
	}
	//delete movies;

}

/* create the map of bsts such that the first character of each tokenized word
signifies a key in the dictionary */
void NotIMDB_Database::__buildMovieBST(List<Movie>* movies)
{
	int SIZE = movies->getLength();
	Movie newMovie;
	List<std::string>* keywords;
	std::string keyword, keywords_preprocess;
	BinarySearchTree<std::string, Movie> found;

	std::string firstCharOfKeyword;

	for (int i = 0; i < SIZE; i++) {
		newMovie = movies->getEntry(i);
		/*  homogenize characters in the string */
		// strip then turn into lowercase
		keywords_preprocess = StringUtil::lowercase(StringUtil::strip(newMovie.getTitle() + " " + newMovie.getYearReleased())); 
		keywords_preprocess = StringUtil::replace(keywords_preprocess, " ", "_");
		// create a list of keywords from movie title and year
		keywords = StringUtil::split(keywords_preprocess, "_");	
		// create trees and populate accordingly such that 
		// the first letter of a keyword from the keyword list signifies a key in the
		// table of BSTS
		for (int j = 0; j < keywords->getLength(); j++)
		{
			keyword = keywords->getEntry(j);
			firstCharOfKeyword = std::string(1, keyword[0]);
			try {
				// check in the dictionary
				found = __movieBST[firstCharOfKeyword];
				__movieBST[firstCharOfKeyword].add(keyword, newMovie);
			}
			// first character of a keyword was not found to denote a key in the table
			catch (const CustomException& e)
			{
				// create a new bst such that the first character of the keyword denotes 
				// a key to a tree in the table of bst 
				__movieBST.add(std::string(1, keywords->getEntry(j)[0]), 
					BinarySearchTree<std::string, Movie>(keywords->getEntry(j), newMovie));

			}

		}
		// memory clean
		delete keywords;
	}

}

void NotIMDB_Database::__updateSearchEngineBST(const std::string edittedAttribute, Movie &)
{
}

void NotIMDB_Database::__updateSearchEngineBST(const std::string edittedAttribute)
{
}

bool NotIMDB_Database::foundMovie(std::string key)
{
	Movie found;
	try {
		found = __movieDB[key];
		return true;
	}
	catch (const CustomException& e)
	{
		return false;
	}
	return false;

}
bool NotIMDB_Database::search(std::string keyword) const
{
}



void NotIMDB_Database::displayMovieTableStats() const
{
	__movieDB.showStats();
}
bool NotIMDB_Database::readMovie(std::string key) const
{
	try {
		Movie found = __movieDB.get(key);
		std::cout << found << std::endl;
		return true;
	}
	catch (const CustomException& e)
	{
		return false;
	}
	return false;
}

void NotIMDB_Database::unitTest()
{
	std::string divider = "--------------------------------";
	NotIMDB_Database db;
	db.loadFromFile();
	db.readMovie("Miss Jerry");
	db.saveToFile("output.tsv");

	std::cout << divider << std::endl;
	std::cout << "Pre-delete:" << std::endl;
	db.displayMovieTableStats();
	std::cout << divider << std::endl;

	std::cout << "Post-delete:" << std::endl;
	db.deleteMovie("Miss Jerry");
	db.displayMovieTableStats();
	std::cout << divider << std::endl;

	db.showMostRecentDelete();
	db.undoMostRecentDelete();
	std::cout << divider << std::endl;
	db.readMovie("Miss Jerry");
	std::string path = "data\\full\\title_basics_cleaned_final_trimmed2.tsv";
	List<Movie>* movies = FileIO::buildMovieList(path);
	db.createMovie(movies->getEntry(5));
	db.displayMovieTableStats();
}


NotIMDB_Database::~NotIMDB_Database()
{
}

bool NotIMDB_Database::loadFromFile(std::string path)
{
	List<Movie>* movies = nullptr;

	//std::thread t1( FileIO::loadActorsIntoList, actorFilePath, actors);
	movies = FileIO::buildMovieList(path);
	__loadMovies(movies);
	__buildMovieBST(movies);
	List<std::string> keys = __movieBST.keys();
	int SIZE = keys.getLength();

	/* DEBUG Keyword Search Engine*/
	for (int i = 0; i < SIZE; i++)
	{
		std::cout << "BST in table at keyword char: " << keys.getEntry(i) << std::endl;
		std::cout << "Depth-first: " << std::endl;
		__movieBST[keys.getEntry(i)].printBreadthFirst();
	}
	// call internal loading functions

	return true;
}

void NotIMDB_Database::saveToFile(string path)
{
	std::ofstream outfile;
	outfile.open(path, std::ios::out);

	std::string out;
	size_t MSIZE = __movieDB.size();
	Movie temp;
	for (size_t i = 0; i < MSIZE; i++)
	{
		temp = (__movieDB[__movieDB.keys().getEntry(i)]);
		out = temp.getID() + " | " + temp.getTitle() + " | " +
			temp.getYearReleased() + " | " + temp.getRuntime()
			+ " | " + temp.getGenres() + "\n";
		outfile << out;
	}
	outfile.close();

}

bool NotIMDB_Database::deleteMovie(std::string key)
{
	try{
		Movie temp;
		temp = __movieDB[key];
		__deletedMovies.push(temp);

	}
	catch (const CustomException& e)
	{
		return false;
	}
	// push onto the stack
	__movieDB.remove(key);	// movie removed from table
	return true;
}

bool NotIMDB_Database::undoMostRecentDelete()
{
	Movie movieDeleted;
	if (__deletedMovies.size() > 0)
	{
		movieDeleted = __deletedMovies.peek();
		__deletedMovies.pop();
	}
	__movieDB.add(movieDeleted.getTitle(), movieDeleted);
	return false;
}

void NotIMDB_Database::showMostRecentDelete() const
{
	std::cout << __deletedMovies.peek() << std::endl;
}
