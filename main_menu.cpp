#include "main_menu.h"

// Обработка главного меню
game_mode main_menu()
{
    short selected_index = get_menu_input(0, 3);
    switch (selected_index)
    {
    case 1:
        return with_bot;
        break;
    case 2:
        return with_other_player;
        break;
    default:
        exit(0);
        break;
    }
}