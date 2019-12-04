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
	std::string in;
	int choice = GUI::menu_prompt("How do you want to search movies by?", GUI::menu_search, 6);
	switch (choice)
	{
	case 1:
	{
		std::cout << "Please insert the title of the movie you want to search: " << std::endl;
		std::getline(std::cin, in);
		UI_search_by_title(in, db);
		break;
	}
	case 2:
	{
		std::cout << "Please insert the release year of the movie you want to search: " << std::endl;
		std::getline(std::cin, in);
		UI_search_by_year(std::stoi(in), db);
		break;
	}
	case 3:
	{
		bool b = false;
		do
		{
			try
			{
				std::cout << "Please insert the ratings of the movie you want to search\n";
				std::cout << "(Should between 0.0 ~ 10.0): " << std::endl;
				std::getline(std::cin, in);
				if (std::stod(in) > 10.0 || std::stod(in) < 0.0)
					throw CustomException("Error: invalid movie rating");;
				UI_search_by_ratings(std::stod(in), db);
				b = true;
			}
			catch(const CustomException& e)
			{
				std::cout << e.getMessage() << std::endl;
			}
		} while (!b);
		break;
	}
	case 4:
	{
		bool b = false;
		do
		{
			try
			{
				std::cout << "Please insert the genre of the movie you want to search: " << std::endl;
				std::getline(std::cin, in);
				// TODO: genre validation
				UI_search_by_genre(in, db);
				b = true;
			}
			catch(const CustomException& e)
			{
				std::cout << e.getMessage() << std::endl;
			}
		} while (!b);
		break;
	}
	default:
		break;
	}
}

void GUI::UI_add(NotIMDB_Database &db)
{
	std::cout << GUI::divider << std::endl;

	std::string newMovieTitle;
	std::cout << "\nEnter the title of the movie you want to add: ";
	std::getline(std::cin, newMovieTitle);

	int newMovieYear;
	double newMovieRating;
	bool b = false;
	do
	{
		try
		{
			std::cout << "\nEnter the release year: ";
			std::cin >> newMovieYear;
			if (newMovieYear > 2020 || newMovieYear < 1820)
				throw CustomException("Error: invalid release year");

			std::cout << "\nEnter the movie's rating (0.0 - 10.0): ";
			std::cin >> newMovieRating;
			if (newMovieYear > 10.0 || newMovieYear < 0.0)
				throw CustomException("Error: invalid movie rating");

			b = true;
		}
		catch(const CustomException& e)
		{
			std::cout << e.getMessage() << std::endl;
		}
	} while (!b);

	std::string newMovieGenre;
	std::cout << "\nEnter the movie's genre: ";
	std::getline(std::cin, newMovieGenre);

	Movie newMovie;
	newMovie.setYearReleased(std::to_string(newMovieYear));
	newMovie.setRating(std::to_string(newMovieRating));
	newMovie.setGenre(newMovieGenre);
	newMovie.setTitle(newMovieTitle);
	
	if (db.createMovie(newMovie))
	{
		std::cout << "Added successfully!" << std::endl;
	}
}

void GUI::UI_remove(NotIMDB_Database &db)
{
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
				db.readMovie(selectedMovieTitle);
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
			int tryAgain = menu_prompt("Would you like to insert again?", menu_yes_no, 2);
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
	std::string outfile_prompt = "Enter the file path for an output file\nExample: C:\\data\\output.txt\nHit enter for a default output.txt file to be created in this program's directory\n";
	std::string infile_prompt = "Enter the file path for an input file\nExample: C:\\data\\input.txt\nHit enter to use the default input.txt file in this program's directory\n";
	std::string user_in = "";
	std::string defaultPath = "InputData.txt";
	ifstream infile;
}

void GUI::UI_edit(NotIMDB_Database &db)
{
	bool b = false;
	do
	{
		try
		{
			std::string selectedMovieTitle;
			std::cout << "Enter the title of the movie you want to edit: ";
			std::getline(std::cin, selectedMovieTitle);
			if (!(db.foundMovie(selectedMovieTitle)))
			{
				throw CustomException("Error: movie not found in database");
			}
			std::cout << std::endl << GUI::divider << std::endl;
			db.readMovie(selectedMovieTitle);
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
				std::string newGenre;
				std::cout << "Enter the new genre of the movie: ";
				std::getline(std::cin, newGenre);
				std::cout << std::endl;
				if (db.updateMovieGenre(selectedMovieTitle, newGenre, 1))
					std::cout << "Edited successfully!" << std::endl;
				else
					throw CustomException("Error while updating genre: " + selectedMovieTitle);
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
			default:
				break;
			}

			b = true;
		}
		catch (const CustomException& e)
		{
			std::cout << e.getMessage() << std::endl;
			int tryAgain = menu_prompt("Try again?", menu_yes_no, 2);
			if (tryAgain != 1)
			{
				return;
			}
		}
	} while (!b);
}

void GUI::UI_run_application(NotIMDB_Database & db)
{
	std::cout << "Welcome to the Movie Database\n\n";
	bool b = false;
	do
	{
		int choice = menu_prompt("What would you like to do?", GUI::menu_operations, 5);
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
		default:
			std::cout << "Exiting the program..." << std::endl;
			b = true;
			break;
		}
	} while (!b);
	

	//bool end = true;
	//while (end) {
	//	int choice = menu_prompt("What would you like to do?", GUI::menu_operations, 5);
	//	switch (choice) {
	//	case 1: {
	//		UI_search(/*const database& database*/);
	//		break;
	//	}
	//	case 2: {
	//		UI_add(/*const database& database*/);
	//		break;
	//	}
	//	case 3: {
	//		UI_remove(/*const database& database*/);
	//		break;
	//	}
	//	case 4: {
	//		UI_edit();
	//		break;
	//	}
	//	case 5: {
	//		end = false;
	//		break;
	//	}
	//	}
	//}
}

void GUI::UI_search_by_title(std::string in_title, const NotIMDB_Database& db)
{
	//TODO: Search by title
}

void GUI::UI_search_by_year(int in_year, const NotIMDB_Database& db)
{
	//TODO: Search by year
}

void GUI::UI_search_by_ratings(double in_ratings, const NotIMDB_Database& db)
{
	//TODO: Search by ratings
}

void GUI::UI_search_by_genre(std::string in_genre, const NotIMDB_Database& db)
{
	//TODO: Search by genre
}
