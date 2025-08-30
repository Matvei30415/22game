#pragma once

#include "card.h"

class Points
{
public:
    void сalculate_points(std::vector<Card> &tricks);
    void get_points(char &more_cards, bool &more_clubs, bool &twenty_of_diamonds, bool &ace_of_hearts);

private:
    char more_cards;
    bool more_clubs;
    bool twenty_of_diamonds;
    bool ace_of_hearts;
};
