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

// Очистка статистики бота
void BotPlayer::clearComboNumber()
{
    this->statistics.comboNumber = 0;
}

// Оставшихся в колоде карт в памяти бота
void BotPlayer::clearModifiedDeck()
{
    (this->modifiedDeck).clear();
}

// Нахождение комбинации с цифровыми картами
void BotPlayer::findDigitalCombo(const std::vector<Card> &mainHand, std::vector<Card> &combo, short n, std::size_t start)
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
        bot.statistics.comboNumber += 1;
        if (comboQuality > bot.getMaxComboQuality())
        {
            bot.setMaxCombo(combo, comboQuality);
            bot.setMaxCard(selectedCard);
        }
    }

    for (std::size_t i = start; i < mainHand.size(); i++)
    {
        if (mainHand[i].getKind() == Card::Kind::Digital &&
            mainHand[i].getDigitalValue() <= n)
        {
            combo.push_back(mainHand[i]);
            if (mainHand[i].getDigitalValue() != 2)
                findDigitalCombo(mainHand, combo, n - mainHand[i].getDigitalValue(), i + 1);
            else
            {
                findDigitalCombo(mainHand, combo, n - 2, i + 1);
                findDigitalCombo(mainHand, combo, n - 11, i + 1);
            }
            combo.pop_back();
        }
    }
}

// Нахождение комбинации с лицами
void BotPlayer::findPictureCombo(const std::vector<Card> &mainHand, std::vector<Card> &combo)
{
    BotPlayer &bot = *this;
    double comboQuality = 0;
    Card::Picture oppositePicture = selectedCard.getPictureValue() == Card::Picture::Gentleman ? Card::Picture::Lady : Card::Picture::Gentleman;
    for (std::size_t i = 0; i < mainHand.size(); i++)
    {
        if (mainHand[i].getKind() == Card::Kind::Picture &&
            mainHand[i].getPictureValue() == oppositePicture)
        {
            combo = {mainHand[i]};
            comboQuality = mainHand[i].getQuality() + selectedCard.getQuality();
            bot.statistics.comboNumber += 1;
            if (comboQuality > bot.getMaxComboQuality())
            {
                bot.setMaxCombo(combo, comboQuality);
                bot.setMaxCard(selectedCard);
            }
        }
    }
}

// Расчёт ценности хода при розыгрше Хантера
void BotPlayer::findHunterCombo(const std::vector<Card> &mainHand, std::vector<Card> &combo)
{
    BotPlayer &bot = *this;
    double comboQuality = 0;
    for (std::size_t i = 0; i < mainHand.size(); i++)
    {
        if ((mainHand[i].getKind() == Card::Kind::Picture &&
             mainHand[i].getPictureValue() == Card::Picture::Hunter) ||
            (mainHand[i].getKind() == Card::Kind::Digital))
        {
            comboQuality += mainHand[i].getQuality();
            combo.push_back(mainHand[i]);
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
void BotPlayer::searchTrick(const std::vector<Card> &tableHand)
{
    BotPlayer &bot = *this;
    std::vector<Card> combo{};
    bot.statistics.minComboNumber = 2000;
    for (std::size_t i = 0; i < hand.size(); i++)
    {
        bot.setSelectedCard(hand[i]);
        if (selectedCard.getKind() == Card::Kind::Digital)
        {

            if (selectedCard.getDigitalValue() != 2)
                bot.findDigitalCombo(tableHand, combo, 22 - selectedCard.getDigitalValue());
            else
            {
                bot.findDigitalCombo(tableHand, combo, 22 - 2);
                combo.clear();
                findDigitalCombo(tableHand, combo, 22 - 11);
            }
        }
        else
        {
            if (selectedCard.getPictureValue() == Card::Picture::Gentleman ||
                selectedCard.getPictureValue() == Card::Picture::Lady)
            {
                bot.findPictureCombo(tableHand, combo);
            }
            else
            {
                bot.findHunterCombo(tableHand, combo);
            }
        }
        if (!(selectedCard.getKind() == Card::Kind::Picture && selectedCard.getPictureValue() == Card::Picture::Hunter))
        {
            // Отладка
            // ConsoleView view;
            /// std::cout << statistics.comboNumber  << ' ' << statistics.minComboNumber << std::endl;
            // view.printCard(selectedCard);
            if (bot.statistics.comboNumber < bot.statistics.minComboNumber)
            {
                bot.statistics.minComboNumber = bot.statistics.comboNumber;
                bot.statistics.minComboNumberIndex = i;
            }
            bot.clearComboNumber();
        }
        combo.clear();
    }
}

// Выбор карты при отсутствии взятки
void BotPlayer::selectNonComboCard()
{
    BotPlayer &bot = *this;
    bot.searchTrick(modifiedDeck);
    bot.setSelectedCard(hand[bot.statistics.minComboNumberIndex]);
}

void BotPlayer::preMoveActions(const std::vector<Card> &playerHand,
                               const std::vector<Card> &deckCards)
{
    BotPlayer &bot = *this;
    bot.setIsTrick(false);
    bot.clearSelectedTrick();
    bot.clearMaxCombo();
    bot.clearModifiedDeck();
    modifiedDeck.reserve(playerHand.size() + deckCards.size());
    modifiedDeck.insert(modifiedDeck.end(), deckCards.begin(), deckCards.end());
    modifiedDeck.insert(modifiedDeck.end(), playerHand.begin(), playerHand.end());
}

// Ход бота
bool BotPlayer::makeMove(Table &table)
{
    BotPlayer &bot = *this;
    bot.searchTrick(table.getCardsOnTable());
    if (bot.getMaxComboQuality() != 0)
    {
        bot.setSelectedCard(maxCard);
        bot.setSelectedTrick(maxCombo);
        if (selectedCard.getKind() == Card::Kind::Picture &&
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
        bot.selectNonComboCard();
        bot.clearSelectedTrick();
        if (selectedCard.getKind() == Card::Kind::Picture &&
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
    return true;
}