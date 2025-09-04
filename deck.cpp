#include "deck.h"

// Инициализация колоды
Deck::Deck()
{
    deckCards.push_back(Card(1, Card::CardKind::Digital, 4, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(2, Card::CardKind::Digital, 6, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(3, Card::CardKind::Digital, 8, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(4, Card::CardKind::Digital, 10, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(5, Card::CardKind::Digital, 12, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(6, Card::CardKind::Digital, 14, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(7, Card::CardKind::Digital, 16, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(8, Card::CardKind::Digital, 18, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(9, Card::CardKind::Digital, 4, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(10, Card::CardKind::Digital, 6, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(11, Card::CardKind::Digital, 8, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(12, Card::CardKind::Digital, 10, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(13, Card::CardKind::Digital, 12, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(14, Card::CardKind::Digital, 14, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(15, Card::CardKind::Digital, 16, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(16, Card::CardKind::Digital, 18, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(17, Card::CardKind::Digital, 4, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(18, Card::CardKind::Digital, 6, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(19, Card::CardKind::Digital, 8, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(20, Card::CardKind::Digital, 10, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(21, Card::CardKind::Digital, 12, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(22, Card::CardKind::Digital, 14, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(23, Card::CardKind::Digital, 16, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(24, Card::CardKind::Digital, 18, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(25, Card::CardKind::Digital, 4, Card::Suit::Clubs, 35.0 / 264.0));
    deckCards.push_back(Card(26, Card::CardKind::Digital, 6, Card::Suit::Clubs, 35.0 / 264.0));
    deckCards.push_back(Card(27, Card::CardKind::Digital, 8, Card::Suit::Clubs, 35.0 / 264.0));
    deckCards.push_back(Card(28, Card::CardKind::Digital, 10, Card::Suit::Clubs, 35.0 / 264.0));
    deckCards.push_back(Card(29, Card::CardKind::Digital, 12, Card::Suit::Clubs, 35.0 / 264.0));
    deckCards.push_back(Card(30, Card::CardKind::Digital, 14, Card::Suit::Clubs, 35.0 / 264.0));
    deckCards.push_back(Card(31, Card::CardKind::Digital, 16, Card::Suit::Clubs, 35.0 / 264.0));
    deckCards.push_back(Card(32, Card::CardKind::Digital, 18, Card::Suit::Clubs, 35.0 / 264.0));
    deckCards.push_back(Card(33, Card::CardKind::Picture, Card::Picture::Lady, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(34, Card::CardKind::Picture, Card::Picture::Gentleman, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(35, Card::CardKind::Picture, Card::Picture::Lady, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(36, Card::CardKind::Picture, Card::Picture::Gentleman, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(37, Card::CardKind::Picture, Card::Picture::Lady, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(38, Card::CardKind::Picture, Card::Picture::Gentleman, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(39, Card::CardKind::Picture, Card::Picture::Lady, Card::Suit::Clubs, 35.0 / 264.0));
    deckCards.push_back(Card(40, Card::CardKind::Picture, Card::Picture::Gentleman, Card::Suit::Clubs, 35.0 / 264.0));
    deckCards.push_back(Card(41, Card::CardKind::Picture, Card::Picture::Hunter, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(42, Card::CardKind::Picture, Card::Picture::Hunter, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(43, Card::CardKind::Picture, Card::Picture::Hunter, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(44, Card::CardKind::Digital, 2, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(45, Card::CardKind::Digital, 2, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(46, Card::CardKind::Digital, 2, Card::Suit::Clubs, 35.0 / 264.0));
    deckCards.push_back(Card(47, Card::CardKind::Digital, 2, Card::Suit::Hearts, 275.0 / 264.0));
    deckCards.push_back(Card(48, Card::CardKind::Digital, 20, Card::Suit::Diamonds, 275.0 / 264.0));
}

// Перемешать колоду
void Deck::shuffle()
{
    for (short i = kDeckSize - 1; i > 1; i--)
    {
        std::swap(deckCards[i], deckCards[rand() % i]);
    }
}

// Раздать карт
void Deck::dealHand(Player &player, short count)
{
    for (short i = 0; i < count; i++)
    {
        player.addCardToHand(deckCards.back());
        deckCards.pop_back();
    }
}