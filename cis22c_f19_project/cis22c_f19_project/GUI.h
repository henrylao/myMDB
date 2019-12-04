#ifndef _GUI_H
#define _GUI_H

#include <iostream>
#include "NotIMDB_Database.h"
#include "Movie.h"
#include "List.h"
#include "menu.h"
#include "menu_dialog.h"
#include "CustomException.h"

namespace GUI
{
	bool isValidName(std::string name);
	bool isValidDay(std::string day);
	bool isValidMonth(std::string month);
	bool isValidYear(std::string month);
	void UI_search(const NotIMDB_Database & db);
	// Search help funciton
	//void UI_search(/*const database& database*/);
	void UI_search_by_title(std::string in_title, const NotIMDB_Database& db);
	void UI_search_by_year(int in_year, const NotIMDB_Database& db);
	void UI_search_by_ratings(double in_ratings, const NotIMDB_Database& db);
	void UI_search_by_genre(std::string in_genre, const NotIMDB_Database& db);
	// Add help funciton
	void UI_add(NotIMDB_Database& db);
	// Remove help funciton
	void UI_remove(NotIMDB_Database & db);
	void promptLoadFile(NotIMDB_Database & db);
	// Edit help funciton
	void UI_edit(NotIMDB_Database & db);
	void UI_edit_old(NotIMDB_Database & db);
	void UI_run_application();
}
#endif
