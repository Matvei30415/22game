#pragma once

#include "consoleIO.h"
#include "card.h"
#include "deck.h"
#include "table.h"
#include "player.h"
#include "human.h"
#include "bot.h"

class Game
{
    enum class Turn : unsigned char
    {
        player1,
        player2
    };
    enum class Mode : short
    {
        withBot = 1,
        withOtherPlayer = 2,
    };
    Mode mode;
    short target;
    Turn lastTrick;
    Turn turn;

public:
    Game()
    {
        turn = Turn::player1;
    }
    void mainMenu(ConsoleView &view);
    void startOneRound(ConsoleView &view, Deck &deck, Table &table, Player &player1, Player &player2);
    void startGame(ConsoleView &view);

private:
    void processLastTrick(Table &table, Player &player1, Player &player2);
    void processGame(ConsoleView &view, Deck &deck, Table &table, Player &player1, Player &player2);
};
