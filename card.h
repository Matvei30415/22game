#pragma once

#include <vector>
#include <variant>
#include <stdexcept>

class Card
{
public:
    enum class Kind : unsigned char
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
    Card(int id, Kind kind, int value, Suit suit, double quality);
    Card(int id, Kind kind, Picture value, Suit suit, double quality);
    int getID() const;
    Kind getKind() const;
    Suit getSuit() const;
    int getDigitalValue() const;
    Picture getPictureValue() const;
    double getQuality() const;

private:
    int id;
    Kind kind;
    std::variant<int, Picture> value;
    Suit suit;
    double quality;
};