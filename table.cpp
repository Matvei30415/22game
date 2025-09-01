#include "table.h"

std::vector<Card> &Table::getHand()
{
    return this->hand;
}

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

void Table::addCardToHand(const Card &card)
{
    (this->hand).push_back(card);
}

void Table::removeCardFromHand(Card &card)
{
    auto it = std::find_if(hand.begin(), hand.end(),
                           [&card](Card &c)
                           { return c.getID() == card.getID(); });
    if (it != hand.end())
        hand.erase(it);
}

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