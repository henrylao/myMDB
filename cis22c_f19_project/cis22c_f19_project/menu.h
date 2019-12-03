#include <string>
#include <iostream>
//#include <fstream>
#include <cstdlib>
#include <stdlib.h>

#ifndef MENU_H
#define MENU_H

namespace GUI {

	/* Outputs a prompt and ordered list (starting from 1) and requests input from
	 * the user for one of the options.
	 *
	 * Returns the index (i.e. starting from 0) of the option selected.
	 */
	int menu_prompt(
		const std::string prompt, // Message to prompt the user to select an option.
		const std::string choices[], // Array of choices to provide to the user.
		int choices_length // Number of items in the choices array.
	);
};
#endif
