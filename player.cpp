#include "player.h"

Player::Player(std::string name)
{
    this->name = name;
    this->isTrick = false;
}

void Player::setSelectedCard(const Card &card)
{
    this->selectedCard = card;
}

std::vector<Card> &Player::getHand()
{
    return this->hand;
}

void Player::setIsTrick(bool isTrick)
{
    this->isTrick = isTrick;
}

std::vector<Card> &Player::getTricks()
{
    return this->tricks;
}

Card &Player::getSelectedCard()
{
    return this->selectedCard;
}

std::vector<Card> &Player::getSelectedTrick()
{
    return this->selectedTrick;
}

bool Player::getIsTrick()
{
    return this->isTrick;
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

void Player::removeCardFromHand(Card &card)
{
    auto it = std::find_if(hand.begin(), hand.end(),
                           [&card](Card &c)
                           { return c.getID() == card.getID(); });
    if (it != hand.end())
        hand.erase(it);
}

void Player::removeTrickFromHand(std::vector<Card> &trick)
{
    std::vector<Card> &hand = this->hand;
    for (short i = 0; i < trick.size(); i++)
        for (short j = 0; j < hand.size(); j++)
            if (trick[i].getID() == hand[j].getID())
            {
                this->removeCardFromHand(hand[j]);
            }
}

void Player::addCardToTricks(const Card &card)
{
    (this->tricks).push_back(card);
}

void Player::addTrickToTricks(const std::vector<Card> &trick)
{
    for (short i = 0; i < trick.size(); i++)
    {
        (this->tricks).push_back(trick[i]);
    }
}

void Player::clearSelectedTrick()
{
    (this->selectedTrick).clear();
}

// Обработка механизма карты Hunter
void Player::makeHunterMove(Player &table)
{
    short count_erase = 0;
    Player &player = (*this);
    std::vector<Card> &tableHand = table.getHand();
    Card &selectedCard = player.getSelectedCard();
    player.setIsTrick(false);
    for (short i = 0; i < tableHand.size(); i++)
    {
        // Проверяем, что карта не Gentleman или Lady
        if (!(tableHand[i].getType() == Card::Picture && (tableHand[i].getPictureValue() == 'G' || tableHand[i].getPictureValue() == 'L')))
        {
            player.addCardToTricks(tableHand[i]);
            table.removeCardFromHand(tableHand[i]);
            count_erase++;
            i--;
        }
    }
    // Остаётся на столе, если не взял ни одной числовой карты или Hunter'a
    if (count_erase == 0)
    {
        table.addCardToHand(selectedCard);
        player.removeCardFromHand(selectedCard);
    }
    // Отправляется во взятки, если взял хотя бы одну числовую карту или Hunter'а
    else
    {
        player.setIsTrick(true);
        player.addCardToTricks(selectedCard);
        player.removeCardFromHand(selectedCard);
    }
}