#pragma once

#include "card.h"
#include "player.h"
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
    void dealHand(Player &player, short count = 4);
private:
    std::vector<Card> deckCards;
};