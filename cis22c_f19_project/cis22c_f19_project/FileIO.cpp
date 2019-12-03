#include "FileIO.h"

List<Person>* FileIO::buildPersonListFromFile(std::string path)
{
	std::ifstream infile;
	List<Person>* people = new List<Person>();
	infile.open(path, std::ios::in);
	List<std::string>* date_tokens;
	Person* new_person = new Person();
	if (!infile.good())
		return nullptr;
	std::string data;

	// build PersonDatabase
	while (infile.good())
	{
		getline(infile, data, '\n');
		data = StringUtil::strip(data);
		// date found case
		if (isdigit(data[0]))
		{
			date_tokens = StringUtil::split(data, "-");
			new_person->setYear(date_tokens->getEntry(0));
			new_person->setMonth(date_tokens->getEntry(1));
			new_person->setDay(date_tokens->getEntry(2));
			date_tokens->clear();
			delete date_tokens;
		}
		// name found case
		else if (isalpha(data[0]))
		{
			new_person->setName(data);
		}
		
		if (new_person->getBirthday().length() != 2 && new_person->getName().length() != 0)
		{
			people->append(*new_person);
			delete new_person;
			new_person = new Person();
		}
		// reset the date string for next line
		data = "";
	}
	// memory clean up
	if (new_person->getBirthday().length() == 0 || new_person->getName().length() == 0)
	{
		delete new_person;
	}
	return people;
}


List<std::string>* FileIO::buildNameListFromFile(std::string path)
{
	std::ifstream infile;
	List<std::string>* names = new List<std::string>();
	infile.open(path, std::ios::in);

	if (!infile.good())
		return nullptr;

	std::string name;
	while (infile.good())
	{
		if (getline(infile, name, '\n'))
		{
			name = StringUtil::strip(name);
			if (name.length() != 0)
			{
				names->append(name);
			}
			// reset after appending or a whitespace has been read
			name = "";
		}
	}
	return names;
}
List<std::string>* FileIO::buildDateListFromFile(std::string path)
{
	std::ifstream infile;
	List<std::string>* dates = new List<std::string>();
	infile.open(path, std::ios::in);
	if (!infile.good())
		return nullptr;

	std::string date;
	while (infile.good())
	{
		if (getline(infile, date, '\n'))
		{
			date = StringUtil::strip(date);
			if (date.length() != 0)
			{
				dates->append(date);
			}
			// reset after appending or a whitespace has been read
			date = "";
		}
	}
	return dates;
}

void FileIO::writeTableToFile(std::string path,
	const List<std::string>& keys,  HashTable<Person>& table)
{
	std::ofstream outfile;
	outfile.open(path, std::ios::out);

	for (int i = 0; i < keys.getLength(); i++)
	{
		outfile << table[keys.getEntry(i)].getName() << std::endl << keys.getEntry(i) << std::endl;
	}
	outfile.close();
}

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
			movies->sortedInsert(newMovie);
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

void FileIO::loadActorsIntoList(std::string path, List<Actor>* actors)
{
	actors = buildActorList(path);
}

void FileIO::loadMoviesIntoList(std::string path, List<Movie>* movies)
{
	movies = buildMovieList(path);
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
