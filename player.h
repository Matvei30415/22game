#ifndef PLAYER_H
#define PLAYER_H

#include "io_custom.h"
#include "hunter.h"

bool validate_digital_card_sum(std::vector<card> &selected_cards, card &current_selected_card, short sum = 0, short start_index = 0);

bool validate_trick(std::vector<card> &selected_cards, card &current_selected_card, short size, short sum = 0);

bool process_trick(std::vector<card> &table_hand, std::vector<card> &current_hand, std::vector<card> &current_tricks, std::vector<card> &selected_cards, short current_selected_card_index);

void select_cards_for_trick(std::vector<card> &selected_cards, std::vector<card> &table_hand, std::vector<card> &current_hand, std::vector<card> &current_tricks);

short select_card_from_hand(std::vector<card> &table_hand, std::vector<card> &current_hand, std::vector<card> &current_tricks);

void process_player_move(std::vector<card> &table_hand, std::vector<card> &current_hand, std::vector<card> &current_tricks, std::vector<card> &selected_cards, bool &is_trick);

#endif