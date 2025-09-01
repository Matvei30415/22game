#pragma once

#include "card.h"
#include <algorithm>
#include <iostream>

class Table
{
public:
    Table() = default;
    std::vector<Card> &getHand();
    void sortHand();
    void addCardToHand(const Card &card);
    void removeCardFromHand(Card &card);
    void removeTrickFromHand(std::vector<Card> &trick);

protected:
    std::vector<Card> hand;
};
