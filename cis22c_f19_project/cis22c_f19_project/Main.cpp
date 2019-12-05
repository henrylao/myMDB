#include <iostream>
#include "GUI.h"
#include "Movie.h"
#include "List.h"
#include "menu.h"
#include "menu_dialog.h"

using namespace std;

int main()
{
	NotIMDB_Database db;
	//db.unitTest();
	GUI::UI_run_application(db);
	//system("pause");
	return 0;
}