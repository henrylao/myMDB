#include <string>

#ifndef MENU_DIALOG_H
#define MENU_DIALOG_H
namespace GUI {

	const std::string menu_expression[] = {
		"Postfix",
		"Prefix"
	};

	const std::string menu_try_again[] = {
		"Try again",
		"Exit to main menu"
	};

	const std::string menu_continue_operation[] = {
		"Yes, Continue the operation",
		"No, Exit"
	};

	const std::string menu_yes_no[] = {
		"Yes",
		"No"
	};

	const std::string menu_continue_program[] = {
		"Yes",
		"No, exit the program"
	};

	const std::string divider = "--------------------------------------";

	const std::string menu_bst_operations[] = {
		"Add a new person",
		"Remove a person",
		"Edit a person",
		"Search for a person",
		"Display the database",
		"Exit program"
	};

	const std::string menu_remove[] = {
		"Remove a person by full name",
		"Remove a person by birthdate",
		"Return to main menu"
	};

	const std::string menu_search[] = {
		"Search for a person by name",
		"Search for a person by birthdate",
		"Return to main menu"
	};

	const std::string menu_continue_edit[] = {
		"Continue editting",
		"Return to main menu"
	};

	const std::string menu_continue_search[] = {
		"Continue searching",
		"Return to main menu"
	};
	const std::string menu_continue_remove[] = {
		"Continue removeing",
		"Return to main menu"
	};

	const std::string menu_display[] = {
		"Display by descending birth dates",
		"Display by alphabetical name order",
		"Display using breadth first for the sorted names",
		"Display using breadth first for the sorted dates",
		"Return to main menu"
	};

	const std::string menu_continue_display[] = {
		"Continue viewing the database",
		"Return to main menu"
	};


#endif

}
