#include "consoleIO.h"
#include "game.h"
// #include <cstdlib>
// #include <ctime>

int main(void)
{
    // std::srand(static_cast<unsigned>(std::time(nullptr)));
    startConsole();
    clearConsole();
    ConsoleView view;
    Game game;
    game.mainMenu(view);
    game.startGame(view);
    return 0;
}