#include "FileIO.h"

List<Movie>* FileIO::buildMovieList(std::string path)
{
	// attempt open file
	std::ifstream infile;
	std::string data;
	infile.open(path, std::ios::in);

	// handle bad file path case
	if (!infile.good())
		return nullptr;

	// begin populating
	Movie newMovie;
	List<Movie>* movies = new List<Movie>();
	List<std::string>* dataList;
	std::string genres;
	while (infile.good())
	{
		getline(infile, data);	// read entire line
		data = StringUtil::strip(data);
		if (data.length() > 0)
		{
			dataList = StringUtil::split(data, "|");
			//cout << *dataList << endl;	// DEBUG
			//std::cout << data << std::endl;
			genres = StringUtil::strip(dataList->getEntry(dataList->getLength() - 1));
			//cout << *genres << endl;	// DEBUG
			newMovie = Movie((*dataList)[0], (*dataList)[1], (*dataList)[2], (*dataList)[3], genres);
			//cout << newMovie << endl;	// DEBUG 
			data = "";
			delete dataList;
			movies->append(newMovie);
		}
		
	}
	return movies;
}

List<Actor>* FileIO::buildActorList(std::string path)
{
	std::ifstream infile;
	std::string data;
	infile.open(path, std::ios::in);

	// begin populating
	Actor newActor;
	List<Actor>* actors = new List<Actor>();
	List<std::string>* dataList;
	List<std::string>* movieIDs;
	while (infile.good())
	{
		getline(infile, data);	// read entire line
		data = StringUtil::strip(data);	// remove whitespaces
		if (data.length() > 0)
		{
			dataList = StringUtil::split(data, "|");	// split from the delim to create a list
			//cout << *dataList << endl;	// DEBUG
			//std::cout << data << std::endl;
			// last entry of the data list contains a list of associated movieID tags
			movieIDs = StringUtil::split(dataList->getEntry(dataList->getLength() - 1), ",");
			// populate the new actor
			newActor = Actor((*dataList)[0], (*dataList)[1], (*dataList)[2], (*dataList)[3],
				(*dataList)[4], *movieIDs);
			//cout << newMovie << endl;	// DEBUG 
			data = "";
			// memory clean up
			delete dataList;
			delete movieIDs;
			// add new actor to the list
			actors->append(newActor);
		}

	}
	return actors;
}

void FileIO::buildMovieTitles_sortedByID(std::string path, List<std::string>* movieTitles)
{
	std::ifstream infile;
	infile.open(path, std::ios::in);
	if (!infile.good())
	{
		return;
	}

	std::string data;
	while (infile.good())
	{
		if (getline(infile, data, '\n'))
		{
			data = StringUtil::strip(data);
			if (data.length() != 0)
			{
				movieTitles->append(data);
			}
			// reset after appending or a whitespace has been read
			data = "";
		}
	}
	return;
}
