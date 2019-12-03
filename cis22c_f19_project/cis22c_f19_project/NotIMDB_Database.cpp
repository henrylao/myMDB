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

NotIMDB_Database::~NotIMDB_Database() {}

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

	std::string out = "";
	int MSIZE = (int)__movieDB.size();
	Movie temp;
	for (int i = 0; i < MSIZE; i++)
	{
		temp = (__movieDB[__movieDB.keys().getEntry(i)]);
		out = temp.getID() + " | "
			+ temp.getTitle() + " | "
			+ temp.getYearReleased() + " | "
			+ temp.getRuntime() + " | "
			+ temp.getGenres() + "\n";
		outfile << out;
	}
	outfile.close();
}

bool NotIMDB_Database::deleteMovie(std::string key)
{
	try {
		// push onto the stack
		Movie temp;
		temp = __movieDB[key];
		__deletedMovies.push(temp);
	}
	catch (const CustomException& e)
	{
		return false;
	}

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

// TODO: refactor to avoid code reuse?
bool NotIMDB_Database::updateMovieName(std::string oldMovieName, std::string newMovieName)
{
	try {
		Movie oldMovie = __movieDB.get(oldMovieName);
		Movie newMovie(oldMovie.getID(), newMovieName,
			oldMovie.getYearReleased(), oldMovie.getRuntime(), oldMovie.getGenres());
		__movieDB.remove(oldMovieName);
		__movieDB.add(newMovieName, newMovie);
		return true;
	}
	catch (CustomException e)
	{
		std::cout << "Error: movie could not be updated" << std::endl;
	}
	return false;
}

// key is the movie's title
bool NotIMDB_Database::updateMovieYear(std::string key, std::string newYearReleased)
{
	try {
		Movie oldMovie = __movieDB.get(key);
		Movie newMovie(oldMovie.getID(), oldMovie.getTitle(), newYearReleased,
			oldMovie.getRuntime(), oldMovie.getGenres());
		__movieDB.remove(key);
		__movieDB.add(key, newMovie);
		return true;
	}
	catch (CustomException e)
	{
		std::cout << "Error: movie could not be updated" << std::endl;
	}
	return false;
}

bool NotIMDB_Database::updateMovieID(std::string key, std::string newID)
{
	try {
		Movie oldMovie = __movieDB.get(key);
		Movie newMovie(newID, oldMovie.getTitle(), oldMovie.getYearReleased(),
			oldMovie.getRuntime(), oldMovie.getGenres());
		__movieDB.remove(key);
		__movieDB.add(key, newMovie);
		return true;
	}
	catch (CustomException e)
	{
		std::cout << "Error: movie could not be updated" << std::endl;
	}
	return false;
}

bool NotIMDB_Database::updateMovieRuntime(std::string key, std::string newRuntime)
{
	try {
		Movie oldMovie = __movieDB.get(key);
		Movie newMovie(oldMovie.getID(), oldMovie.getTitle(),
			oldMovie.getYearReleased(), newRuntime, oldMovie.getGenres());
		__movieDB.remove(key);
		__movieDB.add(key, newMovie);
		return true;
	}
	catch (CustomException e)
	{
		std::cout << "Error: movie could not be updated" << std::endl;
	}
	return false;
}

// TODO: what is format of genres?
bool NotIMDB_Database::updateMovieGenre(std::string key, std::string newGenreName, int op)
{
	try {
		Movie oldMovie = __movieDB.get(key);
		std::string genres;
		if (op)
			genres = newGenreName;
		else
			genres = oldMovie.getGenres().append(newGenreName);

		Movie newMovie(oldMovie.getID(), oldMovie.getTitle(),
			oldMovie.getYearReleased(), oldMovie.getRuntime(), genres);
		__movieDB.remove(key);
		__movieDB.add(key, newMovie);
		return true;
	}
	catch (CustomException e)
	{
		std::cout << "Error: movie could not be updated" << std::endl;
	}
	return false;
}

bool NotIMDB_Database::updateMovieRating(std::string key, std::string newKey)
{
	try {
		Movie oldMovie = __movieDB.get(key);
		Movie newMovie(oldMovie.getID(), oldMovie.getTitle(), oldMovie.getYearReleased(),
			oldMovie.getRuntime(), oldMovie.getGenres(), newKey);
		__movieDB.remove(key);
		__movieDB.add(newKey, newMovie);
		return true;
	}
	catch (CustomException e)
	{
		std::cout << "Error: movie could not be updated" << std::endl;
	}
	return false;
}
