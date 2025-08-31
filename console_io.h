#pragma once

#include "card.h"
#include "points.h"
#include "game_mode.h"
#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <unordered_set>
#include <windows.h>

enum input_error_codes {
    invalid_input = -1,
    invalid_index = -2
};

void clear_console();

short get_input(short min_index, short max_index);

short get_trick_input(std::vector<Card> &table_hand, std::vector<Card> &selected_cards);

short get_card_input(std::vector<Card> &table_hand, std::vector<Card> &current_hand);

short get_menu_input(short min_index, short max_index);

void pass_move();

void print_line();

void moving_cursor(short i);

void print_card(Card &current_card);

void print_card_list(std::vector<Card> &current_cards, short len);

void print_hand(std::vector<Card> &current_cards, short len);

void print_bot_hand(std::vector<Card> &current_cards, short len);

void print_table(std::vector<Card> &current_cards, short len);

void print_tricks(std::vector<Card> &player_1_tricks, std::vector<Card> &player_2_tricks);

void print_results(Points &player_1_results, Points &player_2_results, game_mode mode);

void print_rules();

void print_menu();

void print_move(Card &selected_card, std::vector<Card> &selected_cards);

void confirm_move(Card &selected_card, std::vector<Card> &selected_cards);