#pragma once

#include "card.h"
#include "player.h"

inline constexpr std::size_t kDeckSize = 48;
inline constexpr std::size_t kCardsInHand = 4;
class Deck {
public:
    Deck();
    void shuffle();
    void dealHand(Player &player, std::size_t count = 4);
    const std::vector<Card> &getDeckCards() const;
private:
    std::vector<Card> deckCards;
};