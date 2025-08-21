#ifndef BOT_H
#define BOT_H

#include "card.h"
#include "basic.h"
#include "output.h"
#include "hunter.h"

void find_digital_combinations(std::vector<card> &current_hand, card &current_card, short n, std::vector<card> &combo, std::vector<card> &max_combo, double &max_combo_quality, bool &res, short start = 0);

bool find_picture_combinations(std::vector<card> &current_hand, card &current_card, std::vector<card> &max_combo, double max_combo_quality);

bool find_hunter_combinations(std::vector<card> &current_hand, card &current_card, std::vector<card> &combo, std::vector<card> &max_combo, double max_combo_quality);

void search_trick(std::vector<card> &selected_cards, std::vector<card> &table_hand, std::vector<card> &current_hand, std::vector<card> &max_combo, short &max_combo_card_index);

void process_bot_move(std::vector<card> &table_hand, std::vector<card> &current_hand, std::vector<card> &current_tricks, std::vector<card> &selected_cards);

void process_bot_move(std::vector<card> &table_hand, std::vector<card> &current_hand, std::vector<card> &current_tricks, std::vector<card> &selected_cards, bool &is_trick);

#endif