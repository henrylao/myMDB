#include "NotIMDB_Database.h"

void NotIMDB_Database::__clear()
{
	for (int i = 0; i < 29; i++)
	{
		delete __movieNamesBST_byGenre[i];
	}
}

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


int NotIMDB_Database::__binarySearchList(List<std::string>* list, int l, int r, std::string targetString) const
{
	while (l <= r) {
		BinarySearchTree<std::string>*		__movieNamesBST_byGenre[29];
		int m = l + (r - l) / 2;

		// Check if x is present at mid 
		if (list->getEntry(m)== targetString)
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

void NotIMDB_Database::__loadMovies(List<Movie>* movies)
{
	Movie newMovie;
	int MSIZE, GSIZE;
	MSIZE = movies->getLength();
	for (int i = 0; i < MSIZE; i++)
	{
		newMovie = movies->getEntry(i);
		__movieDB.add(newMovie.getTitle(), new Movie(newMovie));
		for (int j = 0; j < 29; j++)
		{
			if (StringUtil::contains(newMovie.getGenres(), GENRES[j]))
			{
				__movieNamesBST_byGenre[j]->add(newMovie.getTitle());
			}
		}
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
//
//bool NotIMDB_Database::found(const Person & person) const
//{
//	try {
//		//Person found = __tableDB[person.getBirthday()];
//		return true;
//	}
//	catch (const CustomException& e)
//	{
//		return false;
//	}
//	return false;
//}

NotIMDB_Database::~NotIMDB_Database()
{
	for (int i =0; i < 29; i++)
		delete	__movieNamesBST_byGenre[i];


}

bool NotIMDB_Database::loadFromFile(std::string actorFilePath, std::string movieFilePath)
{
	List<Actor>* actors;
	List<Movie>* movies;

	//std::thread t1( FileIO::loadActorsIntoList, actorFilePath, actors);
	std::thread t2( FileIO::loadMoviesIntoList, movieFilePath, movies);
	//t1.join();

	t2.join();
	// call internal loading functions

	return true;
}
