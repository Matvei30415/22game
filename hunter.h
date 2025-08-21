#ifndef HUNTER_H
#define HUNTER_H

#include "card.h"
#include "basic.h"

bool process_hunter_move(std::vector<card> &table_hand, std::vector<card> &current_hand, std::vector<card> &current_tricks, short chosen_card_index);

#endif