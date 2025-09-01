#pragma once

#include "card.h"
#include "consoleIO.h"
#include "table.h"
#include "player.h"

class HumanPlayer : public Player
{
public:
    HumanPlayer(std::string name) : Player(name) {}
    void makeMove(Table &table, gameMode mode) override;
    bool processTrick(Table &table);
    bool validateTrick();
    bool validateDigitalCardSum(short sum = 0, short start_index = 0);
};
