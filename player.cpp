#include "player.h"

// Конструктор класса с параметром
Player::Player(short id)
{
    this->id = id;
    this->isTrick = false;
    (this->results).moreCards =
        (this->results).moreClubs =
            (this->results).twentyOfDiamonds =
                (this->results).aceOfHearts = 0;
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

short Player::getID() const
{
    return this->id;
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
bool Player::getIsTrick() const
{
    return this->isTrick;
}

// Сортировка стола
void Player::sortHand()
{
    std::vector<Card> &cards = this->hand;
    std::size_t countPictureCards = 0;
    Card tmp;
    for (std::size_t i = 0; i < cards.size(); i++)
    {
        if (cards[i].getKind() == Card::Kind::Picture)
        {
            tmp = cards[i];
            cards.erase(cards.cbegin() + i);
            cards.insert(cards.cbegin(), tmp);
            countPictureCards++;
            continue;
        }
        for (std::size_t j = i + 1; j < cards.size(); j++)
        {
            if ((cards[i].getKind() == Card::Kind::Digital && cards[j].getKind() == Card::Kind::Digital) &&
                ((cards[i].getDigitalValue() > cards[j].getDigitalValue()) ||
                 ((cards[i].getDigitalValue() == cards[j].getDigitalValue()) &&
                  (cards[i].getSuit() != Card::Suit::General &&
                   cards[j].getSuit() == Card::Suit::General))))
            {
                std::swap(cards[i], cards[j]);
            }
        }
    }
    for (std::size_t i = 0; i < countPictureCards; i++)
    {
        for (std::size_t j = i + 1; j < countPictureCards; j++)
        {
            if ((cards[i].getPictureValue() == Card::Picture::Lady &&
                 cards[j].getPictureValue() == Card::Picture::Gentleman) ||
                (cards[i].getPictureValue() == Card::Picture::Hunter) ||
                ((cards[i].getPictureValue() == cards[j].getPictureValue()) &&
                 (cards[i].getSuit() != Card::Suit::General &&
                  cards[j].getSuit() == Card::Suit::General)))
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

void Player::addCardToSelectedTrick(const Card &card)
{
    (this->selectedTrick).push_back(card);
}

// Добавить выбранную взятку (со стола) во взятки
void Player::addTrickToTricks(const std::vector<Card> &cards)
{
    for (std::size_t i = 0; i < cards.size(); i++)
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
    for (std::size_t i = 0; i < trick.size(); i++)
        for (std::size_t j = 0; j < hand.size(); j++)
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
    std::size_t countErase = 0;
    Player &player = (*this);
    player.setIsTrick(false);
    for (std::size_t i = 0; i < table.getTableSize(); i++)
    {
        // Проверяем, что карта не Gentleman или Lady
        if (!(table.getCardOnTable(i).getKind() == Card::Kind::Picture &&
              (table.getCardOnTable(i).getPictureValue() == Card::Picture::Gentleman ||
               table.getCardOnTable(i).getPictureValue() == Card::Picture::Lady)))
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
void Player::calculatePoints()
{
    std::size_t len = tricks.size();
    if (len > 24)
        (this->results).moreCards += 2;
    else if (len == 24)
        (this->results).moreCards += 1;
    short sumClubs = 0;
    for (std::size_t i = 0; i < len; i++)
    {
        if (tricks[i].getSuit() == Card::Suit::Clubs)
            sumClubs += 1;
        if (tricks[i].getKind() == Card::Kind::Digital)
        {
            if (tricks[i].getDigitalValue() == 20 && tricks[i].getSuit() == Card::Suit::Diamonds)
                (this->results).twentyOfDiamonds += 1;
            else if (tricks[i].getDigitalValue() == 2 && tricks[i].getSuit() == Card::Suit::Hearts)
                (this->results).aceOfHearts += 1;
        }
    }
    if (sumClubs > 5)
        (this->results).moreClubs += 1;
}

// Получить результаты
void Player::getPoints(short &moreCards, short &moreClubs, short &twentyOfDiamonds, short &aceOfHearts) const
{
    moreCards = (this->results).moreCards;
    moreClubs = (this->results).moreClubs;
    twentyOfDiamonds = (this->results).twentyOfDiamonds;
    aceOfHearts = (this->results).aceOfHearts;
}