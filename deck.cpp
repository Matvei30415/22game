#include "deck.h"

// Инициализация колоды
Deck::Deck()
{
    deckCards.push_back(Card(1, Card::Kind::Digital, 4, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(2, Card::Kind::Digital, 6, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(3, Card::Kind::Digital, 8, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(4, Card::Kind::Digital, 10, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(5, Card::Kind::Digital, 12, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(6, Card::Kind::Digital, 14, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(7, Card::Kind::Digital, 16, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(8, Card::Kind::Digital, 18, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(9, Card::Kind::Digital, 4, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(10, Card::Kind::Digital, 6, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(11, Card::Kind::Digital, 8, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(12, Card::Kind::Digital, 10, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(13, Card::Kind::Digital, 12, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(14, Card::Kind::Digital, 14, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(15, Card::Kind::Digital, 16, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(16, Card::Kind::Digital, 18, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(17, Card::Kind::Digital, 4, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(18, Card::Kind::Digital, 6, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(19, Card::Kind::Digital, 8, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(20, Card::Kind::Digital, 10, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(21, Card::Kind::Digital, 12, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(22, Card::Kind::Digital, 14, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(23, Card::Kind::Digital, 16, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(24, Card::Kind::Digital, 18, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(25, Card::Kind::Digital, 4, Card::Suit::Clubs, 35.0 / 264.0));
    deckCards.push_back(Card(26, Card::Kind::Digital, 6, Card::Suit::Clubs, 35.0 / 264.0));
    deckCards.push_back(Card(27, Card::Kind::Digital, 8, Card::Suit::Clubs, 35.0 / 264.0));
    deckCards.push_back(Card(28, Card::Kind::Digital, 10, Card::Suit::Clubs, 35.0 / 264.0));
    deckCards.push_back(Card(29, Card::Kind::Digital, 12, Card::Suit::Clubs, 35.0 / 264.0));
    deckCards.push_back(Card(30, Card::Kind::Digital, 14, Card::Suit::Clubs, 35.0 / 264.0));
    deckCards.push_back(Card(31, Card::Kind::Digital, 16, Card::Suit::Clubs, 35.0 / 264.0));
    deckCards.push_back(Card(32, Card::Kind::Digital, 18, Card::Suit::Clubs, 35.0 / 264.0));
    deckCards.push_back(Card(33, Card::Kind::Picture, Card::Picture::Lady, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(34, Card::Kind::Picture, Card::Picture::Gentleman, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(35, Card::Kind::Picture, Card::Picture::Lady, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(36, Card::Kind::Picture, Card::Picture::Gentleman, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(37, Card::Kind::Picture, Card::Picture::Lady, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(38, Card::Kind::Picture, Card::Picture::Gentleman, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(39, Card::Kind::Picture, Card::Picture::Lady, Card::Suit::Clubs, 35.0 / 264.0));
    deckCards.push_back(Card(40, Card::Kind::Picture, Card::Picture::Gentleman, Card::Suit::Clubs, 35.0 / 264.0));
    deckCards.push_back(Card(41, Card::Kind::Picture, Card::Picture::Hunter, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(42, Card::Kind::Picture, Card::Picture::Hunter, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(43, Card::Kind::Picture, Card::Picture::Hunter, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(44, Card::Kind::Digital, 2, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(45, Card::Kind::Digital, 2, Card::Suit::General, 11.0 / 264.0));
    deckCards.push_back(Card(46, Card::Kind::Digital, 2, Card::Suit::Clubs, 35.0 / 264.0));
    deckCards.push_back(Card(47, Card::Kind::Digital, 2, Card::Suit::Hearts, 275.0 / 264.0));
    deckCards.push_back(Card(48, Card::Kind::Digital, 20, Card::Suit::Diamonds, 275.0 / 264.0));
}

// Получить колоду
const std::vector<Card> &Deck::getDeckCards() const
{
    return this->deckCards;
}

// Перемешать колоду
void Deck::shuffle()
{
    for (std::size_t i = kDeckSize - 1; i > 1; i--)
    {
        std::swap(deckCards[i], deckCards[rand() % i]);
    }
}

// Раздать карт
void Deck::dealHand(Player &player, std::size_t count)
{
    for (std::size_t i = 0; i < count; i++)
    {
        player.addCardToHand(deckCards.back());
        deckCards.pop_back();
    }
}