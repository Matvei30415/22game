#pragma once

#include "card.h"
#include "player.h"

inline constexpr std::size_t kDeckSize = 48;
inline constexpr std::size_t kCardsInHand = 4;
inline constexpr double kStandartQuality = 11.0/264.0;
inline constexpr double kClubsQuality = 35.0/264.0;
inline constexpr double kBestQuality = 275.0/264.0;
class Deck {
public:
    Deck();
    void shuffle();
    void dealHand(Player &player, std::size_t count = 4);
    const std::vector<Card> &getDeckCards() const;
private:
    std::vector<Card> deckCards;
};