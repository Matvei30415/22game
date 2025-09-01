#include "mainMenu.h"
#include "game.h"
#include <windows.h>

int main(void)
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    clearConsole();
    gameMode mode;
    mode = mainMenu();
    startGame(mode);
    return 0;
}