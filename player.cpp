#include "player.h"

// Конструктор класса с параметром
Player::Player(short ID)
{
    this->ID = ID;
    this->isTrick = false;
    (this->results).moreCards = '\0';
    (this->results).moreClubs =
        (this->results).twentyOfDiamonds =
            (this->results).aceOfHearts = false;
}

// Установить выбранную карту (с руки)
void Player::setSelectedCard(const Card &card)
{
    this->selectedCard = card;
}

// Установить выбранную взятку (со стола)
void Player::setSelectedTrick(const std::vector<Card> &cards)
{
    this->selectedTrick = cards;
}

// Установить параметр Был ли ход взяткой
void Player::setIsTrick(const bool isTrick)
{
    this->isTrick = isTrick;
}

// Получить руку
const std::vector<Card> &Player::getHand() const
{
    return this->hand;
}

// Получить взятки
const std::vector<Card> &Player::getTricks() const
{
    return this->tricks;
}

// Получить выбранную карту (с руки)
const Card &Player::getSelectedCard() const
{
    return this->selectedCard;
}

// Получить выбранную взятку (со стола)
const std::vector<Card> &Player::getSelectedTrick() const
{
    return this->selectedTrick;
}

// Получить параметр Был ли ход взяткой
const bool Player::getIsTrick() const
{
    return this->isTrick;
}

// Сортировка стола
void Player::sortHand()
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

// Добавить карту на руку
void Player::addCardToHand(const Card &card)
{
    (this->hand).push_back(card);
}

// Добавить карту во взятки
void Player::addCardToTricks(const Card &card)
{
    (this->tricks).push_back(card);
}

// Добавить выбранную взятку (со стола) во взятки
void Player::addTrickToTricks(const std::vector<Card> &cards)
{
    for (short i = 0; i < cards.size(); i++)
    {
        (this->tricks).push_back(cards[i]);
    }
}

// Удалить карту с руки
void Player::removeCardFromHand(const Card &card)
{
    auto it = std::find_if(hand.begin(), hand.end(),
                           [&card](Card &c)
                           { return c.getID() == card.getID(); });
    if (it != hand.end())
        hand.erase(it);
}

// Удалить взятку с руки
void Player::removeTrickFromHand(const std::vector<Card> &trick)
{
    std::vector<Card> &hand = this->hand;
    for (short i = 0; i < trick.size(); i++)
        for (short j = 0; j < hand.size(); j++)
            if (trick[i].getID() == hand[j].getID())
            {
                this->removeCardFromHand(hand[j]);
            }
}

// Очистить выбранную взятку (со стола)
void Player::clearSelectedTrick()
{
    (this->selectedTrick).clear();
}

// Обработка механизма карты Hunter
void Player::makeHunterMove(Table &table)
{
    short countErase = 0;
    Player &player = (*this);
    player.setIsTrick(false);
    for (short i = 0; i < table.getTableSize(); i++)
    {
        // Проверяем, что карта не Gentleman или Lady
        if (!(table.getCardOnTable(i).getType() == Card::Picture &&
              (table.getCardOnTable(i).getPictureValue() == 'G' || table.getCardOnTable(i).getPictureValue() == 'L')))
        {
            player.addCardToTricks(table.getCardOnTable(i));
            table.removeCardFromTable(table.getCardOnTable(i));
            countErase++;
            i--;
        }
    }
    // Остаётся на столе, если не взял ни одной числовой карты или Hunter'a
    if (countErase == 0)
    {
        table.addCardToTable(selectedCard);
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

// Вычислить победные очков в конце партии
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

// Получить результаты
void Player::getPoints(char &moreCards, bool &moreClubs, bool &twentyOfDiamonds, bool &aceOfHearts)
{
    moreCards = (this->results).moreCards;
    moreClubs = (this->results).moreClubs;
    twentyOfDiamonds = (this->results).twentyOfDiamonds;
    aceOfHearts = (this->results).aceOfHearts;
}

// СТРОГО ФУНКЦИИ ВВОДА-ВЫВОДА

// Печать выбранной карты
void Player::printSelectedCard() const
{
    printCard(selectedCard);
}

// Печать хода
void Player::printMove() const
{
    short size = selectedTrick.size();
    printSelectedCard();
    if (size != 0)
        printCardList(selectedTrick);
}