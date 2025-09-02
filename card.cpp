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
short Card::getID()
{
    return this->ID;
}

// Получить тип карты (Цифровая или Картинка)
Card::Type Card::getType()
{
    return this->type;
}

// Получить масть карты (Общая, Трефы, Буби, Черви)
char Card::getSuit()
{
    return this->suit;
}

// Получить значение цифровой карты (2, 4, ... , 18, 20)
short Card::getDigitalValue()
{
    return this->digitalValue;
}

// Получить значение карты-картинки (G, L, H)
char Card::getPictureValue()
{
    return this->pictureValue;
}

// Получить ценность карты
double Card::getQuality()
{
    return this->quality;
}