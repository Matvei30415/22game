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
    short count_picture_cards = 0;
    Card tmp;
    for (short idx_i = 0; idx_i < cards.size(); idx_i++)
    {
        if (cards[idx_i].getType() == Card::Picture)
        {
            tmp = cards[idx_i];
            cards.erase(cards.cbegin() + idx_i);
            cards.insert(cards.cbegin(), tmp);
            count_picture_cards++;
            continue;
        }
        for (short idx_j = idx_i + 1; idx_j < cards.size(); idx_j++)
        {
            if ((cards[idx_i].getType() == Card::Digital && cards[idx_j].getType() == Card::Digital) &&
                ((cards[idx_i].getDigitalValue() > cards[idx_j].getDigitalValue()) ||
                 ((cards[idx_i].getDigitalValue() == cards[idx_j].getDigitalValue()) &&
                  (cards[idx_i].getSuit() != 'G' && cards[idx_j].getSuit() == 'G'))))
            {
                std::swap(cards[idx_i], cards[idx_j]);
            }
        }
    }
    for (short idx_i = 0; idx_i < count_picture_cards; idx_i++)
    {
        for (short idx_j = idx_i + 1; idx_j < count_picture_cards; idx_j++)
        {
            if ((cards[idx_i].getPictureValue() == 'L' && cards[idx_j].getPictureValue() == 'G') ||
                (cards[idx_i].getPictureValue() == 'H') ||
                ((cards[idx_i].getPictureValue() == cards[idx_j].getPictureValue()) &&
                 (cards[idx_i].getSuit() != 'G' && cards[idx_j].getSuit() == 'G')))
            {
                std::swap(cards[idx_i], cards[idx_j]);
            }
        }
    }
}