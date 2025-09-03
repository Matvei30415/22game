#include "card.h"

// Конструктор с параметрами
Card::Card(short ID, Type type, short digitalValue, char pictureValue, char suit, double quality)
{
    this->ID = ID;
    this->type = type;
    if (type == Card::Digital)
        this->digitalValue = digitalValue;
    else
        this->pictureValue = pictureValue;
    this->suit = suit;
    this->quality = quality;
}

// Получить ID карты
const short Card::getID() const
{
    return this->ID;
}

// Получить тип карты (Цифровая или Картинка)
const Card::Type Card::getType() const
{
    return this->type;
}

// Получить масть карты (Общая, Трефы, Буби, Черви)
const char Card::getSuit() const
{
    return this->suit;
}

// Получить значение цифровой карты (2, 4, ... , 18, 20)
const short Card::getDigitalValue() const
{
    return this->digitalValue;
}

// Получить значение карты-картинки (G, L, H)
const char Card::getPictureValue() const
{
    return this->pictureValue;
}

// Получить ценность карты
const double Card::getQuality() const
{
    return this->quality;
}