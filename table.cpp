#include "table.h"

std::size_t Table::getTableSize() const
{
    return (this->cardsOnTable).size();
}

// Получить карту с руки по индексу
const Card &Table::getCardOnTable(const std::size_t index) const
{
    return (this->cardsOnTable)[index];
}

// Получить руку
const std::vector<Card> &Table::getCardsOnTable() const
{
    return this->cardsOnTable;
}

// Сортировка стола
void Table::sortCardsOnTable()
{
    std::vector<Card> &cards = this->cardsOnTable;
    std::size_t countPictureCards = 0;
    Card tmp;
    for (std::size_t i = 0; i < cards.size(); i++)
    {
        if (cards[i].getKind() == Card::CardKind::Picture)
        {
            tmp = cards[i];
            cards.erase(cards.cbegin() + i);
            cards.insert(cards.cbegin(), tmp);
            countPictureCards++;
            continue;
        }
        for (std::size_t j = i + 1; j < cards.size(); j++)
        {
            if ((cards[i].getKind() == Card::CardKind::Digital && cards[j].getKind() == Card::CardKind::Digital) &&
                ((cards[i].getDigitalValue() > cards[j].getDigitalValue()) ||
                 ((cards[i].getDigitalValue() == cards[j].getDigitalValue()) &&
                  (cards[i].getSuit() != Card::Suit::General && cards[j].getSuit() == Card::Suit::General))))
            {
                std::swap(cards[i], cards[j]);
            }
        }
    }
    for (std::size_t i = 0; i < countPictureCards; i++)
    {
        for (std::size_t j = i + 1; j < countPictureCards; j++)
        {
            if ((cards[i].getPictureValue() == Card::Picture::Lady &&
                 cards[j].getPictureValue() == Card::Picture::Gentleman) ||
                (cards[i].getPictureValue() == Card::Picture::Hunter) ||
                ((cards[i].getPictureValue() == cards[j].getPictureValue()) &&
                 (cards[i].getSuit() != Card::Suit::General && cards[j].getSuit() == Card::Suit::General)))
            {
                std::swap(cards[i], cards[j]);
            }
        }
    }
}

// Добавить карту на руку
void Table::addCardToTable(const Card &card)
{
    (this->cardsOnTable).push_back(card);
}

// Удалить карту с руки
void Table::removeCardFromTable(const Card &card)
{
    auto it = std::find_if(cardsOnTable.begin(), cardsOnTable.end(),
                           [&card](Card &c)
                           { return c.getID() == card.getID(); });
    if (it != cardsOnTable.end())
        cardsOnTable.erase(it);
}

// Удалить взятку с руки
void Table::removeTrickFromTable(const std::vector<Card> &cards)
{
    std::vector<Card> &cardsOnTable = this->cardsOnTable;
    for (std::size_t i = 0; i < cards.size(); i++)
        for (std::size_t j = 0; j < cardsOnTable.size(); j++)
            if (cards[i].getID() == cardsOnTable[j].getID())
            {
                this->removeCardFromTable(cardsOnTable[j]);
            }
}

// СТРОГО ФУНКЦИИ ВВОДА-ВЫВОДА

// Печать карт на столе
void Table::printTable() const
{
    if (cardsOnTable.size() == 0)
    {
        std::cout << "Стол пуст!" << std::endl;
        return;
    }
    else
    {
        std::cout << "Карты на столе: " << std::endl;
    }
    printCardList(cardsOnTable);
}