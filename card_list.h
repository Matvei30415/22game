#pragma once

#include <vector>
#include "card.h"

class CardList
{
public:
    CardList() = default;
    CardList(short size);
    ~CardList() = default;

    void add(const Card &card);
    void remove(size_t index);
    void pop();
    Card &operator[](size_t index);
    const Card &operator[](size_t index) const;
    short size();
    const short size() const;
    void clear();

    std::vector<Card> &data();

    void moveCardTo(CardList &dst, short index = 0);
    void copyCardTo(CardList &dst, short index = 0);
    void sort();

private:
    std::vector<Card> cards;
};