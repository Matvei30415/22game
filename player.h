#pragma once

#include "card_list.h"
#include "points.h"
#include "game_mode.h"
#include "io_custom.h"
#include "hunter.h"

bool validate_digital_card_sum(card_list &selected_cards, card &current_selected_card, short sum = 0, short start_index = 0);

bool validate_trick(card_list &selected_cards, card &current_selected_card, short size, short sum = 0);

bool process_trick(card_list &table_hand, card_list &current_hand, card_list &current_tricks, card_list &selected_cards, short &current_selected_card_index);

void select_cards_for_trick(card_list &selected_cards, card_list &table_hand, card_list &current_hand, card_list &current_tricks);

short select_card_from_hand(card_list &table_hand, card_list &current_hand, card_list &current_tricks);

void process_player_move(card_list &table_hand, card_list &current_hand, card_list &current_tricks, card_list &selected_cards, bool &is_trick, const game_mode mode);