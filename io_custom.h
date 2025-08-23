#pragma once

#include "card_list.h"
#include "points.h"
#include <iostream>
#include <fstream>
#include <string>
#include <utility>

enum input_error_codes {
    invalid_input = -1,
    invalid_index = -2
};

short get_move_input(short min_index, short max_index);

void print_line();

void moving_cursor(short i);

void print_card_list(card_list &current_cards, short len);

void print_hand(card_list &current_cards, short len);

void print_bot_hand(card_list &current_cards, short len);

void print_table(card_list &current_cards, short len);

void print_tricks(card_list &player_1_tricks, card_list &player_2_tricks);

void print_results(points &player_1_results, points &player_2_results);

void print_rules();

void print_menu();