#pragma once

#include <iostream>
#include <string>
#include "Movie.h"
#include "List.h"
#include "menu.h"
#include "menu_dialog.h"

class GUI
{
private:
    GUI();
public:
    static void UI_search();
    static void UI_add();
    static void UI_remove();
    static void UI_edit();
};
