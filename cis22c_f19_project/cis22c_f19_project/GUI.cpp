#include "GUI.h"

bool GUI::isValidName(string name) {
int size = name.size();
for (int i = 0; i < size; i++)
{
	if (!isalpha(name[i]))
	{
		if (isdigit(name[i]))
		{
			return false;
		}
	}

}
return true;
}
bool GUI::isValidMonth(string month) {
int size = month.size();
if (size != 2)
	return false;
if (stoi(month) > 12 || stoi(month) < 1)
	return false;
for (int i = 0; i < size; i++)
{
	if (isalpha(month[i]))
	{
		return false;
	}

}
return true;
}
bool GUI::isValidDay(string day) {
int size = day.size();
if (size != 2)
	return false;
if (stoi(day) > 31 || stoi(day) < 1)
	return false;
for (int i = 0; i < size; i++)
{
	if (isalpha(day[i]))
	{
		return false;
	}

}
return true;
}
bool GUI::isValidYear(string year) {
int size = year.size();
if (size > 4)
	return false;
else if (size != 4)
	return false;
for (int i = 0; i < size; i++)
{
	if (isalpha(year[i]))
	{
		return false;
	}

}
return true;
}
void GUI::promptLoadFile(TableDatabase& db)
{
	int try_again;
	bool done_file_load = false;
	string outfile_prompt = "Enter the file path for an output file\nExample: C:\\data\\output.txt\nHit enter for a default output.txt file to be created in this program's directory\n";
	string infile_prompt = "Enter the file path for an input file\nExample: C:\\data\\input.txt\nHit enter to use the default input.txt file in this program's directory\n";
	string user_in = "";
	string defaultPath = "InputData.txt";
	ifstream infile;
	int choice;

	// prompt file path loop
	while (!done_file_load)
	{
		std::cout << infile_prompt;
		getline(std::cin, user_in);
		std::cout << "You entered: " << user_in << std::endl;
		if (user_in.size() == 0)
		{
			cout << "Building from " << defaultPath << endl;
			cout << divider << endl;
			db.buildDatabase(defaultPath);
			break;
		}
		// user specified file case
		else if (user_in.size() > 1)
		{
			//attempt to open
			infile.open(user_in, ios::in);
			if (infile.fail())
			{
				std::cout << "I couldn't open the file from the path entered\n";
				try_again = menu_prompt("Would you like to try again?", menu_continue_program, 2);
				if (try_again == 2)
					return;
			}
			else {
				db.buildDatabase(user_in);
				break;
			}
			// prompt for a try again
			if (try_again == 1) continue;
		}
	} // end file prompt loop
	db.displayStats();
	//db.displayDatabase();	// DEBUG
	cout << divider << endl;
}

void GUI::promptRead(const TableDatabase& db)
{
	bool done = false;
	std::string input;
	int choiceExit;
	while (!done)
	{
		std::cout << "Please enter any date in the format: YYYY-MM-DD" << std::endl;
		getline(cin, input);
		input = StringUtil::strip(input);
		
		// valid input case
		if (!StringUtil::containsAlpha(input))
		{
			if (db.found(input))
			{
				db.displayPerson(input);
			}
			else
				std::cout << "Invalid data" << std::endl;

			choiceExit = menu_prompt("Would you like to continue searching?", menu_yes_no, 2);
			if (choiceExit == 2)
			{
				break;
				std::cout << "Exitting...\n";
			}
		}
		// invalid input case
		else {

			std::cout << "Invalid data" << std::endl;

			choiceExit = menu_prompt("Would you like to continue searching?", menu_yes_no, 2);
			if (choiceExit == 2)
			{
				break;
				std::cout << "Exitting...\n";
			}
		}

		
	}
}
