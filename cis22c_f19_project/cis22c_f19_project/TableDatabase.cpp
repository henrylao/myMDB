#include "TableDatabase.h"

void TableDatabase::__loadMovies(List<Movie>* movies)
{
	Movie newMovie;
	int MSIZE = movies->getLength();
	for (int i = 0; i < MSIZE; i++)
	{
		newMovie = movies->getEntry(i);
		__movieDB.add(newMovie.getTitle(), new Movie(newMovie));
	}
	// either delete or save internally for later use
	delete movies;

}

void TableDatabase::__loadActors(List<Actor>* actors)
{
	int ASIZE = actors->getLength();
	Actor newActor;
	for (int i = 0; i < ASIZE; i++)
	{
		newActor = actors->getEntry(i);
		__actorDB.add(newActor.getName(), newActor);
	}
	// either delete or save internally for later use
	delete actors;

}

bool TableDatabase::foundMovie(std::string key)  const
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
//bool TableDatabase::found(const Person & person) const
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

TableDatabase::~TableDatabase()
{
}

void TableDatabase::buildDatabase(std::string actorFilePath, std::string movieFilePath)
{
	List<Actor>* actors;
	List<Movie>* movies;

	std::thread t1( FileIO::loadActorsIntoList, actorFilePath, actors);
	std::thread t2( FileIO::loadMoviesIntoList, movieFilePath, movies);
	t1.join();
	t2.join();


}

void TableDatabase::displayStats() const
{
	//std::cout << "Quantity Loaded: " << __tableDB.size() << std::endl;
	//std::cout << "Max Capacity: " << __tableDB.capacity() << std::endl;
	//std::cout << "Load factor: " << __tableDB.loadFactor() << std::endl;
	//std::cout << "Collisions: " << __tableDB.collisions() << std::endl;
}
