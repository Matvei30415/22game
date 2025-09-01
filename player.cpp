#include "player.h"

Player::Player(short ID)
{
    this->ID = ID;
    this->isTrick = false;
    (this->results).moreCards = '\0';
    (this->results).moreClubs =
        (this->results).twentyOfDiamonds =
            (this->results).aceOfHearts = false;
}

void Player::setSelectedCard(const Card &card)
{
    this->selectedCard = card;
}

void Player::setSelectedTrick(const std::vector<Card> &cards)
{
    this->selectedTrick = cards;
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
void Player::makeHunterMove(Table &table)
{
    short countErase = 0;
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
            countErase++;
            i--;
        }
    }
    // Остаётся на столе, если не взял ни одной числовой карты или Hunter'a
    if (countErase == 0)
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

// Вычисление очков в конце партии
void Player::сalculatePoints()
{
    short len = tricks.size();
    if (len > 24)
        (this->results).moreCards = 2;
    else if (len == 24)
        (this->results).moreCards = 1;
    short sumClubs = 0;
    for (short i = 0; i < len; i++)
    {
        if (tricks[i].getSuit() == 'C')
            sumClubs += 1;
        if (tricks[i].getDigitalValue() == 20 && tricks[i].getSuit() == 'D')
            (this->results).twentyOfDiamonds = true;
        else if (tricks[i].getDigitalValue() == 2 && tricks[i].getSuit() == 'H')
            (this->results).aceOfHearts = true;
    }
    if (sumClubs > 5)
        (this->results).moreClubs = true;
}

// Геттер результатов
void Player::getPoints(char &moreCards, bool &moreClubs, bool &twentyOfDiamonds, bool &aceOfHearts)
{
    moreCards = (this->results).moreCards;
    moreClubs = (this->results).moreClubs;
    twentyOfDiamonds = (this->results).twentyOfDiamonds;
    aceOfHearts = (this->results).aceOfHearts;
}

// СТРОГО ФУНКЦИИ ВВОДА-ВЫВОДА

// Печать выбранной карты
void Player::printSelectedCard()
{
    printCard(selectedCard);
}

// Печать хода
void Player::printMove()
{
    short size = selectedTrick.size();
    printSelectedCard();
    if (size != 0)
        printCardList(selectedTrick);
}