#pragma once

#include "card_list.h"
#include "points.h"
#include "console_io.h"
#include "hunter.h"
#include "player.h"

class BotPlayer : public Player
{
public:
    BotPlayer(std::string name) : Player(name) {}
    void makeMove(Player &table, game_mode mode) override;
};

void find_digital_combinations(CardList &current_hand, Card &current_card, short n, CardList &combo, CardList &max_combo, double &max_combo_quality, bool &res, short start = 0);

bool find_picture_combinations(CardList &current_hand, Card &current_card, CardList &max_combo, double max_combo_quality);

bool find_hunter_combinations(CardList &current_hand, Card &current_card, CardList &combo, CardList &max_combo, double max_combo_quality);

short search_trick(CardList &selected_cards, CardList &table_hand, CardList &current_hand, CardList &max_combo);