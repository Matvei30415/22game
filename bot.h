#pragma once

#include "card_list.h"
#include "points.h"
#include "io_custom.h"
#include "hunter.h"

void find_digital_combinations(card_list &current_hand, card &current_card, short n, card_list &combo, card_list &max_combo, double &max_combo_quality, bool &res, short start = 0);

bool find_picture_combinations(card_list &current_hand, card &current_card, card_list &max_combo, double max_combo_quality);

bool find_hunter_combinations(card_list &current_hand, card &current_card, card_list &combo, card_list &max_combo, double max_combo_quality);

void search_trick(card_list &selected_cards, card_list &table_hand, card_list &current_hand, card_list &max_combo, short &max_combo_card_index);

void process_bot_move(card_list &table_hand, card_list &current_hand, card_list &current_tricks, card_list &selected_cards);

void process_bot_move(card_list &table_hand, card_list &current_hand, card_list &current_tricks, card_list &selected_cards, bool &is_trick);