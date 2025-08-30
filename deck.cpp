#include "deck.h"

// Инициализация колоды
Deck::Deck()
{
    deckCards.add({1, Card::Digital, 4, '\0', 'G', 11.0 / 264.0});
    deckCards.add({2, Card::Digital, 6, '\0', 'G', 11.0 / 264.0});
    deckCards.add({3, Card::Digital, 8, '\0', 'G', 11.0 / 264.0});
    deckCards.add({4, Card::Digital, 10, '\0', 'G', 11.0 / 264.0});
    deckCards.add({5, Card::Digital, 12, '\0', 'G', 11.0 / 264.0});
    deckCards.add({6, Card::Digital, 14, '\0', 'G', 11.0 / 264.0});
    deckCards.add({7, Card::Digital, 16, '\0', 'G', 11.0 / 264.0});
    deckCards.add({8, Card::Digital, 18, '\0', 'G', 11.0 / 264.0});
    deckCards.add({9, Card::Digital, 4, '\0', 'G', 11.0 / 264.0});
    deckCards.add({10, Card::Digital, 6, '\0', 'G', 11.0 / 264.0});
    deckCards.add({11, Card::Digital, 8, '\0', 'G', 11.0 / 264.0});
    deckCards.add({12, Card::Digital, 10, '\0', 'G', 11.0 / 264.0});
    deckCards.add({13, Card::Digital, 12, '\0', 'G', 11.0 / 264.0});
    deckCards.add({14, Card::Digital, 14, '\0', 'G', 11.0 / 264.0});
    deckCards.add({15, Card::Digital, 16, '\0', 'G', 11.0 / 264.0});
    deckCards.add({16, Card::Digital, 18, '\0', 'G', 11.0 / 264.0});
    deckCards.add({17, Card::Digital, 4, '\0', 'G', 11.0 / 264.0});
    deckCards.add({18, Card::Digital, 6, '\0', 'G', 11.0 / 264.0});
    deckCards.add({19, Card::Digital, 8, '\0', 'G', 11.0 / 264.0});
    deckCards.add({20, Card::Digital, 10, '\0', 'G', 11.0 / 264.0});
    deckCards.add({21, Card::Digital, 12, '\0', 'G', 11.0 / 264.0});
    deckCards.add({22, Card::Digital, 14, '\0', 'G', 11.0 / 264.0});
    deckCards.add({23, Card::Digital, 16, '\0', 'G', 11.0 / 264.0});
    deckCards.add({24, Card::Digital, 18, '\0', 'G', 11.0 / 264.0});
    deckCards.add({25, Card::Digital, 4, '\0', 'C', 35.0 / 264.0});
    deckCards.add({26, Card::Digital, 6, '\0', 'C', 35.0 / 264.0});
    deckCards.add({27, Card::Digital, 8, '\0', 'C', 35.0 / 264.0});
    deckCards.add({28, Card::Digital, 10, '\0', 'C', 35.0 / 264.0});
    deckCards.add({29, Card::Digital, 12, '\0', 'C', 35.0 / 264.0});
    deckCards.add({30, Card::Digital, 14, '\0', 'C', 35.0 / 264.0});
    deckCards.add({31, Card::Digital, 16, '\0', 'C', 35.0 / 264.0});
    deckCards.add({32, Card::Digital, 18, '\0', 'C', 35.0 / 264.0});
    deckCards.add({33, Card::Picture, 0, 'L', 'G', 11.0 / 264.0});
    deckCards.add({34, Card::Picture, 0, 'G', 'G', 11.0 / 264.0});
    deckCards.add({35, Card::Picture, 0, 'L', 'G', 11.0 / 264.0});
    deckCards.add({36, Card::Picture, 0, 'G', 'G', 11.0 / 264.0});
    deckCards.add({37, Card::Picture, 0, 'L', 'G', 11.0 / 264.0});
    deckCards.add({38, Card::Picture, 0, 'G', 'G', 11.0 / 264.0});
    deckCards.add({39, Card::Picture, 0, 'L', 'C', 35.0 / 264.0});
    deckCards.add({40, Card::Picture, 0, 'G', 'C', 35.0 / 264.0});
    deckCards.add({41, Card::Picture, 0, 'H', 'G', 11.0 / 264.0});
    deckCards.add({42, Card::Picture, 0, 'H', 'G', 11.0 / 264.0});
    deckCards.add({43, Card::Picture, 0, 'H', 'G', 11.0 / 264.0});
    deckCards.add({44, Card::Digital, 2, '\0', 'G', 11.0 / 264.0});
    deckCards.add({45, Card::Digital, 2, '\0', 'G', 11.0 / 264.0});
    deckCards.add({46, Card::Digital, 2, '\0', 'C', 35.0 / 264.0});
    deckCards.add({47, Card::Digital, 2, '\0', 'H', 275.0 / 264.0});
    deckCards.add({48, Card::Digital, 20, '\0', 'D', 275.0 / 264.0});
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
void Deck::dealHand(CardList &hand, short count)
{
    for (short i = 0; i < count; i++)
    {
        deckCards.moveCardTo(hand);
    }
}