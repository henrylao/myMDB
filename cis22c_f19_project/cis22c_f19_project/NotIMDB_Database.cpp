#include "NotIMDB_Database.h"
#include "GUI.h"
#include "SortAlgos.h"

void NotIMDB_Database::__loadMovies(List<Movie*>* movies)
{
	Movie* newMovie;
	int MSIZE;
	MSIZE = movies->getLength();
	__movieDB = new HashTable<Movie*>(MSIZE * 2.5);

	for (int i = 0; i < MSIZE; i++)
	{
		newMovie = movies->getEntry(i);

		// preprocess the key
		std::string key = newMovie->getTitle() + " " + newMovie->getYearReleased();
		key = StringUtil::lowercase(StringUtil::strip(key));	// remove whitespace and turn into lowercase
		key = StringUtil::replace(key, " ", "_");
		// add to the table
		__movieDB->add(key, newMovie);
	}
	//std::cout << *__movieDB << std::endl;	// DEBUG
	//delete movies;
}

/* create the map of bsts such that the first character of each tokenized word
signifies a key in the dictionary, does not delete the input list pointer */
void NotIMDB_Database::__buildBSTSearchEngine(List<Movie*>* movies)
{
	int SIZE = movies->getLength();
	Movie* newMovie = nullptr;
	List<std::string>* keywords;
	std::string keyword, keywords_preprocess;
	BinarySearchTree<std::string, Movie*>* found = nullptr;

	std::string firstCharOfKeyword;
	// loop the tokenization of movie attribute string == "movie_name_DDDD"
	for (int i = 0; i < SIZE; i++) {
		// get the movie
		newMovie = movies->getEntry(i);
		/*  homogenize characters in the string */
		// strip then turn into lowercase
		keywords_preprocess = StringUtil::lowercase(StringUtil::strip(newMovie->getTitle() + " " + newMovie->getYearReleased()));
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
				found = (*__searchEngineBST)[firstCharOfKeyword];
				std::string keywordFound = found->getKey(keyword);
				// simply add if keywordFound else the exception caught will signify to add the new keyword
				(*__searchEngineBST)[firstCharOfKeyword]->addValue(keyword, newMovie);
				//found.printBreadthFirst();	// DBEUG

			}
			// first character of a keyword was not found to denote a key in the table
			catch (const CustomException& e)
			{
				// create a new bst such that the first character of the keyword denotes
				// a key to a tree in the table of bst
				__searchEngineBST->add(firstCharOfKeyword,
					new BinarySearchTree<std::string, Movie*>(keywords->getEntry(j)));
				(*__searchEngineBST)[firstCharOfKeyword]->addKey(keyword);
				(*__searchEngineBST)[firstCharOfKeyword]->addValue(keyword, newMovie);
				//found.printBreadthFirst();	// DBEUG

			}
			catch (const NotFoundException& e)
			{
				// create the new node holdsing the keyword
				found->addKey(keyword);
				// append to the list of values in the newly created keyword-node
				found->addValue(keyword, newMovie);
				//found.printBreadthFirst();	// DBEUG
			}

		}
		// memory clean
		delete keywords;

	}
	found = nullptr;
}

/* Internal function for maintaining the keyword search engine
	be called during updates to a specific movie where either the year or
	the name of the movie is change update the search engine bst when edits
	are made to movies via removal
	toggle between various operations:
	toggle between various comparisons:
	1 by movieID
	2 by rating
	3 by year
	4 by title
	5 by runtime */
Movie NotIMDB_Database::__updateSearchEngineBST(const std::string newAttribute, Movie* movieToEdit, int op)
{
	// check for correct operation
	if (op < 1)
		throw CustomException("Error: Invalid Update Operation Value");

	BinarySearchTree<std::string, Movie*>* found = nullptr;
	List<std::string>* keywords;
	std::string keyword, keywords_preprocess, firstCharOfKeyword;

	// create copy of the movie
	Movie* edittedMovie = movieToEdit;

	switch (op)
	{
	case 1:
		edittedMovie->setTitle(newAttribute);
		break;
	case 2:
		edittedMovie->setYearReleased(newAttribute);
		break;
	case 3:
		edittedMovie->setID(newAttribute);
		break;
	case 4:
		edittedMovie->setRuntime(newAttribute);
		break;
	case 5:
		edittedMovie->setGenre(newAttribute);
		break;
	case 6:
		edittedMovie->setRating(newAttribute);
		break;
	default:
		break;
	}

	// preprocess keyword string
	keywords_preprocess = StringUtil::lowercase(StringUtil::strip(movieToEdit->getTitle() + " " + movieToEdit->getYearReleased()));
	keywords_preprocess = StringUtil::replace(keywords_preprocess, " ", "_");

	// tokenize the keywords
	keywords = StringUtil::split(keywords_preprocess, "|");
	// remove all matched keyword and movie pairs from the search engine
	for (int j = 0; j < keywords->getLength(); j++)
	{
		keyword = keywords->getEntry(j);
		firstCharOfKeyword = std::string(1, keyword[0]);
		try {
			// check for existence in the dictionary
			found = (*__searchEngineBST)[firstCharOfKeyword];
			// remove from target bst
			(*__searchEngineBST)[firstCharOfKeyword]->remove(keyword, movieToEdit);
		}
		catch (...)
		{
			keyword = keywords->getEntry(j);
			firstCharOfKeyword = std::string(1, keyword[0]);
			try {
				// check in the dictionary
				found = (*__searchEngineBST)[firstCharOfKeyword];
				(*__searchEngineBST)[firstCharOfKeyword]->remove(keyword, movieToEdit);
			}
			// first character of a keyword was not found to denote a key in the table
			catch (const CustomException& e)
			{
				// create a new bst such that the first character of the keyword denotes
				// a key to a tree in the table of bst
				__searchEngineBST->add(std::string(1, keywords->getEntry(j)[0]),
					new BinarySearchTree<std::string, Movie*>(keywords->getEntry(j)));

			}

		}
		delete keywords;
	}

	// Add the keyword, movie pairs for updated movie
	keywords_preprocess = StringUtil::lowercase(StringUtil::strip(edittedMovie->getTitle() + " " + edittedMovie->getYearReleased()));
	keywords_preprocess = StringUtil::replace(keywords_preprocess, " ", "_");
	keywords = StringUtil::split(keywords_preprocess, "_");
	int SIZE = keywords->getLength();
	for (int i = 0; i < SIZE; i++)
	{
		keyword = keywords->getEntry(i);
		firstCharOfKeyword = std::string(1, keyword[0]);
		try {
			// check in the dictionary
			found = (*__searchEngineBST)[firstCharOfKeyword];
			std::string keywordFound = found->getKey(keyword);
			// simply add if keywordFound else the exception caught will signify to add the new keyword
			(*__searchEngineBST)[firstCharOfKeyword]->addValue(keyword, edittedMovie);
			//found.printBreadthFirst();	// DBEUG

		}
		// first character of a keyword was not found to denote a key in the table
		catch (const CustomException& e)
		{
			// create a new bst such that the first character of the keyword denotes
			// a key to a tree in the table of bst
			__searchEngineBST->add(firstCharOfKeyword,
				new BinarySearchTree<std::string, Movie*>(keywords->getEntry(i)));
			(*__searchEngineBST)[firstCharOfKeyword]->addKey(keyword);
			(*__searchEngineBST)[firstCharOfKeyword]->addValue(keyword, edittedMovie);
			//found.printBreadthFirst();	// DBEUG

		}
		catch (const NotFoundException& e)
		{
			// create the new node holdsing the keyword
			found->addKey(keyword);
			// append to the list of values in the newly created keyword-node
			found->addValue(keyword, edittedMovie);
			//found.printBreadthFirst();	// DBEUG
		}
		delete keywords;
	}
}

List<Movie*>* NotIMDB_Database::__getKeywordWeightedMovies(const std::string & searchEntry) const
{
	// process search entry
	std::string processedKey = __processSearchEntry(searchEntry);
	// table for tallying occurences in the bst
	HashTable<int> movieTallyTable;
	// tokenize the processed search entry
	List<std::string>* keywords = StringUtil::split(processedKey, "_");
	List<Movie*>* sortedByWeightMovies = new List<Movie*>();

	/* Find all relevant keyword relations to movies */
	// variables for accessing table of BSTs
	std::string keyword;
	int SIZE = keywords->getLength();
	std::string firstCharOfKeyword;
	// for each keyword get the bst associated with the first character of the keyword
	for (int i = 0; i < SIZE; i++)
	{
		// new list of movies for each keyword in a loop
		List<Movie*> moviesByKeyword;
		keyword = keywords->getEntry(i);
		firstCharOfKeyword = std::string(1, keyword[0]);
		// verified key case
		try {
			std::string keyFound = __searchEngineBST->get(firstCharOfKeyword)->getKey(keyword);
			BinarySearchTree<std::string, Movie*>* keywordTree = (__searchEngineBST->get(firstCharOfKeyword));
			for (int i = 0; i < keywordTree->getValues(keyword)->getLength(); i++)
			{
				//std::cout << *keywordTree->getValues(keyword) << std::endl;			 // DEBUG
				moviesByKeyword.append(keywordTree->getValues(keyword)->getEntry(i));
			}
			//.getValues(keyword) << std::endl;
			int MBK_SIZE = moviesByKeyword.getLength();
			// loop through the list of values from
			for (int j = 0; j < MBK_SIZE; j++)
			{
				// create the processedMovieName
				std::string processedMovieName = moviesByKeyword.getEntry(j)->getTitle()
					+ " " + moviesByKeyword.getEntry(j)->getYearReleased();
				try {
					processedMovieName = __processSearchEntry(processedMovieName);
					// if an associated weight exists for the movie increment by 1
					int found = movieTallyTable[processedMovieName];
					movieTallyTable[processedMovieName] += 1;
				}
				// processed movie title does not exist in the table of weighted movies
				catch (const CustomException& e)
				{
					movieTallyTable.add(processedMovieName, 1);
				}
			}
		}
		// key not found in any node of tree
		catch (...) { 
			// do nothing
		}
	}
	/* Finally check for an exact match == movie_name_and_year
	and give weight to the exact match denoted by a percentage of
	the summed values of the keys in the tally table */
	bool foundExact = false;
	size_t WMT_SIZE = movieTallyTable.size();
	try {
		Movie* exactMovie = (*__movieDB)[processedKey];
		exactMovie = nullptr;
		foundExact = true;
	}
	catch (...)
	{
		// do nothing 
	}
	List<std::string> WMT_KEYS = movieTallyTable.keys();
	int sumOfWeight = 0;
	if (foundExact)
	{
		for (int i = 0; i < movieTallyTable.size(); i++)
			sumOfWeight += movieTallyTable[WMT_KEYS.getEntry(i)];

		movieTallyTable[processedKey] += (sumOfWeight * .75);
	}

	// build the array of movies sorted by their tallied values
	Pair<Movie*, int>** weightMoviesArr = new Pair<Movie*, int>*[WMT_SIZE];

	for (size_t i = 0; i < WMT_SIZE; i++)
	{
		std::string key = WMT_KEYS.getEntry(i);
		//std::cout << (*__movieDB)[key] << std::endl;	// DEBUG
		weightMoviesArr[i] = new Pair<Movie*, int>();
		weightMoviesArr[i]->setCompareByValue();
		// movie addresses to be added 
		weightMoviesArr[i]->setKey((*__movieDB)[key]);
		weightMoviesArr[i]->setValue(movieTallyTable[key]);
		// movies are created in ascending order
		//std::cout << weightMoviesArr[i]->getKey() << std::endl;	// DEBUG
	}
	// sort pairs of Movie & Weight by their weight
	SortUtil::quickSort(weightMoviesArr, 0, WMT_SIZE - 1);
	//std::cout << "Post Sort" << std::endl;	// DEBUG
	for (size_t i = 0; i < WMT_SIZE; i++)
	{
		//std::cout << *weightMoviesArr[i]->getKey() << std::endl; // DEBUG

		sortedByWeightMovies->append(weightMoviesArr[i]->getKey());
		// movies are created in ascending order
	}
	if (movieTallyTable.keys().getLength() == 0)
		return new List<Movie*>();
	for (size_t i = 0; i < WMT_SIZE; i++)
	{
		delete weightMoviesArr[i];
	}
	delete[] weightMoviesArr;
	// mem clean
	return sortedByWeightMovies;
}

std::string NotIMDB_Database::__processSearchEntry(const std::string & query) const
{
	std::string processedKey = StringUtil::lowercase(StringUtil::strip(query));
	processedKey = StringUtil::replace(processedKey, " ", "_");
	return processedKey;
}

void NotIMDB_Database::__searchEngineDeletionHandler(Movie * movieToDelete)
{
	std::string unprocessedKey = movieToDelete->getTitle() + " " + movieToDelete->getYearReleased();
	std::string processedKey = __processSearchEntry(unprocessedKey);
	List<std::string>* keywords = StringUtil::split(processedKey, "_");
	int SIZE = keywords->getLength();
	std::string firstCharOfKeyword;
	std::string keyword;

	// loop through each keyword to find the appropriate bst to delete from
	for (int i = 0; i < SIZE; i++)
	{
		keyword = keywords->getEntry(i);
		firstCharOfKeyword = std::string(1, keyword[0]);
		// verified key case
		try {
			std::string keyFound = __searchEngineBST->get(firstCharOfKeyword)->getKey(keyword);
			List<Movie*>* keywordMovies = __searchEngineBST->get(firstCharOfKeyword)->getValues(keyFound);
			keywordMovies->removeByValue(movieToDelete);
		}
		// regardless of what the exception thrown is key not found in any node of tree 
		catch (...)
		{
			// do nothing 
		}
	}
}

void NotIMDB_Database::testKeywordWeightedSearch(const std::string & searchEntry) const
{
	List<Movie*>* weightedMovies = nullptr;
	weightedMovies = __getKeywordWeightedMovies(searchEntry);
	if (weightedMovies->getLength() == 0)
		std::cout << "There were no matches for your search\n";
	else
	{
		int size = weightedMovies->getLength();
		if (size > 20)
		{
			for (int i = 0; i < 21; i++)
				std::cout << *weightedMovies->getEntry(i) << std::endl;
		}
		else
		{
			for (int i = 0; i < size; i++)
				std::cout << *weightedMovies->getEntry(i) << std::endl;
		}
	}
	// clean up memory allocated for list only
	delete weightedMovies;
}

bool NotIMDB_Database::foundMovie(std::string key) const
{
	Movie* found;
	try {
		found = (*__movieDB)[key];
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
	__movieDB->showStats();
}

/* Gets a list of movies sorted in descending order of keyword occurences in the search engine
sets the passed exactMatch to true if an exact match was found 
@pre exactMatch is unknown 
@post confirmation of exactMatch and a list of movies if found 
@param key any keyword
@return pointer to a list of movies */
List<Movie>* NotIMDB_Database::readMovie(std::string key, bool& exactMatch) const
{
	std::string processedKey = StringUtil::lowercase(StringUtil::strip(key));
	processedKey = StringUtil::replace(processedKey, " ", "_");
	List<Movie>* listOfMoviesByWeight = new List<Movie>();
	if (foundMovie(processedKey) == true)
		exactMatch = true;
	else
		exactMatch = false;
	// get all related movies to a tokenized keyword if any 
	List<Movie*> weightedMovies = *__getKeywordWeightedMovies(processedKey);
	if (weightedMovies.getLength() > 0)
	{
		// add weighted movies to the list
		for (int i = 0; i < (weightedMovies).getLength(); i++)
		{
			listOfMoviesByWeight->append(*(weightedMovies).getEntry(i));
		}
	}
	return listOfMoviesByWeight;
}


void NotIMDB_Database::displaySearchEngineState() const
{
	List<std::string> keys = __searchEngineBST->keys();
	int SIZE = keys.getLength();
	for (int i = 0; i < SIZE; i++)
	{
		std::cout << keys.getEntry(i);
	}
	/* DEBUG Keyword Search Engine*/
	BinarySearchTree<std::string, Movie> found;
	for (int i = 0; i < SIZE; i++)
	{
		std::cout << GUI::divider << std::endl;
		std::cout << "BST in table at keyword char: " << keys.getEntry(i) << std::endl;
		std::cout << "Depth-first: " << std::endl;
		//found = (*__searchEngineBST)[keys.getEntry(i)];
		//found.printBreadthFirst();
		(*__searchEngineBST)[keys.getEntry(i)]->printBreadthFirst();
	}
	// call internal loading functions
	std::cout << __searchEngineBST->size() << std::endl;	// DEBUG
}

void NotIMDB_Database::unitTest()
{
	std::string divider = "--------------------------------";
	std::string path = "title_basics_cleaned_final_full_50000.tsv";
	NotIMDB_Database db;
	bool exactMatchFound = false;
	db.loadFromFile(path);
	db.readMovie("Miss Jerry", exactMatchFound);
	db.saveToFile("output.tsv");

	std::cout << divider << std::endl;
	std::cout << "Pre-delete:" << std::endl;
	db.displayMovieTableStats();
	std::cout << divider << std::endl;

	std::cout << "Post-delete:" << std::endl;
	db.displayMovieTableStats();
	std::cout << divider << std::endl;

	db.showMostRecentDelete();
	db.undoMostRecentDelete();
	std::cout << divider << std::endl;
	db.readMovie("Miss Jerry", exactMatchFound);
	path = "data\\full\\title_basics_cleaned_final_trimmed2.tsv";
	List<Movie*>* movies = FileIO::buildMovieList(path);
	db.createMovie(*movies->getEntry(5));
	db.displayMovieTableStats();
	db.displaySearchEngineState();
	db.updateMovieName("Miss Jerry 1894", "Mister Jerry");

	db.displaySearchEngineState();	// BUGGED
	db.testKeywordWeightedSearch("Miss Jerry");
	db.updateMovieName("Miss Jerry 1894", "Mister Jerry");
	db.displaySearchEngineState();	// BUGGED
	db.testKeywordWeightedSearch("Miss");
	db.testKeywordWeightedSearch("El blocao 1909");

	for (int i = 0; i < movies->getLength(); i++)
	{
		delete movies->getEntry(i);
	}
	delete movies;
}



NotIMDB_Database::~NotIMDB_Database()
{
	// memory clean search engine does not delete movie addresses
	std::string key = "";
	List<std::string> keys = __searchEngineBST->keys();
	for (int i = 0; i < __searchEngineBST->keys().getLength(); i++)
	{
		key = keys.getEntry(i);
		// clean mem alloc for a bst
		delete __searchEngineBST->get(key);
	}
	// clean mem alloc for table of bst
	delete __searchEngineBST;

	/*delete stack all existing movies in memory
	are deleted using keys stored in the table */
	int SSIZE = __deletedMovies->size();
	for (int i = 0; i < SSIZE; i++)
	{
		// delete mem alloc to movies that no longer exist in table
		Movie* toDelete = __deletedMovies->peek();
		delete toDelete;
		__deletedMovies->pop();
		toDelete = nullptr;
	}
	// clean mem alloc to the stack
	delete __deletedMovies;

	// memory clean movie table removing mem alloc for movies and the table
	size_t SIZE = __movieDB->size();
	keys = __movieDB->keys();
	List<std::string> MKEYS = __movieDB->keys();

	Movie* toDelete = nullptr;
	for (size_t i = 0; i < SIZE; i++)
	{
		key = MKEYS.getEntry(i);
		// delete mem alloc to movies
		toDelete = __movieDB->get(key);
		if (toDelete != nullptr)
			delete toDelete;
	}
	toDelete = nullptr;
	// clean mem alloc table
	delete __movieDB;
}


bool NotIMDB_Database::loadFromFile(std::string path)
{
	List<Movie*>* movies;

	// allocate memory for a list to contain movie values
	auto start = std::chrono::high_resolution_clock::now();
	movies = FileIO::buildMovieList(path);
	auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = finish - start;
	std::string listStatsLabel = "|\tList of Movies Generation Time\t\t\t|\t" 
		+ std::to_string(elapsed.count()) + "s\t|\n";
	std::cout << GUI::divider << GUI::divider << "-----\n";
	std::cout << listStatsLabel;
	std::cout << GUI::divider << GUI::divider << "-----\n";

	// create table of movies
	start = std::chrono::high_resolution_clock::now();
	__loadMovies(movies);
	finish = std::chrono::high_resolution_clock::now();
	elapsed = finish - start;
	std::cout << "|\tMovie Load From List to Table Time\t\t|\t" << elapsed.count() << "s\t|\n";
	std::cout << GUI::divider << GUI::divider << "-----\n";

	// create search engine
	start = std::chrono::high_resolution_clock::now();
	__buildBSTSearchEngine(movies);
	finish = std::chrono::high_resolution_clock::now();
	elapsed = finish - start;
	std::cout << "|\tTabled BST Search Engine Time\t\t\t|\t" << elapsed.count() << "s\t|\n";
	std::cout << GUI::divider << GUI::divider << "-----\n";


	/* Show statistics of movie table */
	std::cout << "\n\n";
	std::cout << GUI::divider << "------------\n";
	std::string movieStatsLabel = "|\t\tMovie Table Statistics\t\t|\n";
	std::cout << movieStatsLabel;
	std::cout << GUI::divider << "------------\n";
	__movieDB->showStats();
	std::cout << GUI::divider << "------------\n";

	/* Show statistics of search engine table */
	std::cout << "\n\n";
	std::cout << GUI::divider << "------------\n";
	std::string searchEngineLabel = "|\tTabled BST Search Engine Statistics\t|\n";
	std::cout << searchEngineLabel;
	std::cout << GUI::divider << "------------\n";
	__searchEngineBST->showStats();

	std::cout << GUI::divider << "------------\n";
	// list memory clean
	delete movies;
	return true;
}

void NotIMDB_Database::saveToFile(string path)
{
	std::ofstream outfile;
	outfile.open(path, std::ios::out);

	std::string out = "";
	int MSIZE = (int)__movieDB->size();
	Movie* temp;
	for (int i = 0; i < MSIZE; i++)
	{
		temp = (*__movieDB)[__movieDB->keys().getEntry(i)];
		out = temp->getID() + " | "
			+ temp->getTitle() + " | "
			+ temp->getYearReleased() + " | "
			+ temp->getRuntime() + " | "
			+ temp->getGenres() + "\n";
		outfile << out;
	}
	outfile.close();
}


bool NotIMDB_Database::deleteMovie(std::string key)
{
	// clean and process to format that can be handled by the database
	std::string processedKey = __processSearchEntry(key);
	try {
		// pointer to hold address of movie to be removed
		Movie* deletedMovie = nullptr;
		deletedMovie = (*__movieDB)[processedKey];
		// removes the address stored in the table therefore no longer exists in the table
		__movieDB->remove(processedKey);
		// pushes the movie onto the undo-stack
		__deletedMovies->push(deletedMovie);
		__searchEngineDeletionHandler(deletedMovie);
		return true;
	}
	catch (const CustomException& e)
	{
		return false;
	}
	return false;
}

bool NotIMDB_Database::undoMostRecentDelete()
{
	Movie* movieDeleted;
	if (__deletedMovies->size() > 0)
	{
		movieDeleted = __deletedMovies->peek();
		__deletedMovies->pop();
	}
	__movieDB->add(movieDeleted->getTitle(), movieDeleted);
	return false;
}

void NotIMDB_Database::showMostRecentDelete() const
{
	if (__deletedMovies->size() > 0)
		std::cout << __deletedMovies->peek() << std::endl;
}

bool NotIMDB_Database::updateMovieName(std::string oldMovieName, std::string newMovieName)
{
	// check for existence
	if (!foundMovie(oldMovieName))
		return false;
	Movie edittedMovie = __updateSearchEngineBST(newMovieName, (*__movieDB)[oldMovieName], 1);
	(*__movieDB)[newMovieName] = new Movie(edittedMovie);
	return true;
}

bool NotIMDB_Database::updateMovieYear(std::string key, std::string newYearReleased)
{
	try {
		std::string processedKey = __processSearchEntry(key);
		Movie newMovie = __updateSearchEngineBST(newYearReleased, (*__movieDB)[processedKey], 2);
		(*__movieDB)[processedKey] = new Movie(newMovie);
		return true;
	}
	catch (CustomException e)
	{
		std::cout << e.getMessage() << std::endl;
	}
	return false;
}

bool NotIMDB_Database::updateMovieID(std::string key, std::string newID)
{
	try {
		std::string processedKey = __processSearchEntry(key);
		Movie newMovie = __updateSearchEngineBST(newID, (*__movieDB)[processedKey], 3);
		delete (*__movieDB)[processedKey];
		(*__movieDB)[processedKey] = new Movie(newMovie);
		return true;
	}
	catch (CustomException e)
	{
		std::cout << e.getMessage() << std::endl;
	}
	return false;
}

bool NotIMDB_Database::updateMovieRuntime(std::string key, std::string newRuntime)
{
	try {
		std::string processedKey = __processSearchEntry(key);
		Movie newMovie = __updateSearchEngineBST(newRuntime, (*__movieDB)[processedKey], 4);
		delete (*__movieDB)[processedKey];
		(*__movieDB)[processedKey] = new Movie(newMovie);		return true;
	}
	catch (CustomException e)
	{
		std::cout << e.getMessage() << std::endl;
	}
	return false;
}

bool NotIMDB_Database::updateMovieGenre(std::string key, std::string newGenreName, int op)
{
	try {
		std::string processedKey = __processSearchEntry(key);
		std::string genres;
		if (op)
			genres = newGenreName;
		else
			genres = (*__movieDB)[processedKey]->getGenres().append(newGenreName);
		Movie newMovie = __updateSearchEngineBST(genres, (*__movieDB)[processedKey], 5);
		delete (*__movieDB)[processedKey];
		(*__movieDB)[processedKey] = new Movie(newMovie);		return true;
	}
	catch (CustomException e)
	{
		std::cout << e.getMessage() << std::endl;
	}
	return false;
}
bool NotIMDB_Database::updateMovieRating(std::string key, std::string newKey)
{
	try {
		std::string processedKey = __processSearchEntry(key);
		Movie newMovie = __updateSearchEngineBST(newKey, (*__movieDB)[processedKey], 6);
		delete (*__movieDB)[processedKey];
		(*__movieDB)[processedKey] = new Movie(newMovie);
		return true;
	}
	catch (CustomException e)
	{
		std::cout << e.getMessage() << std::endl;
	}
	return false;
}
