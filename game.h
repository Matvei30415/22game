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

void processLastTrick(Turn lastTrick, Table &table, Player &player1, Player &player2);

void processGame(Deck &deck, gameMode mode, Table &table,
                  Player &player1, Player &player2, Turn &lastTrick);

void startGame(gameMode mode);