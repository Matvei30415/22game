#pragma once

#include "card_list.h"
#include "points.h"
#include "game_mode.h"
#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <windows.h>

enum input_error_codes {
    invalid_input = -1,
    invalid_index = -2
};

void clear_console();

short get_move_input(short min_index, short max_index);

void pass_move();

void print_line();

void moving_cursor(short i);

void print_card(Card &current_card);

void print_card_list(CardList &current_cards, short len);

void print_hand(CardList &current_cards, short len);

void print_bot_hand(CardList &current_cards, short len);

void print_table(CardList &current_cards, short len);

void print_tricks(CardList &player_1_tricks, CardList &player_2_tricks);

void print_results(Points &player_1_results, Points &player_2_results, game_mode mode);

void print_rules();

void print_menu();

void print_move(Card &selected_card, CardList &selected_cards);

void confirm_move(Card &selected_card, CardList &selected_cards);