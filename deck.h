#pragma once

#include "card.h"
#include <cstdlib>
#include <ctime>

enum : short
{
    deckSize = 48,
    cardsInHand = 4
};
class Deck {
public:
    Deck();
    void shuffle();
    void dealHand(std::vector<Card> &hand, short count = 4);
    bool empty() const;
private:
    std::vector<Card> deckCards;
};