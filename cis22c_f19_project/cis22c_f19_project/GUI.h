#ifndef _GUI_H
#define _GUI_H

#include <iostream>
#include "GUI.h"
//#include "Movie.h"
#include "TableDatabase.h"
#include "List.h"
#include "menu.h"
#include "menu_dialog.h"

using namespace GUI;

namespace GUI
{
	// Search help funciton
	void UI_search(/*const database& database*/);
	void UI_search_by_title(std::string in_title/*,const database& database*/);
	void UI_search_by_year(int in_year/*,const database& database*/);
	void UI_search_by_ratings(double in_ratings/*,const database& database*/);
	void UI_search_by_genre(std::string in_genre/*,const database& database*/);
	void UI_search_by_cast(std::string in_genre/*,const database& database*/);
	// Add help funciton
	void UI_add(/*const database& database*/);
	// Remove help funciton
	void UI_remove(/*const database& database*/);
	void promptLoadFile(TableDatabase & db);
	// Edit help funciton
	void UI_edit(/*const database& database*/);
	void UI_run_application();
}
#endif
