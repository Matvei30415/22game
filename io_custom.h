#ifndef IO_H
#define IO_H

#include "card.h"
#include "basic.h"
#include "points.h"
#include <iostream>
#include <fstream>
#include <string>
#include <utility>

using input_error_codes = enum {
    invalid_input = -1,
    invalid_index = -2
};

short get_move_input(short min_index, short max_index);

void moving_cursor(short i);

void print_card_list(std::vector<card> &current_cards, short len);

void print_hand(std::vector<card> &current_cards, short len);

void print_bot_hand(std::vector<card> &current_cards, short len);

void print_table(std::vector<card> &current_cards, short len);

void print_tricks(std::vector<card> &player_1_tricks, std::vector<card> &player_2_tricks);

void print_results(points &player_1_results, points &player_2_results);

void print_rules();

void print_menu();

#endif