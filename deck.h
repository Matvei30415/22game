#pragma once

#include "card_list.h"
#include <cstdlib>
#include <ctime>

class Deck {
public:
    Deck();
    void shuffle();
    void dealHand(CardList &hand, short count = 4);
    bool empty() const;
private:
    CardList deckCards;
};

enum
{
    deck_size = 48,
    cards_in_hand = 4
};