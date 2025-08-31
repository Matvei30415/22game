#pragma once

#include "card.h"

class Points
{
public:
    Points() { more_cards = '\0'; more_clubs = twenty_of_diamonds = ace_of_hearts = false;};
    void сalculate_points(std::vector<Card> &tricks);
    void get_points(char &more_cards, bool &more_clubs, bool &twenty_of_diamonds, bool &ace_of_hearts);

private:
    char more_cards;
    bool more_clubs;
    bool twenty_of_diamonds;
    bool ace_of_hearts;
};
