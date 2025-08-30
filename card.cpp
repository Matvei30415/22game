#include "card.h"

Card::Card(short id, Type type, short digitalValue, char pictureValue, char suit, double quality)
{
    this->id = id;
    this->type = type;
    if (type == Card::Digital)
        this->digitalValue = digitalValue;
    else
        this->pictureValue = pictureValue;
    this->suit = suit;
    this->quality = quality;
}

short Card::getID()
{
    return this->id;
}

Card::Type Card::getType()
{
    return this->type;
}

char Card::getSuit()
{
    return this->suit;
}

short Card::getDigitalValue()
{
    return this->digitalValue;
}

char Card::getPictureValue()
{
    return this->pictureValue;
}

double Card::getQuality()
{
    return this->quality;
}