#ifndef OUTPUT_H
#define OUTPUT_H

#include "card.h"
#include "points.h"
#include "basic.h"
#include <iostream>

void moving_cursor(short i);

void print_card_list(std::vector<card> &current_cards, short len);

void print_hand(std::vector<card> &current_cards, short len);

void print_bot_hand(std::vector<card> &current_cards, short len);

void print_table(std::vector<card> &current_cards, short len);

void print_tricks(std::vector<card> &player_1_tricks, std::vector<card> &player_2_tricks);

void print_results(points &player_1_results, points &player_2_results);

#endif