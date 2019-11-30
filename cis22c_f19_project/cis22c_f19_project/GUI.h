#ifndef _GUI_H
#define _GUI_H

#include "binary_node.h"
#include "binary_tree.h"
#include "binary_search_tree.h"

#include <iostream>
#include <fstream>
#include "person.h"
#include "menu.h"
#include "menu_dialog.h"
#include "TableDatabase.h"
#include <string>

#include <time.h>
#include <chrono>

namespace GUI
{
	bool isValidName(std::string name);
	bool isValidDay(std::string day);
	bool isValidMonth(std::string month);
	bool isValidYear(std::string month);
	/* Prompt user for a filepath with the option to use the
	included default file (InputData.txt). The prompt loops until
	the user either quits or enters a valid file path. 
	@pre TableDatabase db is empty
	@post TableDatabase db is populated with data from the specified file path
	@param db is a reference to an empty TableDatabase to be loaded with the file data */
	void promptLoadFile(TableDatabase& db);
	void promptCreate(TableDatabase& db);
	void promptDelete(TableDatabase& db);
	void promptUpdate(TableDatabase& db);
	/* Prompt the user to enter a date(key) to display a Person
	stored in the database's contained hashtable.
	If the key is found, the corresponding value is displayed
	else a message of "Invalid Data" is outputted. The prompt loops
	until the user decides to exit.
	@param db is a populated TableDatabase	*/
	void promptRead(const TableDatabase& db);
}

#endif // !_GUI_H
