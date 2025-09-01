#include "mainMenu.h"

// Обработка главного меню
gameMode mainMenu()
{
    short mode = getMenuInput(0, 3);
    switch (mode)
    {
    case 1:
        return withBot;
        break;
    case 2:
        return withOtherPlayer;
        break;
    default:
        exit(0);
        break;
    }
}