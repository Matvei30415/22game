#include "player.h"

Player::Player(std::string &name)
{
    this->name = name;
    this->is_trick = false;
}

CardList &Player::getHand()
{
    return this->hand;
}

CardList &Player::getTricks()
{
    return this->tricks;
}

bool Player::getIsTrick()
{
    return this->is_trick;
}

void Player::setHand(CardList &src)
{
    this->hand = src;
}

void Player::sortHand()
{
    this->hand.sort();
}

void Player::addCardToHand(const Card &card)
{
    (this->hand).add(card);
}

void Player::removeCardFromHand(short index)
{
    (this->hand).remove(index);
}

void Player::addCardToTrick(const Card &card)
{
    (this->tricks).add(card);
}

void Player::addTrick(const CardList &trick)
{
    for (short i = 0; i < trick.size(); i++)
    {
        (this->tricks).add(trick[i]);
    }
}