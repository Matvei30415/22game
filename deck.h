#pragma once

#include "card.h"
#include <cstdlib>
#include <ctime>

class Deck {
public:
    Deck();
    void shuffle();
    void dealHand(std::vector<Card> &hand, short count = 4);
    bool empty() const;
private:
    std::vector<Card> deckCards;
};

enum
{
    deck_size = 48,
    cards_in_hand = 4
};