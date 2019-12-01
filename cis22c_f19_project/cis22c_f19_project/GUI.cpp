#include <iostream>
#include "GUI.h"
#include "Movie.h"
#include "List.h"
#include "menu.h"
#include "menu_dialog.h"


void UI_search(/*const database& database*/) {
	int choice = menu_prompt("How do you want to search movies by?", menu_search, 6);
	switch (choice) {
	case 1: {
		UI_search_by_title(/*const database& database*/);
		break;
	}
	case 2: {
		UI_search_by_year(/*const database& database*/);
		break;
	}
	case 3: {
		UI_search_by_ratings(/*const database& database*/);
		break;
	}
	case 4: {
		UI_search_by_genre(/*const database& database*/);
		break;
	}
	case 5: {
		UI_search_by_cast(/*const database& database*/);
		break;
	}
	case 6:{
		return
	}
	}
}

void UI_add(/*const database& database*/) {

}

void UI_remove(/*const database& database*/) {

}

void UI_edit(/*const database& database*/) {

}

void UI_add(/*const database& database*/) {

}

void UI_remove(/*const database& database*/) {

}

void UI_edit(/*const database& database*/) {

}