#include "card.h"
#include <stdexcept>

// Конструктор с параметрами
Card::Card(int id, Kind kind, int value, Suit suit, double quality)
{
    this->id = id;
    this->kind = kind;
    if (kind == Card::Kind::Digital)
        this->value = value;
    this->suit = suit;
    this->quality = quality;
}

// Конструктор с параметрами
Card::Card(int id, Kind kind, Picture value, Suit suit, double quality)
{
    this->id = id;
    this->kind = kind;
    if (kind == Card::Kind::Picture)
        this->value = value;
    this->suit = suit;
    this->quality = quality;
}

// Получить ID карты
int Card::getID() const
{
    return this->id;
}

// Получить тип карты (Цифровая или Картинка)
Card::Kind Card::getKind() const
{
    return this->kind;
}

// Получить масть карты (Общая, Трефы, Буби, Черви)
Card::Suit Card::getSuit() const
{
    return this->suit;
}

// Получить значение цифровой карты (2, 4, ... , 18, 20)
int Card::getDigitalValue() const
{
    if (kind != Kind::Digital)
        throw std::logic_error("Карточка не цифровая");

    if (auto ptr = std::get_if<int>(&value)) {
        return *ptr;
    } else {
        throw std::logic_error("В карточке ожидается цифровое значение");
    }
}

// Получить значение карты-картинки (G, L, H)
Card::Picture Card::getPictureValue() const
{
    if (kind != Kind::Picture)
        throw std::logic_error("Карточка не картинка");

    if (auto ptr = std::get_if<Card::Picture>(&value)) {
        return *ptr;
    } else {
        throw std::logic_error("В карточке ожидается значение-картинка");
    }
}

// Получить ценность карты
double Card::getQuality() const
{
    return this->quality;
}