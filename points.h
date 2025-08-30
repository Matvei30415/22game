#pragma once

#include "card_list.h"

class Points
{
public:
    void сalculate_points(CardList &tricks);
    void get_points(char &more_cards, bool &more_clubs, bool &twenty_of_diamonds, bool &ace_of_hearts);

private:
    char more_cards;
    bool more_clubs;
    bool twenty_of_diamonds;
    bool ace_of_hearts;
};
