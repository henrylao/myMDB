#include "NotIMDB_Database.h"

void NotIMDB_Database::__loadMovies(List<Movie>* movies)
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

void NotIMDB_Database::__loadActors(List<Actor>* actors)
{

	int ASIZE = actors->getLength();
	Actor newActor;
	/* Create list of movie titles sorted by their movieID */
	//list containing str of "movieIDs, movieTitle"
	List<std::string> movieIDs;
	std::ifstream infile;
	infile.open("sorted_movie_tags.tsv", std::ios::in);
	std::string data; 
	while (infile.good())
	{
		// read infile into data
		std::getline(infile, data);
		// remove white spaces if any
		data = StringUtil::strip(data);
		// append the movieTag with the associated title
		movieIDs.append(data);
	}

	/* Populate the list of movie titles contained in actor using the 
	previously created list, verified via the 
	movieID-list inside of actor */
	int ID_SIZE;
	for (int i = 0; i < ASIZE; i++)
	{
		
		newActor = actors->getEntry(i);
		List<std::string> movieIDs = newActor.getMovieIDs();
		ID_SIZE = movieIDs.getLength();
		for (int i = 0; i < ID_SIZE; i++)
		{
			// binarily search for movieIDs in an actor 
			// in the sorted movieID list from file and add the pointer to
			// the actor 
		}
	}

	/* Add the completed actor objects to the table database */
	for (int i = 0; i < ASIZE; i++)
	{
		newActor = actors->getEntry(i);
		
		__actorDB.add(newActor.getName(), newActor);
	}
	// either delete or save internally for later use
	delete actors;

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
}

bool NotIMDB_Database::loadFromFile(std::string actorFilePath, std::string movieFilePath)
{
	List<Actor>* actors;
	List<Movie>* movies;

	std::thread t1( FileIO::loadActorsIntoList, actorFilePath, actors);
	std::thread t2( FileIO::loadMoviesIntoList, movieFilePath, movies);
	t1.join();
	t2.join();

	return true;
}
