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
	// Add help funciton
	void UI_add(NotIMDB_Database& db);
	// Remove help funciton
	void UI_remove(NotIMDB_Database & db);
	void promptLoadFile(NotIMDB_Database & db);
	// Edit help funciton
	void UI_edit(NotIMDB_Database & db);
	void UI_run_application(NotIMDB_Database & db);
	std::string UI_pick_from_potential_matches_to_edit(NotIMDB_Database& db, const std::string& userIn, bool& exit);
}
#endif
