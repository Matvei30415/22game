#pragma once

#include <vector>

enum type_denomination
{
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

class card_list : public std::vector<card>
{
public:
    card_list() = default;
    card_list(short size);
    static void move_card(card_list &dst, card_list &src, short index = 0);
    static void clear_card_list(card_list &src);
    static void sort_card_list(card_list &src);
};