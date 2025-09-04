#pragma once

#include "card.h"
#include "player.h"
#include <cstdlib>
#include <ctime>

inline constexpr short kDeckSize = 48;
inline constexpr short kCardsInHand = 4;
class Deck {
public:
    Deck();
    void shuffle();
    void dealHand(Player &player, short count = 4);
private:
    std::vector<Card> deckCards;
};