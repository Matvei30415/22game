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
    void makeMove(Player &table_hand, game_mode mode) override;
};

bool validate_digital_card_sum(std::vector<Card> &selected_cards, Card &current_selected_card, short sum = 0, short start_index = 0);

bool validate_trick(std::vector<Card> &selected_cards, Card &current_selected_card, short size, short sum = 0);

bool process_trick(std::vector<Card> &table_hand, std::vector<Card> &current_hand, std::vector<Card> &current_tricks, std::vector<Card> &selected_cards, short &current_selected_card_index);

void select_cards_for_trick(std::vector<Card> &selected_cards, Player &table, Player &player);

short select_card_from_hand(std::vector<Card> &table_hand, std::vector<Card> &current_hand, std::vector<Card> &current_tricks);