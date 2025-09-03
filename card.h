#pragma once

#include <vector>
#include <variant>
#include <stdexcept>

class Card
{
public:
    enum class CardKind : unsigned char
    {
        Digital,
        Picture
    };
    enum class Suit : unsigned char
    {
        General = 'G',
        Clubs = 'C',
        Diamonds = 'D',
        Hearts = 'H',
    };
    enum class Picture : unsigned char
    {
        Gentleman = 'G',
        Lady = 'L',
        Hunter = 'H'
    };
    Card() = default;
    Card(int id, CardKind kind, int value, Suit suit, double quality);
    Card(int id, CardKind kind, Picture value, Suit suit, double quality);
    int getID() const;
    CardKind getKind() const;
    Suit getSuit() const;
    int getDigitalValue() const;
    Picture getPictureValue() const;
    double getQuality() const;

private:
    int id;
    CardKind kind;
    std::variant<int, Picture> value;
    Suit suit;
    double quality;
};