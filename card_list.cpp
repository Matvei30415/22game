#include "card_list.h"

CardList::CardList(short size)
{
    this->cards.resize(size);
}

void CardList::add(const Card &card)
{
    cards.push_back(card);
}

void CardList::remove(size_t index)
{
    cards.erase(cards.begin() + index);
}

void CardList::pop()
{
    cards.pop_back();
}

short CardList::size()
{
    return cards.size();
}

const short CardList::size() const
{
    return cards.size();
}

void CardList::clear()
{
    cards.clear();
}

std::vector<Card> &CardList::data()
{
    return cards;
}

Card &CardList::operator[](size_t index)
{
    return cards[index];
}

const Card &CardList::operator[](size_t index) const
{
    return cards[index];
}

// Перемещение карты из src в dst, с последующим удалением в src
void CardList::moveCardTo(CardList &dst, short index)
{
    dst.add(cards[index]);
    this->remove(index);
}

// Копирование карты из src в dst, без последующего удаления в src
void CardList::copyCardTo(CardList &dst, short index)
{
    dst.add(cards[index]);
}

// Сортировка текущих карт на столе
void CardList::sort()
{
    
}