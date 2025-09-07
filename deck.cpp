#include "deck.h"
#include <random>
#include <algorithm>
// #include <cstdlib>

// Инициализация колоды
void Deck::init()
{
    auto addDigital = [&](int id, int value, Card::Suit suit, double q)
    {
        deckCards.emplace_back(id, Card::Kind::Digital, value, suit, q);
    };

    auto addPicture = [&](int id, Card::Picture pic, Card::Suit suit, double q)
    {
        deckCards.emplace_back(id, Card::Kind::Picture, pic, suit, q);
    };

    for (int i = 0; i < 48; i++)
    {
        if (i > 45)
        {
            addDigital(i + 1, 2, Card::Suit::Hearts, kBestQuality);
            addDigital(i + 2, 20, Card::Suit::Diamonds, kBestQuality);
            i++;
        }
        else if (i > 42)
        {
            addPicture(i + 1, Card::Picture::Hunter, Card::Suit::General, kStandartQuality);
        }
        else if (i > 40)
        {
            addPicture(i + 1, Card::Picture::Lady, Card::Suit::Clubs, kClubsQuality);
            addPicture(i + 2, Card::Picture::Gentleman, Card::Suit::Clubs, kClubsQuality);
            i++;
        }
        else if (i > 34)
        {
            addPicture(i + 1, Card::Picture::Lady, Card::Suit::General, kStandartQuality);
            addPicture(i + 2, Card::Picture::Gentleman, Card::Suit::General, kStandartQuality);
            i++;
        }
        else if (i > 25)
            addDigital(i + 1, 2 + 2 * ((i + 1) % 9), Card::Suit::Clubs, kClubsQuality);
        else if (i > 17)
            addDigital(i + 1, 4 + 2 * (i % 9), Card::Suit::General, kStandartQuality);
        else
            addDigital(1 + i, 2 + 2 * (i % 9), Card::Suit::General, kStandartQuality);
    }
}

// Получить колоду
const std::vector<Card> &Deck::getDeckCards() const
{
    return this->deckCards;
}

// Перемешать колоду
void Deck::shuffle()
{
    static std::mt19937 rng(std::random_device{}());
    std::shuffle(deckCards.begin(), deckCards.end(), rng);
    // for (std::size_t i = kDeckSize - 1; i > 1; i--)
    // {
    //     std::swap(deckCards[i], deckCards[rand() % i]);
    // }
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