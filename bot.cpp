#include "bot.h"

// Установить наилучшую коминацию (со стола) с параметром эффективности
void BotPlayer::setMaxCombo(std::vector<Card> &combo, double quality)
{
    this->maxCombo = combo;
    this->maxComboQuality = quality;
}

// Установить карту (с руки) для наилучшей комбинации
void BotPlayer::setMaxCard(Card &card)
{
    this->maxCard = card;
}

// Получить наилучшую комбинацию
std::vector<Card> &BotPlayer::getMaxCombo()
{
    return this->maxCombo;
}

// Получить карту для наилучшей комбинации
Card &BotPlayer::getMaxCard()
{
    return this->maxCard;
}

// Получить эффективность наилучшей комбинации
double BotPlayer::getMaxComboQuality()
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
void BotPlayer::findDigitalCombo(Table &table, std::vector<Card> &combo, short n, short start)
{
    BotPlayer &bot = *this;
    std::vector<Card> &tableHand = table.getHand();
    double comboQuality = 0;
    if (n == 0)
    {
        comboQuality += selectedCard.getQuality();
        for (short i = 0; i < combo.size(); i++)
        {
            comboQuality += combo[i].getQuality();
        }
        if (comboQuality > bot.getMaxComboQuality())
        {
            bot.setMaxCombo(combo, comboQuality);
            bot.setMaxCard(selectedCard);
        }
    }

    for (short i = start; i < tableHand.size(); i++)
    {
        if (tableHand[i].getType() == Card::Digital && tableHand[i].getDigitalValue() <= n)
        {
            combo.push_back(tableHand[i]);
            if (tableHand[i].getDigitalValue() != 2)
                findDigitalCombo(table, combo, n - tableHand[i].getDigitalValue(), i + 1);
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
void BotPlayer::findPictureCombo(Table &table, std::vector<Card> &combo)
{
    BotPlayer &bot = *this;
    std::vector<Card> &tableHand = table.getHand();
    double comboQuality = 0;
    char oppositePicture = selectedCard.getPictureValue() == 'G' ? 'L' : 'G';
    for (short i = 0; i < tableHand.size(); i++)
    {
        if (tableHand[i].getType() == Card::Picture && tableHand[i].getPictureValue() == oppositePicture)
        {
            combo = {tableHand[i]};
            comboQuality = tableHand[i].getQuality() + selectedCard.getQuality();
            if (comboQuality > bot.getMaxComboQuality())
            {
                bot.setMaxCombo(combo, comboQuality);
                bot.setMaxCard(selectedCard);
            }
        }
        else if (tableHand[i].getType() == Card::Digital)
            break;
    }
}

// Расчёт ценности хода при розыгрше Хантера
void BotPlayer::findHunterCombo(Table &table, std::vector<Card> &combo)
{
    BotPlayer &bot = *this;
    std::vector<Card> &tableHand = table.getHand();
    double comboQuality = 0;
    for (short i = 0; i < tableHand.size(); i++)
    {
        if ((tableHand[i].getType() == Card::Picture && tableHand[i].getPictureValue() == 'H') ||
            (tableHand[i].getType() == Card::Digital))
        {
            comboQuality += tableHand[i].getQuality();
            combo.push_back(tableHand[i]);
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
void BotPlayer::searchTrick(Table &table)
{
    BotPlayer &bot = *this;
    std::vector<Card> combo{};
    for (short i = 0; i < hand.size(); i++)
    {
        bot.setSelectedCard(hand[i]);
        if (selectedCard.getType() == Card::Digital)
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
            if (selectedCard.getPictureValue() == 'G' || selectedCard.getPictureValue() == 'L')
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
    table.sortHand();
    BotPlayer &bot = *this;
    bot.searchTrick(table);
    // bot.printHand();
    if (bot.getMaxComboQuality() != 0)
    {
        bot.setSelectedCard(maxCard);
        bot.setSelectedTrick(maxCombo);
        bot.printMove();
        if (selectedCard.getType() == Card::Picture && selectedCard.getPictureValue() == 'H')
        {
            bot.makeHunterMove(table);
        }
        else
        {
            bot.addCardToTricks(selectedCard);
            bot.removeCardFromHand(selectedCard);
            bot.addTrickToTricks(maxCombo);
            table.removeTrickFromHand(maxCombo);
            bot.setIsTrick(true);
        }
    }
    else
    {
        bot.setSelectedCard(hand[rand() % hand.size()]);
        bot.printSelectedCard();
        if (selectedCard.getType() == Card::Picture && selectedCard.getPictureValue() == 'H')
        {
            bot.makeHunterMove(table);
        }
        else
        {
            table.addCardToHand(selectedCard);
            bot.removeCardFromHand(selectedCard);
            bot.setIsTrick(false);
        }
    }
    bot.clearSelectedTrick();
    bot.clearMaxCombo();
}

// СТРОГО ФУНКЦИИ ВВОДА-ВЫВОДА

// Печать анонса хода
void BotPlayer::printAnnouncement()
{
    printLine();
    std::cout << "Ход бота " << std::to_string(ID) << std::endl;
    printLine();
}

// Печать руки
void BotPlayer::printHand()
{
    printLine();
    std::cout << "Карты бота: " << std::endl;
    printCardList(hand);
}

// Печать взяток
void BotPlayer::printTricks()
{
    printLine();
    std::cout << "Взятки бота " << std::endl;
    printLine();
    printCardList(tricks);
}