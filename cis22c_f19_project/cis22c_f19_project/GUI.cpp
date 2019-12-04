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
		UI_search_by_title(in /*const database& database*/);
		break;
	}
	case 2:
	{
		std::cout << "Please insert the release year of the movie you want to search: " << std::endl;
		std::getline(std::cin, in);
		UI_search_by_year(std::stoi(in) /*const database& database*/);
		break;
	}
	case 3:
	{
		bool !b = false;
		do
		{
			try
			{
				std::cout << "Please insert the ratings of the movie you want to search\n";
				std::cout << "(Should between 0.0 ~ 10.0): " << std::endl;
				std::getline(std::cin, in);
				if (std::stod(in) > 10.0 || std::stod(in) < 0.0)
					throw 0;
				UI_search_by_ratings(std::stod(in) /*const database& database*/);
				b = true;
			}
			catch(const CustomException& e)
			{
				std::cerr << e.what() << '\n';
			}
		} while (!b);
		break;
	}
	case 4:
	{
		while (1)
		{
			try
			{
				std::cout << "Please insert the genre of the movie you want to search: " << std::endl;
				std::getline(std::cin, in);
				//TODO:
				//if (invalid genre)
				//	throw 0;
				UI_search_by_genre(in /*const database& database*/);
				break;
			}
			catch (...)
			{
				std::cout << "The genre you insert does not exist!" << std::endl;
			}
		}
		break;
	}
	case 5:
	{
		try
		{
			std::cout << "Please insert the cast of the movie you want to search: " << std::endl;
			std::getline(std::cin, in);
			//TODO:
			//if (invalid cast)
			//	throw 0;
			UI_search_by_cast(in);
			///*const database& database*/);
			break;
		}
		catch (...)
		{
			std::cout << "The cast you insert does not exist!" << std::endl;
		}
		break;
	}
	case 6:
	{
		return;
	}
	}
}

void GUI::UI_add(NotIMDB_Database &db)
{
	std::string tmp;
	std::string in_title;
	int in_year;
	double in_rate;
	List<std::string> in_g;
	List<std::string> in_c;

	//Insert title
	std::cout << "Please insert the title of the movie you want to add: " << std::endl;
	std::getline(std::cin, in_title);
	std::cout << std::endl;

	//Insert release year
	while (1)
	{
		try
		{
			std::cout << "Please insert the release year of the the movie you want to add(Should be less than 2019): " << std::endl;
			std::getline(std::cin, tmp);
			if (std::stoi(tmp) > 2019)
				throw 0;
			break;
		}
		catch (...)
		{
			std::cout << "Year date should less than 2019!" << std::endl;
		}
	}
	in_year = std::stoi(tmp);
	std::cout << std::endl;

	//Insert ratings
	while (1)
	{
		try
		{
			std::cout << "Please insert the ratings of the the movie you want to add(Should between 0.0 ~ 10.0): " << std::endl;
			std::getline(std::cin, tmp);
			if (std::stod(tmp) < 0.0 || std::stod(tmp) > 10.0)
				throw 0;
			break;
		}
		catch (...)
		{
			std::cout << "Ratings should between 0.0 ~ 10.0" << std::endl;
		}
	}
	in_rate = std::stod(tmp);
	std::cout << std::endl;

	//Insert genres
	while (1)
	{
		try
		{
			std::cout << "Please insert the genre of the the movie you want to add(Press enter to stop inserting): " << std::endl;
			std::getline(std::cin, tmp);
			if (tmp == "")
				break;
			//TODO:
			//if (invalid genre)
			//	throw 0;
			in_g.append(tmp);
		}
		catch (...)
		{
			std::cout << "The genre you insert does not exist!" << std::endl;
		}
	}
	std::cout << std::endl;

	//Insert cast
	while (1)
	{
		std::cout << "Please insert the cast of the the movie you want to add(Press enter to stop inserting): " << std::endl;
		std::getline(std::cin, tmp);
		if (tmp == "")
			break;
		in_c.append(tmp);
	}
	std::cout << std::endl;

	//TODO: Create movie obj

	std::cout << "This is the movie you want to add: " << std::endl;
	//TODO: Display obj

	std::cout << "Added successfully!" << std::endl;
}

void GUI::UI_remove(NotIMDB_Database &db)
{
	while (1)
	{
		std::string input;
		bool found = false;

		std::cout << "Please insert the title of the movie you want to remove: " << std::endl;
		getline(std::cin, input);

		//TODO:
		//Search the obj
		//If found, set boolean found = true

		if (!found)
		{
			std::cout << "The movie you want to remove does not exist!" << std::endl;
			int tryAgain = menu_prompt("Would you like to insert again?", menu_yes_no, 2);
			if (tryAgain == 1)
				continue;
			else
				return;
		}
		std::cout << "This is the movie you want to remove:" << std::endl;
		// TODO: Display the obj

		int confirm = menu_prompt("Are you sure you want to remove this movie?", menu_yes_no, 2);
		if (confirm == 1)
		{
			//TODO: Remove obj from database

			std::cout << "Deleted successfully!" << std::endl;
			int tryAgain = menu_prompt("Would you like to insert again?", menu_continue_remove, 2);
			if (tryAgain == 1)
				continue;
			else
				return;
		}
		else
		{
			int tryAgain = menu_prompt("Would you like to insert again?", menu_yes_no, 2);
			if (tryAgain == 1)
				continue;
			else
				return;
		}
	}
}

void GUI::promptLoadFile(NotIMDB_Database &db)
{
	int try_again;
	bool done_file_load = false;
	std::string outfile_prompt = "Enter the file path for an output file\nExample: C:\\data\\output.txt\nHit enter for a default output.txt file to be created in this program's directory\n";
	std::string infile_prompt = "Enter the file path for an input file\nExample: C:\\data\\input.txt\nHit enter to use the default input.txt file in this program's directory\n";
	std::string user_in = "";
	std::string defaultPath = "InputData.txt";
	ifstream infile;

	// prompt file path loop
	while (!done_file_load)
	{
		std::string input;
		bool found = false;

		std::cout << "Please insert the title of the movie you want to remove: " << std::endl;
		std::getline(std::cin, input);

		//TODO:
		//Search the obj
		//If found, set boolean found = true

		if (!found)
		{
			std::cout << "The movie you want to remove does not exist!" << std::endl;
			int tryAgain = menu_prompt("Would you like to insert again?", menu_yes_no, 2);
			if (tryAgain == 1)
				continue;
			else
				return;
		}
		std::cout << "This is the movie you want to remove:" << std::endl;
		// TODO: Display the obj

		int confirm = menu_prompt("Are you sure you want to remove this movie?", menu_yes_no, 2);
		if (confirm == 1)
		{
			//TODO: Remove obj from database

			std::cout << "Deleted successfully!" << std::endl;
			int tryAgain = menu_prompt("Would you like to insert again?", menu_continue_remove, 2);
			if (tryAgain == 1)
				continue;
			else
				return;
		}
		else
		{
			int tryAgain = menu_prompt("Would you like to insert again?", menu_yes_no, 2);
			if (tryAgain == 1)
				continue;
			else
				return;
		}
	}
}

void GUI::UI_edit(NotIMDB_Database &db)
{
	while (1)
	{
		std::string input;
		bool found = false;

		std::cout << "Please insert the title of the movie you want to edit: " << std::endl;
		std::getline(std::cin, input);

		//TODO:
		//Search the obj
		//If found, set boolean found = true

		if (!found)
		{
			std::cout << "The movie you want to remove does not exist!" << std::endl;
			int tryAgain = GUI::menu_prompt("Would you like to insert again?", menu_yes_no, 2);
			if (tryAgain == 1)
				continue;
			else
				return;
		}
		std::cout << "This is the movie you want to edit:" << std::endl;
		// TODO: Display the obj

		std::string tmp;
		std::string in_title;
		int in_year;
		double in_rate;
		List<std::string> in_g;
		List<std::string> in_c;

		//Insert title
		std::cout << "Please insert the title you want to change to: " << std::endl;
		std::getline(std::cin, in_title);
		std::cout << std::endl;

		//Insert release year
		while (1)
		{
			try
			{
				std::cout << "Please insert the release year you want to change to(Should be less than 2019): " << std::endl;
				std::getline(std::cin, tmp);
				if (std::stoi(tmp) > 2019)
					throw 0;
				break;
			}
			catch (...)
			{
				std::cout << "Year date should less than 2019!" << std::endl;
			}
		}
		in_year = std::stoi(tmp);
		std::cout << std::endl;

		//Insert ratings
		while (1)
		{
			try
			{
				std::cout << "Please insert the ratings you want to change to(Should between 0.0 ~ 10.0): " << std::endl;
				std::getline(std::cin, tmp);
				if (std::stod(tmp) < 0.0 || std::stod(tmp) > 10.0)
					throw 0;
				break;
			}
			catch (...)
			{
				std::cout << "Ratings should between 0.0 ~ 10.0" << std::endl;
			}
		}
		in_rate = std::stod(tmp);
		std::cout << std::endl;

		//Insert genres
		while (1)
		{
			try
			{
				std::cout << "Please insert the genre of the the movie you want to change to(Press enter to stop inserting): " << std::endl;
				std::getline(std::cin, tmp);
				if (tmp == "")
					break;
				//TODO:
				//if (invalid genre)
				//	throw 0;
				in_g.append(tmp);
			}
			catch (...)
			{
				std::cout << "The genre you insert does not exist!" << std::endl;
			}
		}
		std::cout << std::endl;

		//Insert cast
		while (1)
		{
			std::cout << "Please insert the cast you want to change to(Press enter to stop inserting): " << std::endl;
			std::getline(std::cin, tmp);
			if (tmp == "")
				break;
			in_c.append(tmp);
		}
		std::cout << std::endl;

		//TODO: Edit movie obj

		std::cout << "This is the movie you want change to: " << std::endl;
		//TODO: Display obj

		int confirm = GUI::menu_prompt("Are you sure you want to edit this movie?", menu_yes_no, 2);
		if (confirm == 1)
		{
			//TODO: Remove obj from database

			std::cout << "Edited successfully!" << std::endl;
			int tryAgain = GUI::menu_prompt("Would you like to edit again?", menu_continue_remove, 2);
			if (tryAgain == 1)
				continue;
			else
				return;
		}
		else
		{
			int tryAgain = GUI::menu_prompt("Would you like to edit again?", menu_yes_no, 2);
			if (tryAgain == 1)
				continue;
			else
				return;
		}
	}
}
//
//void GUI::UI_run_application()
//{
//	std::cout << "Welcome to NotNetfix!" << std::endl;
//
//	bool end = true;
//	while (end) {
//		int choice = menu_prompt("What would you like to do?", GUI::menu_operations, 5);
//		switch (choice) {
//		case 1: {
//			UI_search(/*const database& database*/);
//			break;
//		}
//		case 2: {
//			UI_add(/*const database& database*/);
//			break;
//		}
//		case 3: {
//			UI_remove(/*const database& database*/);
//			break;
//		}
//		case 4: {
//			UI_edit();
//			break;
//		}
//		case 5: {
//			end = false;
//			break;
//		}
//		}
//	}
//	return 0;
//}

void GUI::UI_search_by_title(std::string in_title /*,const database& database*/)
{
	//TODO: Search by title
}

void GUI::UI_search_by_year(int in_year /*,const database& database*/)
{
	//TODO: Search by year
}

void GUI::UI_search_by_ratings(double in_ratings /*,const database& database*/)
{
	//TODO: Search by ratings
}

void GUI::UI_search_by_genre(std::string in_genre /*,const database& database*/)
{
	//TODO: Search by genre
}

void GUI::UI_search_by_cast(std::string in_genre /*,const database& database*/)
{
	//TODO: Search by cast
}
