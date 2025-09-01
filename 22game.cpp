#include "game.h"

int main(void)
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    clearConsole();
    Game game;
    game.mainMenu();
    game.startGame();
    return 0;
}