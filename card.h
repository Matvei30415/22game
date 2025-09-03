#pragma once

#include <vector>

class Card
{
public:
    enum Type
    {
        Digital,
        Picture
    };
    Card() = default;
    Card(short ID, Type type, short digitalValue, char pictureValue, char suit, double quality);
    const short getID() const;
    const Type getType() const;
    const char getSuit() const;
    const short getDigitalValue() const;
    const char getPictureValue() const;
    const double getQuality() const;

private:
    short ID;
    Type type;
    union
    {
        short digitalValue;
        char pictureValue;
    };
    char suit;
    double quality;
};