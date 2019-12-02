#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdlib.h>
#include "menu.h"

int GUI::menu_prompt(std::string prompt, const std::string choices[], int choices_length) {
	std::cout << prompt << std::endl << std::endl;
	for (int i = 0; i < choices_length; i++) {
		std::cout << i + 1 << ": " << choices[i] << std::endl;
	}
	std::cout << std::endl;

	std::string choice_str;
	int choice;
	// Loops the input prompt until a valid choice has been inputted.
	while (true) {
		std::cout << "> ";
		//t_os << "> ";
		if (getline(std::cin, choice_str)) {
			//t_os << choice_str;
			choice = atoi(choice_str.c_str()) - 1;
			if (choice < choices_length) {
				break;
			}
		}
		std::cout << "Sorry, your choice was invalid. Please enter an integer "
			"from the options above." << std::endl;
		//t_os << "Sorry, your choice was invalid. Please enter an integer "
		//	"from the options above." << std::endl;
	}

	std::cout << std::endl;
	//t_os << std::endl;
	return choice + 1;
}