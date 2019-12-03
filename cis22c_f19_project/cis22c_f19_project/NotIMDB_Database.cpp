#include "NotIMDB_Database.h"


int NotIMDB_Database::__binarySearch_byMovieName(List<std::string>* list, int l, int r, std::string targetString) const
{
	while (l <= r) {
		int m = l + (r - l) / 2;

		// Check if x is present at mid 
		if (StringUtil::contains(list->getEntry(m), targetString))
			return m;

		// If x greater, ignore left half 
		if (list->getEntry(m) < targetString)
			l = m + 1;

		// If x is smaller, ignore right half 
		else
			r = m - 1;
	}

	// if we reach here, then element was 
	// not present 
	return -1;
}
//
//
//int NotIMDB_Database::__binarySearchList(List<std::string>* list, int l, int r, std::string targetString) const
//{
//	while (l <= r) {
//		BinarySearchTree<std::string>*		__movieNamesBST_byGenre[29];
//		int m = l + (r - l) / 2;
//
//		// Check if x is present at mid 
//		if (list->getEntry(m)== targetString)
//			return m;
//
//		// If x greater, ignore left half 
//		if (list->getEntry(m) < targetString)
//			l = m + 1;
//
//		// If x is smaller, ignore right half 
//		else
//			r = m - 1;
//	}
//
//	// if we reach here, then element was 
//	// not present 
//	return -1;
//}

void NotIMDB_Database::__loadMovies(List<Movie>* movies)
{
	Movie newMovie;
	int MSIZE;
	MSIZE = movies->getLength();
	for (int i = 0; i < MSIZE; i++)
	{
		newMovie = movies->getEntry(i);
		__movieDB.add(newMovie.getTitle(), new Movie(newMovie));
		//for (int j = 0; j < 29; j++)
		//{
		//	if (StringUtil::contains(newMovie.getGenres(), GENRES[j]))
		//	{
		//		// keys for searching by a specific genre as a filter
		//		__movieNamesBST_byGenre[j]->add(newMovie.getTitle());
		//	}
		//}
	}
	// either delete or save internally for later use
	delete movies;

}

bool NotIMDB_Database::foundMovie(std::string key)  const
{
	try {
		//Movie found = __tableDB[key];
		return true;
	} 
	catch (const CustomException& e)
	{
		return false;
	}
	return false;
}

bool NotIMDB_Database::readMovie(std::string key) const
{
	Movie* found = __movieDB.get(key);
	if (found == nullptr)
		return false;
	else
	{
		std::cout << *found << std::endl;
		return true;
	}
	found = nullptr;
	return false;
}


NotIMDB_Database::~NotIMDB_Database()
{
	// memory clean up for table
	size_t MSIZE = __movieDB.size();
	for (int i = 0; i < MSIZE; i++)
		delete __movieDB[__movieDB.keys().getEntry(i)];
	// memory clean up for stack
	int SSIZE = __deletedMovies->size();
	Movie* movieToDelete = nullptr;
	for (int i = 0; i < SSIZE; i++)
	{
		movieToDelete = __deletedMovies->peek();
		__deletedMovies->pop();
		delete movieToDelete;
	}
	movieToDelete = nullptr;
	delete __deletedMovies;
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
		temp = *(__movieDB[__movieDB.keys().getEntry(i)]);
		out = temp.getID() + " | " + temp.getTitle() + " | " +
			temp.getYearReleased() + " | " + temp.getRuntime()
			+ " | " + temp.getGenres() + "\n";
		outfile << out;
	}
	outfile.close();
	
}
