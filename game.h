#pragma once

#include "card.h"
#include "consoleIO.h"
#include "deck.h"
#include "table.h"
#include "player.h"
#include "human.h"
#include "bot.h"

enum Turn
{
    player1Turn = 1,
    player2Turn = 2
};

class Game
{
    GameMode mode;
    Turn lastTrick;
    Turn turn;

public:
    Game()
    {
        turn = player1Turn;
    }
    void mainMenu();
    void startGame();

private:
    void processLastTrick(Table &table, Player &player1, Player &player2);
    void processGame(Deck &deck, Table &table, Player &player1, Player &player2);
    // Строго функции ввода-вывода
    void printResults(Player &player1, Player &player2);
    void printRules();
    void printMenu();
    short menuInput(short min, short max);
};
