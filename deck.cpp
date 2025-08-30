#include "deck.h"

// Инициализация колоды
Deck::Deck()
{
    deckCards.push_back({1, Card::Digital, 4, '\0', 'G', 11.0 / 264.0});
    deckCards.push_back({2, Card::Digital, 6, '\0', 'G', 11.0 / 264.0});
    deckCards.push_back({3, Card::Digital, 8, '\0', 'G', 11.0 / 264.0});
    deckCards.push_back({4, Card::Digital, 10, '\0', 'G', 11.0 / 264.0});
    deckCards.push_back({5, Card::Digital, 12, '\0', 'G', 11.0 / 264.0});
    deckCards.push_back({6, Card::Digital, 14, '\0', 'G', 11.0 / 264.0});
    deckCards.push_back({7, Card::Digital, 16, '\0', 'G', 11.0 / 264.0});
    deckCards.push_back({8, Card::Digital, 18, '\0', 'G', 11.0 / 264.0});
    deckCards.push_back({9, Card::Digital, 4, '\0', 'G', 11.0 / 264.0});
    deckCards.push_back({10, Card::Digital, 6, '\0', 'G', 11.0 / 264.0});
    deckCards.push_back({11, Card::Digital, 8, '\0', 'G', 11.0 / 264.0});
    deckCards.push_back({12, Card::Digital, 10, '\0', 'G', 11.0 / 264.0});
    deckCards.push_back({13, Card::Digital, 12, '\0', 'G', 11.0 / 264.0});
    deckCards.push_back({14, Card::Digital, 14, '\0', 'G', 11.0 / 264.0});
    deckCards.push_back({15, Card::Digital, 16, '\0', 'G', 11.0 / 264.0});
    deckCards.push_back({16, Card::Digital, 18, '\0', 'G', 11.0 / 264.0});
    deckCards.push_back({17, Card::Digital, 4, '\0', 'G', 11.0 / 264.0});
    deckCards.push_back({18, Card::Digital, 6, '\0', 'G', 11.0 / 264.0});
    deckCards.push_back({19, Card::Digital, 8, '\0', 'G', 11.0 / 264.0});
    deckCards.push_back({20, Card::Digital, 10, '\0', 'G', 11.0 / 264.0});
    deckCards.push_back({21, Card::Digital, 12, '\0', 'G', 11.0 / 264.0});
    deckCards.push_back({22, Card::Digital, 14, '\0', 'G', 11.0 / 264.0});
    deckCards.push_back({23, Card::Digital, 16, '\0', 'G', 11.0 / 264.0});
    deckCards.push_back({24, Card::Digital, 18, '\0', 'G', 11.0 / 264.0});
    deckCards.push_back({25, Card::Digital, 4, '\0', 'C', 35.0 / 264.0});
    deckCards.push_back({26, Card::Digital, 6, '\0', 'C', 35.0 / 264.0});
    deckCards.push_back({27, Card::Digital, 8, '\0', 'C', 35.0 / 264.0});
    deckCards.push_back({28, Card::Digital, 10, '\0', 'C', 35.0 / 264.0});
    deckCards.push_back({29, Card::Digital, 12, '\0', 'C', 35.0 / 264.0});
    deckCards.push_back({30, Card::Digital, 14, '\0', 'C', 35.0 / 264.0});
    deckCards.push_back({31, Card::Digital, 16, '\0', 'C', 35.0 / 264.0});
    deckCards.push_back({32, Card::Digital, 18, '\0', 'C', 35.0 / 264.0});
    deckCards.push_back({33, Card::Picture, 0, 'L', 'G', 11.0 / 264.0});
    deckCards.push_back({34, Card::Picture, 0, 'G', 'G', 11.0 / 264.0});
    deckCards.push_back({35, Card::Picture, 0, 'L', 'G', 11.0 / 264.0});
    deckCards.push_back({36, Card::Picture, 0, 'G', 'G', 11.0 / 264.0});
    deckCards.push_back({37, Card::Picture, 0, 'L', 'G', 11.0 / 264.0});
    deckCards.push_back({38, Card::Picture, 0, 'G', 'G', 11.0 / 264.0});
    deckCards.push_back({39, Card::Picture, 0, 'L', 'C', 35.0 / 264.0});
    deckCards.push_back({40, Card::Picture, 0, 'G', 'C', 35.0 / 264.0});
    deckCards.push_back({41, Card::Picture, 0, 'H', 'G', 11.0 / 264.0});
    deckCards.push_back({42, Card::Picture, 0, 'H', 'G', 11.0 / 264.0});
    deckCards.push_back({43, Card::Picture, 0, 'H', 'G', 11.0 / 264.0});
    deckCards.push_back({44, Card::Digital, 2, '\0', 'G', 11.0 / 264.0});
    deckCards.push_back({45, Card::Digital, 2, '\0', 'G', 11.0 / 264.0});
    deckCards.push_back({46, Card::Digital, 2, '\0', 'C', 35.0 / 264.0});
    deckCards.push_back({47, Card::Digital, 2, '\0', 'H', 275.0 / 264.0});
    deckCards.push_back({48, Card::Digital, 20, '\0', 'D', 275.0 / 264.0});
}

// Тасовка колоды
void Deck::shuffle()
{
    srand(time(NULL));
    for (short i = deck_size - 1; i > 1; i--)
    {
        short j = rand() % i;
        std::swap(deckCards[i], deckCards[j]);
    }
}

// Раздача карт
void Deck::dealHand(std::vector<Card> &hand, short count)
{
    for (short i = 0; i < count; i++)
    {
        hand.push_back(deckCards[0]);
        deckCards.erase(begin(deckCards));
    }
}