#include "consoleIO.h"
#include "game.h"

int main(void)
{
    startConsole();
    clearConsole();
    Game game;
    game.mainMenu();
    game.startGame();
    return 0;
}