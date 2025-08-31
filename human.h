#pragma once

#include "card.h"
#include "points.h"
#include "game_mode.h"
#include "console_io.h"
#include "player.h"

class HumanPlayer : public Player
{
public:
    HumanPlayer(std::string name) : Player(name) {}
    void makeMove(Player &table, game_mode mode) override;
    bool process_trick(Player &table_hand);
    bool validate_digital_card_sum(short sum = 0, short start_index = 0);
    bool validate_trick();
};
