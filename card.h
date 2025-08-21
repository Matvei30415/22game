#ifndef CARD_H
#define CARD_H

#include <vector>

enum type_denomination {
    digital_card,
    picture_card
};

union denomination
{
    short digital_cards;
    char picture_cards;
};

struct card
{
    short id;
    type_denomination type;
    denomination value;
    char suit;
    double quality;
};

using card_list = std::vector<card>;

#endif