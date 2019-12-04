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
	List<std::string>* dataList = nullptr;	// data tokenized 
	std::string genres;
	while (infile.good())
	{
		try {
			getline(infile, data);	// read entire line
			data = StringUtil::strip(data);
			dataList = StringUtil::split(data, "|");
			if (data != "" && dataList->getLength() == 5)
			{
				
				//cout << *dataList << endl;	// DEBUG
				//std::cout << data << std::endl;
				genres = dataList->getEntry(dataList->getLength() - 1);
				//cout << *genres << endl;	// DEBUG
				newMovie = Movie((*dataList)[0], (*dataList)[1], (*dataList)[2], (*dataList)[3], genres);
				//cout << newMovie << endl;	// DEBUG
				data = "";
				genres = "";
				delete dataList;
				movies->append(newMovie);
			}
		}
		catch (...)
		{
			std::cout << newMovie << std::endl;
			std::cout << *movies << std::endl;
			std::cout << genres << std::endl;
			if (dataList != nullptr)
				std::cout << *dataList << std::endl;
		}
		

	}
	return movies;
}
void FileIO::loadMoviesIntoList(std::string path, List<Movie>* movies)
{
	movies = buildMovieList(path);
}
