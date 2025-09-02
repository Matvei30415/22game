#include "table.h"

// Получить руку
std::vector<Card> &Table::getHand()
{
    return this->hand;
}

// Сортировка стола
void Table::sortHand()
{
    std::vector<Card> &cards = this->hand;
    short countPictureCards = 0;
    Card tmp;
    for (short i = 0; i < cards.size(); i++)
    {
        if (cards[i].getType() == Card::Picture)
        {
            tmp = cards[i];
            cards.erase(cards.cbegin() + i);
            cards.insert(cards.cbegin(), tmp);
            countPictureCards++;
            continue;
        }
        for (short j = i + 1; j < cards.size(); j++)
        {
            if ((cards[i].getType() == Card::Digital && cards[j].getType() == Card::Digital) &&
                ((cards[i].getDigitalValue() > cards[j].getDigitalValue()) ||
                 ((cards[i].getDigitalValue() == cards[j].getDigitalValue()) &&
                  (cards[i].getSuit() != 'G' && cards[j].getSuit() == 'G'))))
            {
                std::swap(cards[i], cards[j]);
            }
        }
    }
    for (short i = 0; i < countPictureCards; i++)
    {
        for (short j = i + 1; j < countPictureCards; j++)
        {
            if ((cards[i].getPictureValue() == 'L' && cards[j].getPictureValue() == 'G') ||
                (cards[i].getPictureValue() == 'H') ||
                ((cards[i].getPictureValue() == cards[j].getPictureValue()) &&
                 (cards[i].getSuit() != 'G' && cards[j].getSuit() == 'G')))
            {
                std::swap(cards[i], cards[j]);
            }
        }
    }
}

// Добавить карту на руку
void Table::addCardToHand(const Card &card)
{
    (this->hand).push_back(card);
}

// Удалить карту с руки
void Table::removeCardFromHand(Card &card)
{
    auto it = std::find_if(hand.begin(), hand.end(),
                           [&card](Card &c)
                           { return c.getID() == card.getID(); });
    if (it != hand.end())
        hand.erase(it);
}

// Удалить взятку с руки
void Table::removeTrickFromHand(std::vector<Card> &trick)
{
    std::vector<Card> &hand = this->hand;
    for (short i = 0; i < trick.size(); i++)
        for (short j = 0; j < hand.size(); j++)
            if (trick[i].getID() == hand[j].getID())
            {
                this->removeCardFromHand(hand[j]);
            }
}

// СТРОГО ФУНКЦИИ ВВОДА-ВЫВОДА

// Печать карт на столе
void Table::printTable()
{
    if (hand.size() == 0)
    {
        std::cout << "Стол пуст!" << std::endl;
        return;
    }
    else
    {
        std::cout << "Карты на столе: " << std::endl;
    }
    printCardList(hand);
}