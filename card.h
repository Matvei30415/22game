#pragma once

class Card
{
public:
    enum Type
    {
        Digital,
        Picture
    };
    Card() = default;
    Card(short id, Type type, short digitalValue, char pictureValue, char suit, double quality);
    short getID();
    Type getType();
    char getSuit();
    short getDigitalValue();
    char getPictureValue();
    double getQuality();

private:
    short id;
    Type type;
    union
    {
        short digitalValue;
        char pictureValue;
    };
    char suit;
    double quality;
};