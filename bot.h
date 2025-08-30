#pragma once

#include "console_io.h"
#include "hunter.h"
#include "player.h"

class BotPlayer : public Player
{
public:
    BotPlayer(std::string name) : Player(name) {}
    void makeMove(Player &table, game_mode mode) override;
};

void find_digital_combinations(std::vector<Card> &current_hand, Card &current_card, short n, std::vector<Card> &combo, std::vector<Card> &max_combo, double &max_combo_quality, bool &res, short start = 0);

bool find_picture_combinations(std::vector<Card> &current_hand, Card &current_card, std::vector<Card> &max_combo, double max_combo_quality);

bool find_hunter_combinations(std::vector<Card> &current_hand, Card &current_card, std::vector<Card> &combo, std::vector<Card> &max_combo, double max_combo_quality);

short search_trick(std::vector<Card> &selected_cards, std::vector<Card> &table_hand, std::vector<Card> &current_hand, std::vector<Card> &max_combo);