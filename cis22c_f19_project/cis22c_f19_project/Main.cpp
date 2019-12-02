#include <iostream>
#include "GUI.h"
#include "Movie.h"
#include "List.h"
#include "menu.h"
#include "menu_dialog.h"

using namespace std;

int main()
{
	//string str1 = "ThanksGiving";
	//List<string> g1;
	//g1.append("Horror");
	//g1.append("Comedey");
	//List<string> c1;
	//g1.append("Jon Doe");
	//g1.append("Herry Styles");
	//cout << c1;
	//Movie m(str1, 2019, 8.0, &g1, &c1);
	////cout << m.getGenre() << endl;
	////cout << m << endl;

	bool end = true;

	do
	{
		std::cout << "Welcome to NotNetflix!" << std::endl;
		int choice = menu_prompt("What would you like to do?", menu_operations, 5);
		switch (choice)
		{
		case 1:
			GUI::UI_search();
			break;

		case 2:
			GUI::UI_add();
			break;

		case 3:
			GUI::UI_remove();
			break;
		
		case 4:
			GUI::UI_edit();
			break;

		default:
			end = false;
			break;
		}
	} while (end);

	return 0;
}