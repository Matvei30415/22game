#pragma once

#include "card.h"
#include <algorithm>

class Table
{
public:
    Table() = default;
    Table(const std::vector<Card> &cardsOnTable)
    {
        this->cardsOnTable = cardsOnTable;
    }
    std::size_t getTableSize() const;
    const Card &getCardOnTable(const std::size_t index) const;
    const std::vector<Card> &getCardsOnTable() const;
    void sortCardsOnTable();
    void addCardToTable(const Card &card);
    void removeCardFromTable(const Card &card);
    void removeTrickFromTable(const std::vector<Card> &cards);

private:
    std::vector<Card> cardsOnTable;
};
