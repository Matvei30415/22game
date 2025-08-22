#include "main_menu.h"
#include "game.h"
#include <windows.h>

int main(void)
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    game_mode mode;
    mode = main_menu();
    start_game(mode);
    return 0;
}