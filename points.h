#ifndef POINTS_H
#define POINTS_H

#include "card.h"

struct points
{
    char get_more_cards;
    bool get_more_clubs;
    bool get_twenty_of_diamonds;
    bool get_ace_of_hearts;
};

void сalculate_points(points &results, std::vector<card> &current_hand, short len);

#endif