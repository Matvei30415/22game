#ifndef BASIC_H
#define BASIC_H

#include "card.h"
#include <algorithm>
#include <string>

enum game_mode {
    with_bot = 1,
    with_other_player = 2,
};

extern const std::string line;

void move_card(std::vector<card> &dst, std::vector<card> &src, short index = 0);

void clear_card_list(std::vector<card> &src);

void sort_card_list(std::vector<card> &src);

#endif