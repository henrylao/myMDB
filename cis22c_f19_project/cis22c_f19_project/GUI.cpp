#include "GUI.h"

bool GUI::isValidName(std::string name)
{
	int size = name.size();
	for (int i = 0; i < size; i++)
	{
		if (!isalpha(name[i]) && isdigit(name[i]))
			return false;
	}
	return true;
}

bool GUI::isValidMonth(std::string month)
{
	int size = month.size();
	if (size != 2 || stoi(month) > 12 || stoi(month) < 1)
		return false;
	for (int i = 0; i < size; i++)
	{
		if (isalpha(month[i]))
			return false;
	}
	return true;
}

bool GUI::isValidDay(std::string day)
{
	int size = day.size();
	if (size != 2 || stoi(day) > 31 || stoi(day) < 1)
		return false;
	for (int i = 0; i < size; i++)
	{
		if (isalpha(day[i]))
			return false;
	}
	return true;
}

bool GUI::isValidYear(std::string year)
{
	int size = year.size();
	if (size > 4 || size != 4)
		return false;
	for (int i = 0; i < size; i++)
	{
		if (isalpha(year[i]))
			return false;
	}
	return true;
}

void GUI::UI_search(const NotIMDB_Database &db)
{
	int currentIndex = 0;
	int counter = 0;
	bool doneScrolling = false;
	bool doneSearching = false;
	bool exactMatch = false;
	while (!doneSearching) {
		std::string user_in;
		std::cout << "Please enter any keywords related to the movie youd like to search: " << std::endl;
		getline(std::cin, user_in);
	
		if (StringUtil::strip(user_in).length() < 1)
		{
			int choice;
			std::cout << "I couldn't process your input\n";
			choice = menu_prompt("What would you like to do?", menu_continue_search, 2);
			if (choice == 2)
			{
				break;
			}
		}
		else {
			List<Movie>* keywordMovies = db.readMovies(user_in, exactMatch);
			const int START = 0;
			const int MSIZE = keywordMovies->getLength();
			const int END = MSIZE - 1;
			if (keywordMovies->getLength() == 0)
			{
				int choice;
				std::cout << "I couldn't find an exact match in the database.\n";
				std::cout << "Also, I couldn't find other related matches...\n" << std::endl;
				choice = menu_prompt("What would you like to do?", menu_continue_search, 2);
				if (choice == 2)
				{
					break;
				}
			}
			else if (exactMatch)
			{
				std::cout << "I found an exact match in the database.\n" << keywordMovies->getEntry(0) << std::endl;
				std::cout << "I also found other related matches as well...\n" << std::endl;

				int choice;
				choice = menu_prompt("Would you like to see them?", menu_yes_no, 2);
				// only exact match case
				if (choice == 2)
				{
					choice = menu_prompt("What would you like to do?", menu_continue_search, 2);
					if (choice == 2)
					{
						break;
					}
				}
				// scroll through list
				else 
				{

					// show initial found
					int counter = 0;
					int optionNum = 1;
					int currentPos = 0;
					std::cout << divider << std::endl;
					std::cout << "I found a total of " << MSIZE << " movie(s) related to your search\n";
					// exit case 
					if (MSIZE > 3)
					{
						std::cout << "Here are the first 3 entries:\n" <<
							keywordMovies->getEntry(0) << divider << "\n" <<
							keywordMovies->getEntry(1) << divider << "\n" <<
							keywordMovies->getEntry(2) << divider << "\n";
						currentPos = 3;
					}
					else
					{
						for (int i = 0; i < MSIZE; i++)
						{
							std::cout << keywordMovies->getEntry(i) << std::endl;
							std::cout << divider << std::endl;
							currentPos++;
						}
					}
					// resets from the end of case 1 to allow use mobility
					doneScrolling = false;
					while (!doneScrolling) {
						// scrolls by 1 movie each time
						choice = menu_prompt("What would you like to do?", menu_search_scroll, 6);
						std::cout << divider << endl;
						switch (choice)
						{
							// view next set 
						case 1:
						{
							currentIndex += 3;
							if (currentIndex == END || currentIndex > END) {
								std::cout << "We can't go further forward\n";
							}
							//  reposition accordingly to redisplay current state
							if (currentIndex > MSIZE)
								currentIndex = MSIZE - 3;
							if (currentIndex < 0)
								currentIndex = 0;
							// attempt to show the next 3- 4 movies
							while (counter < 3 && currentIndex < MSIZE)
							{
								std::cout << keywordMovies->getEntry(currentIndex) << divider << "\n";
								counter++;
								currentIndex++;
							}
							counter = 0;
							break;
						}
						// view prev. set 
						case 2:
						{
							currentIndex -= 3;
							if (currentIndex == START || currentIndex) {
								std::cout << "We can't go further back\n";
							}
							if (currentIndex < 0)
								currentIndex = 0;
							// attempt to show the next 3- 4 movies
							while (counter < 3 && currentIndex < MSIZE)
							{
								std::cout << keywordMovies->getEntry(currentIndex) << divider << "\n";
								counter++;
								currentIndex++;
							}
							counter = 0;
							break;
						}
						// go to the start of the list showing first few results
						case 3:
						{
							currentIndex = 0;
							while (counter < 3 && currentIndex < MSIZE)
							{
								std::cout << keywordMovies->getEntry(currentIndex) << divider << "\n";
								counter++;
								currentIndex++;
							}
							counter = 0;
							break;
						}
						// go to the end of the list showing the last few results ~3/4
						case 4:
						{
							currentIndex = END - 3;
							if (currentIndex > MSIZE)
								currentIndex = MSIZE - 3;
							// handle small list case
							if (currentIndex < 0)
								currentIndex = 0;
							// attempt to show the next 3- 4 movies
							while (counter < 3 && currentIndex < MSIZE)
							{
								std::cout << keywordMovies->getEntry(currentIndex) << divider << "\n";
								counter++;
								currentIndex++;
							}
							counter = 0;
							break;
						}
						case 5:
							doneScrolling = true;
							break;
						case 6:
							doneScrolling = true;
							return;
							break;
						}
						
					} // end scroll loop
				}
			}
			else {
				std::cout << divider << endl;

				std::cout << "I couldn't find an exact match in the database.\n";
				std::cout << "But, I did find other related matches though...\n" << std::endl;
				int choice;
				choice = menu_prompt("Would you like to see them?", menu_yes_no, 2);
				std::cout << divider << endl;

				// only exact match case
				if (choice == 2)
				{
					choice = menu_prompt("What would you like to do?", menu_continue_search, 2);

					if (choice == 2)
					{
						std::cout << divider << endl;
						break;
					}
				}
				// scroll through list
				else {
					// show initial found
					int counter = 0;
					int optionNum = 1;
					int currentPos = 0;
					std::cout << divider << std::endl;
					std::cout << "I found a total of " << MSIZE << " movie(s) related to your search\n";
					// exit case 
					if (MSIZE > 3)
					{
						std::cout << "Here are the first 3 entries:\n" <<
							keywordMovies->getEntry(0) << divider << "\n" <<
							keywordMovies->getEntry(1) << divider << "\n" <<
							keywordMovies->getEntry(2) << divider << "\n";
						currentPos = 3;
					}
					else
					{
						for (int i = 0; i < MSIZE; i++)
						{
							std::cout << keywordMovies->getEntry(i) << std::endl;
							std::cout << divider << std::endl;
							currentPos++;
						}
					}
					// resets from the end of case 1 to allow use mobility
					doneScrolling = false;

					while (!doneScrolling) {
						// scrolls by 1 movie each time
						choice = menu_prompt("What would you like to do?", menu_search_scroll, 6);
						std::cout << divider << endl;
						switch (choice)
						{
							// view next set 
						case 1:
						{
							currentIndex += 3;
							if (currentIndex == END || currentIndex > END) {
								std::cout << "We can't go further forward\n";
							}
							//  reposition accordingly to redisplay current state
							if (currentIndex > MSIZE)
								currentIndex = MSIZE - 3;
							if (currentIndex < 0)
								currentIndex = 0;
							// attempt to show the next 3- 4 movies
							while (counter < 3 && currentIndex < MSIZE)
							{
								std::cout << keywordMovies->getEntry(currentIndex) << divider << "\n";
								counter++;
								currentIndex++;
							}
							counter = 0;
							break;
						}
						// view prev. set 
						case 2:
						{
							currentIndex -= 3;
							if (currentIndex == START || currentIndex) {
								std::cout << "We can't go further back\n";
							}
							if (currentIndex < 0)
								currentIndex = 0;
							// attempt to show the next 3- 4 movies
							while (counter < 3 && currentIndex < MSIZE)
							{
								std::cout << keywordMovies->getEntry(currentIndex) << divider << "\n";
								counter++;
								currentIndex++;
							}
							counter = 0;
							break;
						}
						// go to the start of the list showing first few results
						case 3:
						{
							currentIndex = 0;
							while (counter < 3 && currentIndex < MSIZE)
							{
								std::cout << keywordMovies->getEntry(currentIndex) << divider << "\n";
								counter++;
								currentIndex++;
							}
							counter = 0;
							break;
						}
						// go to the end of the list showing the last few results ~3/4
						case 4:
						{
							currentIndex = END - 3;
							if (currentIndex > MSIZE)
								currentIndex = MSIZE - 3;
							// handle small list case
							if (currentIndex < 0)
								currentIndex = 0;
							// attempt to show the next 3- 4 movies
							while (counter < 3 && currentIndex < MSIZE)
							{
								std::cout << keywordMovies->getEntry(currentIndex) << divider << "\n";
								counter++;
								currentIndex++;
							}
							counter = 0;
							break;
						}
						case 5:
							doneScrolling = true;
							break;
						case 6:
							doneScrolling = true;
							return;
							break;
						}
					} // end scroll loop

				}

			}
		}
	}
	
}

void GUI::UI_add(NotIMDB_Database &db)
{
	std::cout << GUI::divider << std::endl;

	std::string newMovieTitle;
	std::cout << "\nEnter the title of the movie you want to add: ";
	std::getline(std::cin, newMovieTitle);
	std::string runtime;
	std::string id = "";
	int newMovieYear;
	double newMovieRating;
	bool b = false;
	do
	{
		try
		{
			std::cout << "\nEnter the release year: ";
			std::cin >> newMovieYear;
			if (newMovieYear > 2020)
				throw CustomException("Error: invalid release year");
			b = true;
		}
		catch(const CustomException& e)
		{
			std::cout << e.getMessage() << std::endl;
		}
	} while (!b);

	b = false;
	do
	{
		try
		{
			std::cout << "\nEnter the movie's rating (0.0 - 10.0): ";
			std::cin >> newMovieRating;
			if (newMovieRating > 10.0 || newMovieRating < 0.0)
				throw CustomException("Error: invalid movie rating");
			b = true;
		}
		catch (const CustomException& e)
		{
			std::cout << e.getMessage() << std::endl;
		}
	} while (!b);

	b = false;
	do
	{
		try
		{
			std::cout << "\nEnter an id for the movie. For example tt03231: ";
			std::cin >> id;
			b = true;
		}
		catch (const CustomException& e)
		{
			std::cout << e.getMessage() << std::endl;
		}
	} while (!b);

	b = false;
	do
	{
		try
		{
			std::cout << "\nEnter a runtimes(minutes) for the movie. For example 135: ";
			std::cin >> runtime;
			b = true;
		}
		catch (const CustomException& e)
		{
			std::cout << e.getMessage() << std::endl;
		}
	} while (!b);

	std::cin.ignore();
	std::string newMovieGenre;
	std::cout << "\nEnter the movie's genre: ";
	std::getline(std::cin, newMovieGenre);

	Movie newMovie;
	newMovie.setRuntime(runtime);
	newMovie.setID(id);
	newMovie.setYearReleased(std::to_string(newMovieYear));
	newMovie.setRating(std::to_string(newMovieRating));
	newMovie.setGenre(newMovieGenre);
	newMovie.setTitle(newMovieTitle);
	
	std::cout << "This is the movie you are adding:" << std::endl;
	std::cout << newMovie << std::endl;

	if (db.createMovie(newMovie))
	{
		std::cout << "Added successfully!" << std::endl;
	}
}

void GUI::UI_remove(NotIMDB_Database &db)
{
	bool exactMatchFound = false;
	bool b = false;
	do
	{
		try
		{
			std::string selectedMovieTitle;
			std::cout << "\nEnter the title of the movie to remove: ";
			getline(std::cin, selectedMovieTitle);

			if (!(db.foundMovie(selectedMovieTitle)))
			{
				throw CustomException("Error: movie not found in database");
			}
			else
			{
				std::cout << GUI::divider << std::endl;
				db.readMovies(selectedMovieTitle, exactMatchFound);
				int confirm = menu_prompt("Are you sure you want to remove this movie?", menu_yes_no, 2);
				if (confirm == 1)
				{
					db.deleteMovie(selectedMovieTitle);
					if (!(db.foundMovie(selectedMovieTitle)))
					{
						std::cout << "Deleted successfully!" << std::endl;
					}
				}
			}
			b = true;
		}
		catch (const CustomException& e)
		{
			std::cout << e.getMessage() << std::endl;
			int tryAgain = menu_prompt("Would you like to try again?", menu_yes_no, 2);
			if (tryAgain != 1)
				return;
		}
	} while (!b);
}

// TODO
void GUI::promptLoadFile(NotIMDB_Database &db)
{
	int try_again;
	bool done_file_load = false;
	//std::string outfile_prompt = "Enter the file path for an output file\nExample: C:\\data\\output.txt\nHit enter for a default output.txt file to be created in this program's directory\n";
	std::string infile_prompt = "Enter the file path for an input file .tsv file\nExample: C:\\data\\input.tsv\nHit enter to use the default .tsv file in this program's directory\n";
	std::string user_in = "";
	std::string defaultPath = "title_basics_cleaned_final_trimmed_500.tsv";
	ifstream infile;
	while (!done_file_load)
	{
		std::cout << infile_prompt << std::endl;
		std::getline(std::cin, user_in);
		user_in = StringUtil::strip(user_in);
		// default case
		if (user_in.length() == 0)
		{
			db.loadFromFile(defaultPath);
			break;
		}
		else {
			// user input case
			infile.open(user_in);
			if (!infile.good())
			{
				std::cout << "I couldn't open from the provided file path." << std::endl;
				try_again = GUI::menu_prompt("Would you like to try again or exit the program?", menu_try_again_or_exit_prog, 2);
				if (try_again == 2)
					break;
			}
			else
			{
				db.loadFromFile(user_in);
				break;
			}
		}
	}
	std::cout << "\n";
	infile.close();
}

void GUI::UI_edit(NotIMDB_Database &db)
{
	bool exactMatchFound = false;
	bool b = false;
	bool movieSelectedFromList = false;
	// input required to be atleast 1 character long
	bool goodInput = false;
	std::string selectedMovieTitle = "";
	do
	{
		while (!goodInput)
		{
			if (!movieSelectedFromList) {
				selectedMovieTitle = "";
				std::cout << "Enter the title and year of a movie you want to edit or a keyword of the movie: ";
				std::getline(std::cin, selectedMovieTitle);
				//std::cout << selectedMovieTitle << std::endl;	// DEBUG
				selectedMovieTitle = StringUtil::strip(selectedMovieTitle);
				//std::cout << selectedMovieTitle << std::endl;	// DEBUG
				if (selectedMovieTitle.length() == 0)
				{
					std::cout << "I can't process your input" << std::endl;
					int tryAgain = menu_prompt("Try again?", menu_yes_no, 2);
					goodInput = false;
					if (tryAgain != 1)
					{
						return;
					}
				}
				else
				{
					goodInput = true;
					break;
				}
			}
			else
				break;
		}
		try
		{
			// clean query 
			selectedMovieTitle = db.processSearchEntry(selectedMovieTitle);
			if (!(db.foundMovie(selectedMovieTitle)))
			{
				movieSelectedFromList = false;
				throw CustomException("Error: movie not found in database");
			}
			std::cout << std::endl << GUI::divider << std::endl;
			db.readMovies(selectedMovieTitle, exactMatchFound);
			std::cout << std::endl << GUI::divider << std::endl;
			int attribute = menu_prompt("What attribute are you changing?", menu_attributes, 6);
			switch (attribute)
			{
			case 1:
			{
				std::string newMovieTitle;
				std::cout << "Enter the new title of the movie: ";
				std::getline(std::cin, newMovieTitle);
				std::cout << std::endl;
				if (db.updateMovieName(selectedMovieTitle, newMovieTitle))
					std::cout << "Edited successfully!" << std::endl;
				else
					throw CustomException("Error while updating title: " + selectedMovieTitle);
				break;
			}
			case 2:
			{
				// TODO: year validation
				int newReleaseYear;
				std::cout << "Enter the new release year of the movie: ";
				cin >> newReleaseYear;
				std::cout << std::endl;
				if (db.updateMovieYear(selectedMovieTitle, std::to_string(newReleaseYear)))
					std::cout << "Edited successfully!" << std::endl;
				else
					throw CustomException("Error while updating year: " + selectedMovieTitle);
				break;
			}
			case 3:
			{
				int newID;
				std::cout << "Enter the new ID of the movie: ";
				cin >> newID;
				std::cout << std::endl;
				if (db.updateMovieID(selectedMovieTitle, std::to_string(newID)))
					std::cout << "Edited successfully!" << std::endl;
				else
					throw CustomException("Error while updating ID: " + selectedMovieTitle);
				break;
			}
			case 4:
			{
				std::string newRuntime;
				std::cout << "Enter the new runtime of the movie: ";
				std::getline(std::cin, newRuntime);
				std::cout << std::endl;
				if (db.updateMovieRuntime(selectedMovieTitle, newRuntime))
					std::cout << "Edited successfully!" << std::endl;
				else
					throw CustomException("Error while updating runtime: " + selectedMovieTitle);
				break;
			}
			case 5:
			{
				bool b = false;
				do
				{
					int select = GUI::menu_prompt("How would you like to edit genres of this movie?", GUI::menu_edit_genre, 2);
					if (select == 1)
					{
						std::string newGenre;
						std::cout << "Enter the new genre of the movie: ";
						std::getline(std::cin, newGenre);
						std::cout << std::endl;
						if (db.updateMovieGenre(selectedMovieTitle, newGenre, 0))
							std::cout << "Edited successfully!" << std::endl;
						else
							throw CustomException("Error while updating genre: " + selectedMovieTitle);
						b = true;
					}
					else if (select == 2)
					{
						std::string newGenre;
						std::cout << "Enter the new genre of the movie: ";
						std::getline(std::cin, newGenre);
						std::cout << std::endl;
						if (db.updateMovieGenre(selectedMovieTitle, newGenre, 1))
							std::cout << "Edited successfully!" << std::endl;
						else
							throw CustomException("Error while updating genre: " + selectedMovieTitle);
						b = true;
					}
				} while (!b);
				break;
			}
			case 6:
			{
				double newMovieRating;
				std::cout << "Enter the new rating (0.0 - 10.0): ";
				cin >> newMovieRating;
				std::cout << std::endl;
				if (db.updateMovieRating(selectedMovieTitle, std::to_string(newMovieRating)))
					std::cout << "Edited successfully!" << std::endl;
				else
					throw CustomException("Error while updating score: " + selectedMovieTitle);
				break;
			}
			}

			b = true;
		}
		catch (const CustomException& e) {
			int tryAgain = menu_prompt("Try again?", menu_yes_no, 2);
			if (tryAgain != 1)
			{
				selectedMovieTitle = UI_pick_from_potential_matches_to_edit(db, selectedMovieTitle, b);
				if (selectedMovieTitle.length() == 0 && b == true)
					return;
				// no potential movies found
				else if (selectedMovieTitle.length() == 0 && b != true)
				{
					std::cout << e.getMessage() << std::endl;
					int tryAgain = menu_prompt("Try again?", menu_yes_no, 2);
					goodInput = false;
					if (tryAgain != 1)
					{
						return;
					}
				}
				else {
					// movie was chosen from the list therefore don't reprompt
					movieSelectedFromList = true;
				}
			}
		}

	} while (!b);
}

void GUI::UI_run_application(NotIMDB_Database & db)
{
	std::cout << "Welcome to the Movie Database\n\n";
	promptLoadFile(db);
	bool b = false;
	do
	{
		int choice = menu_prompt("What would you like to do?", GUI::menu_operations, 6);
		switch (choice)
		{
		case 1:
			UI_search(db);
			break;
		case 2:
			UI_add(db);
			break;
		case 3:
			UI_remove(db);
			break;
		case 4:
			UI_edit(db);
			break;
		case 5:
		{
			if (db.canUndoDelete())
			{
				std::cout << "This was the most recently deleted movie: " << std::endl;
				db.showMostRecentDelete();
				std::cout << "Would you like to undo this deletion?" << std::endl;
				
				int choice = menu_prompt("Would you like to undo this deletion?", menu_yes_no, 2);
				if (choice == 1)
				{
					db.undoMostRecentDelete();
				}
			}
			else {
				std::cout << "You have to delete something from the database before you can undo a deletion" << std::endl;
			}
		}
		break;
		case 6:
			std::cout << "Exiting the program..." << std::endl;
			b = true;
			break;
		}
	} while (!b);
	std::cout << "Saving to output.tsv" << std::endl;
	db.saveToFile();
}

/* Allow user to select from a list of approximated matches
@param db is the database of movies
@param userIn is the users input to find approx matched movies 
@param exit signify if the user wants to leave the edit section and go back to main menu 
@return a raw string of a selected == "movie_title + <whitespace> + movie_year" */
std::string GUI::UI_pick_from_potential_matches_to_edit(NotIMDB_Database & db, const std::string& userIn, bool& exit)
{
	if (StringUtil::strip(userIn).length() < 1)
	{
		return "";
	}
	bool exactMatch = false;
	List<Movie>* keywordMovies = db.readMovies(userIn, exactMatch);
	bool doneSelecting = false;
	exit = false;
	const int START = 0;
	int MSIZE = 0;
	int END = 0;
	try {
		MSIZE = (*keywordMovies).getLength();
		END = MSIZE - 1;
	}
	catch (...)
	{
		return "";
	}
	// return nothing 
	/*if (MSIZE == 0)
		return "";*/
	int choice;
	bool doneScrolling = false;
	int currentIndex = 0;
	// display 3 items at a time
	while (!doneSelecting)
	{
		int counter = 0;
		int optionNum = 1;
		int currentPos = 0;
		std::cout << divider << std::endl;
		std::cout << "I found a total of " << MSIZE << " movie(s) related to your search\n";
		// exit case 
		if (MSIZE > 3)
		{
			std::cout << "Here are the first 3 entries:\n" <<
				keywordMovies->getEntry(0) << divider << "\n" <<
				keywordMovies->getEntry(1) << divider << "\n" <<
				keywordMovies->getEntry(2) << divider << "\n";
			currentPos = 3;
		}
		else
		{
			for (int i = 0; i < MSIZE; i++)
			{
				std::cout << keywordMovies->getEntry(i) << std::endl;
				std::cout << divider << std::endl;
				currentPos++;
			}
		}
		choice = menu_prompt("What would you like to do?", menu_search_browse, 3);
		// resets from the end of case 1 to allow use mobility
		doneScrolling = false;

		switch(choice) {
		// browse list of movies found
		case 1:
			
			while (!doneScrolling) {
				// scrolls by 1 movie each time
				choice = menu_prompt("What would you like to do?", menu_search_scroll, 5);
				std::cout << divider << endl;
				switch (choice)
				{
				// view next set 
				case 1: 
				{
					currentIndex += 3;
					if (currentIndex == END || currentIndex > END) {
						std::cout << "*************************************" << std::endl;
						std::cout << "*\tWe can't go further forward\t*\n";
						std::cout << "*************************************" << std::endl;
					}
					//  reposition accordingly to redisplay current state
					if (currentIndex > MSIZE)
						currentIndex = MSIZE - 3;
					if (currentIndex < 0)
						currentIndex = 0;
					// attempt to show the next 3- 4 movies
					while (counter < 3 && currentIndex < MSIZE)
					{
						std::cout << keywordMovies->getEntry(currentIndex) << divider << "\n";
						counter++;
						currentIndex++;
					}
					counter = 0;
					break;
				}
				// view prev. set 
				case 2:
				{
					currentIndex -= 3;
					if (currentIndex == START || currentIndex) {
						std::cout << "*************************************" << std::endl;
						std::cout << "*\tWe can't go further back\t*\n";
						std::cout << "*************************************" << std::endl;

					}
					if (currentIndex < 0)
						currentIndex = 0;
					// attempt to show the next 3- 4 movies
					while (counter < 3 && currentIndex < MSIZE)
					{
						std::cout << keywordMovies->getEntry(currentIndex) << divider << "\n";
						counter++;
						currentIndex++;
					}
					counter = 0;
					break;
				}
				// go to the start of the list showing first few results
				case 3:
				{
					currentIndex = 0;
					while (counter < 3 && currentIndex < MSIZE)
					{
						std::cout << keywordMovies->getEntry(currentIndex) << divider << "\n";
						counter++;
						currentIndex++;
					}
					counter = 0;
					break;
				}
				// go to the end of the list showing the last few results ~3/4
				case 4:
				{
					currentIndex = END - 3;
					if (currentIndex > MSIZE)
						currentIndex = MSIZE - 3;
					// handle small list case
					if (currentIndex < 0)
						currentIndex = 0;
					// attempt to show the next 3- 4 movies
					while (counter < 3 && currentIndex < MSIZE)
					{
						std::cout << keywordMovies->getEntry(currentIndex) << divider << "\n";
						counter++;
						currentIndex++;
					}
					counter = 0;
					break;
				}
				// leave to search section
				case 5:
					doneScrolling = true;
					break;
				}
			} // end scroll loop
			break;
		// return to the main search menu
		case 2:
			exit = false;
			return "";
		// return the main menu
		case 3:
			exit = true;
			return "";
		}
	}
}
