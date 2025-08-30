#include "player.h"

Player::Player(std::string &name)
{
    this->name = name;
    this->is_trick = false;
}

std::vector<Card> &Player::getHand()
{
    return this->hand;
}

std::vector<Card> &Player::getTricks()
{
    return this->tricks;
}

bool Player::getIsTrick()
{
    return this->is_trick;
}

void Player::sortHand()
{
    std::vector<Card> &cards = this->hand;
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

void Player::addCardToHand(const Card &card)
{
    (this->hand).push_back(card);
}

void Player::removeCardFromHand(short index)
{
    (this->hand).erase((this->hand).begin() + index);
}

void Player::addCardToTrick(const Card &card)
{
    (this->tricks).push_back(card);
}

void Player::addTrick(const std::vector<Card> &trick)
{
    for (short i = 0; i < trick.size(); i++)
    {
        (this->tricks).push_back(trick[i]);
    }
}