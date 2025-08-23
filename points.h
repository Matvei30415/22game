#pragma once

#include "card_list.h"

struct points
{
    char get_more_cards;
    bool get_more_clubs;
    bool get_twenty_of_diamonds;
    bool get_ace_of_hearts;
};

void сalculate_points(points &results, card_list &current_hand, short len);