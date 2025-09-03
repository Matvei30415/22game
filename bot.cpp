#include "bot.h"

// Установить наилучшую коминацию (со стола) с параметром эффективности
void BotPlayer::setMaxCombo(const std::vector<Card> &combo, const double quality)
{
    this->maxCombo = combo;
    this->maxComboQuality = quality;
}

// Установить карту (с руки) для наилучшей комбинации
void BotPlayer::setMaxCard(const Card &card)
{
    this->maxCard = card;
}

// Получить наилучшую комбинацию
const std::vector<Card> &BotPlayer::getMaxCombo() const
{
    return this->maxCombo;
}

// Получить карту для наилучшей комбинации
const Card &BotPlayer::getMaxCard() const
{
    return this->maxCard;
}

// Получить эффективность наилучшей комбинации
double BotPlayer::getMaxComboQuality() const
{
    return this->maxComboQuality;
}

// Очистка наилучшей комбинации и параметра эффективности
void BotPlayer::clearMaxCombo()
{
    (this->maxCombo).clear();
    this->maxComboQuality = 0;
}

// Нахождение комбинации с цифровыми картами
void BotPlayer::findDigitalCombo(const Table &table, std::vector<Card> &combo, short n, std::size_t start)
{
    BotPlayer &bot = *this;
    double comboQuality = 0;
    if (n == 0)
    {
        comboQuality += selectedCard.getQuality();
        for (std::size_t i = 0; i < combo.size(); i++)
        {
            comboQuality += combo[i].getQuality();
        }
        if (comboQuality > bot.getMaxComboQuality())
        {
            bot.setMaxCombo(combo, comboQuality);
            bot.setMaxCard(selectedCard);
        }
    }

    for (std::size_t i = start; i < table.getTableSize(); i++)
    {
        if (table.getCardOnTable(i).getKind() == Card::CardKind::Digital &&
            table.getCardOnTable(i).getDigitalValue() <= n)
        {
            combo.push_back(table.getCardOnTable(i));
            if (table.getCardOnTable(i).getDigitalValue() != 2)
                findDigitalCombo(table, combo, n - table.getCardOnTable(i).getDigitalValue(), i + 1);
            else
            {
                findDigitalCombo(table, combo, n - 2, i + 1);
                findDigitalCombo(table, combo, n - 11, i + 1);
            }
            combo.pop_back();
        }
    }
}

// Нахождение комбинации с лицами
void BotPlayer::findPictureCombo(const Table &table, std::vector<Card> &combo)
{
    BotPlayer &bot = *this;
    double comboQuality = 0;
    Card::Picture oppositePicture = selectedCard.getPictureValue() == Card::Picture::Gentleman ? Card::Picture::Lady : Card::Picture::Gentleman;
    for (std::size_t i = 0; i < table.getTableSize(); i++)
    {
        if (table.getCardOnTable(i).getKind() == Card::CardKind::Picture &&
            table.getCardOnTable(i).getPictureValue() == oppositePicture)
        {
            combo = {table.getCardOnTable(i)};
            comboQuality = table.getCardOnTable(i).getQuality() + selectedCard.getQuality();
            if (comboQuality > bot.getMaxComboQuality())
            {
                bot.setMaxCombo(combo, comboQuality);
                bot.setMaxCard(selectedCard);
            }
        }
        else if (table.getCardOnTable(i).getKind() == Card::CardKind::Digital)
            break;
    }
}

// Расчёт ценности хода при розыгрше Хантера
void BotPlayer::findHunterCombo(const Table &table, std::vector<Card> &combo)
{
    BotPlayer &bot = *this;
    double comboQuality = 0;
    for (std::size_t i = 0; i < table.getTableSize(); i++)
    {
        if ((table.getCardOnTable(i).getKind() == Card::CardKind::Picture &&
             table.getCardOnTable(i).getPictureValue() == Card::Picture::Hunter) ||
            (table.getCardOnTable(i).getKind() == Card::CardKind::Digital))
        {
            comboQuality += table.getCardOnTable(i).getQuality();
            combo.push_back(table.getCardOnTable(i));
        }
    }
    // Закомментировано из-за неэффективности использования карты Hunter ботом
    // if (comboQuality != 0)
    //     comboQuality += selectedCard.getQuality();
    if (comboQuality > bot.getMaxComboQuality())
    {
        bot.setMaxCombo(combo, comboQuality);
        bot.setMaxCard(selectedCard);
    }
}

// Нахождение самого выгодного хода для бота
void BotPlayer::searchTrick(const Table &table)
{
    BotPlayer &bot = *this;
    std::vector<Card> combo{};
    for (std::size_t i = 0; i < hand.size(); i++)
    {
        bot.setSelectedCard(hand[i]);
        if (selectedCard.getKind() == Card::CardKind::Digital)
        {

            if (selectedCard.getDigitalValue() != 2)
                bot.findDigitalCombo(table, combo, 22 - selectedCard.getDigitalValue());
            else
            {
                bot.findDigitalCombo(table, combo, 22 - 2);
                combo.clear();
                findDigitalCombo(table, combo, 22 - 11);
            }
        }
        else
        {
            if (selectedCard.getPictureValue() == Card::Picture::Gentleman ||
                selectedCard.getPictureValue() == Card::Picture::Lady)
            {
                bot.findPictureCombo(table, combo);
            }
            else
            {
                bot.findHunterCombo(table, combo);
            }
        }
        combo.clear();
    }
}

// Ход бота
void BotPlayer::makeMove(Table &table, GameMode mode)
{
    table.sortCardsOnTable();
    BotPlayer &bot = *this;
    bot.searchTrick(table);
    // bot.printHand();
    if (bot.getMaxComboQuality() != 0)
    {
        bot.setSelectedCard(maxCard);
        bot.setSelectedTrick(maxCombo);
        bot.printMove();
        if (selectedCard.getKind() == Card::CardKind::Picture &&
            selectedCard.getPictureValue() == Card::Picture::Hunter)
        {
            bot.makeHunterMove(table);
        }
        else
        {
            bot.addCardToTricks(selectedCard);
            bot.removeCardFromHand(selectedCard);
            bot.addTrickToTricks(maxCombo);
            table.removeTrickFromTable(maxCombo);
            bot.setIsTrick(true);
        }
    }
    else
    {
        bot.setSelectedCard(hand[rand() % hand.size()]);
        bot.clearSelectedTrick();
        bot.printMove();
        if (selectedCard.getKind() == Card::CardKind::Picture &&
            selectedCard.getPictureValue() == Card::Picture::Hunter)
        {
            bot.makeHunterMove(table);
        }
        else
        {
            table.addCardToTable(selectedCard);
            bot.removeCardFromHand(selectedCard);
            bot.setIsTrick(false);
        }
    }
    bot.clearSelectedTrick();
    bot.clearMaxCombo();
}

// СТРОГО ФУНКЦИИ ВВОДА-ВЫВОДА

// Печать анонса хода
void BotPlayer::printAnnouncement() const
{
    printLine();
    std::cout << "Ход бота " << std::to_string(id) << std::endl;
    printLine();
}

// Печать руки
void BotPlayer::printHand() const
{
    printLine();
    std::cout << "Карты бота: " << std::endl;
    printCardList(hand);
}

// Печать взяток
void BotPlayer::printTricks() const
{
    printLine();
    std::cout << "Взятки бота " << std::endl;
    printLine();
    printCardList(tricks);
}