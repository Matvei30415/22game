#pragma once

#include "card.h"
#include "consoleIO.h"
#include <algorithm>

class Table
{
public:
    Table() = default;
    Table(std::vector<Card> &hand)
    {
        this->hand = hand;
    }
    std::vector<Card> &getHand();
    void sortHand();
    void addCardToHand(const Card &card);
    void removeCardFromHand(Card &card);
    void removeTrickFromHand(std::vector<Card> &trick);
    // Строго функции ввода-вывода
    void printTable();

protected:
    std::vector<Card> hand;
};
