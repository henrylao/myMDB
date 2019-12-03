#include "NotIMDB_Database.h"

void NotIMDB_Database::__loadMovies(List<Movie>* movies)
{
	Movie newMovie;
	int MSIZE;
	MSIZE = movies->getLength();
	for (int i = 0; i < MSIZE; i++)
	{
		newMovie = movies->getEntry(i);
		__movieDB.add(newMovie.getTitle(), newMovie);
	}
	delete movies;

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
	std::string path = "data\\full\\title_basics_cleaned_final_trimmed.tsv";
	NotIMDB_Database db;
	db.loadFromFile(path);
	db.readMovie("Miss Jerry");
	db.saveToFile();

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
	path = "data\\full\\title_basics_cleaned_final_trimmed2.tsv";
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
