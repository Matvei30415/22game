#include "bot.h"

void BotPlayer::setMaxCombo(std::vector<Card> &combo, double quality)
{
    this->maxCombo = combo;
    this->maxComboQuality = quality;
}

void BotPlayer::setMaxCard(Card &card)
{
    this->maxCard = card;
}

std::vector<Card> &BotPlayer::getMaxCombo()
{
    return this->maxCombo;
}

Card &BotPlayer::getMaxCard()
{
    return this->maxCard;
}

double BotPlayer::getMaxComboQuality()
{
    return this->maxComboQuality;
}

void BotPlayer::clearMaxCombo()
{
    (this->maxCombo).clear();
    this->maxComboQuality = 0;
}

// Нахождение комбинации с цифровыми картами
void BotPlayer::find_digital_combinations(Player &table, std::vector<Card> &combo, short n, short start)
{
    BotPlayer &bot = *this;
    std::vector<Card> &tableHand = table.getHand();
    double current_combo_quality = 0;
    if (n == 0)
    {
        current_combo_quality += selectedCard.getQuality();
        for (short i = 0; i < combo.size(); i++)
        {
            current_combo_quality += combo[i].getQuality();
        }
        if (current_combo_quality > bot.getMaxComboQuality())
        {
            bot.setMaxCombo(combo, current_combo_quality);
            bot.setMaxCard(selectedCard);
        }
    }

    for (short i = start; i < tableHand.size(); i++)
    {
        if (tableHand[i].getType() == Card::Digital && tableHand[i].getDigitalValue() <= n)
        {
            combo.push_back(tableHand[i]);
            if (tableHand[i].getDigitalValue() != 2)
                find_digital_combinations(table, combo, n - tableHand[i].getDigitalValue(), i + 1);
            else
            {
                find_digital_combinations(table, combo, n - 2, i + 1);
                find_digital_combinations(table, combo, n - 11, i + 1);
            }
            combo.pop_back();
        }
    }
}

// Нахождение комбинации с лицами
void BotPlayer::find_picture_combinations(Player &table, std::vector<Card> &combo)
{
    BotPlayer &bot = *this;
    std::vector<Card> &tableHand = table.getHand();
    double current_combo_quality = 0;
    char current_value = selectedCard.getPictureValue() == 'G' ? 'L' : 'G';
    for (int i = 0; i < tableHand.size(); i++)
    {
        if (tableHand[i].getType() == Card::Picture && tableHand[i].getPictureValue() == current_value)
        {
            combo = {tableHand[i]};
            current_combo_quality = tableHand[i].getQuality() + selectedCard.getQuality();
            if (current_combo_quality > bot.getMaxComboQuality())
            {
                bot.setMaxCombo(combo, current_combo_quality);
                bot.setMaxCard(selectedCard);
            }
        }
        else if (tableHand[i].getType() == Card::Digital)
            break;
    }
}

// Расчёт ценности хода при розыгрше Хантера
void BotPlayer::find_hunter_combinations(Player &table, std::vector<Card> &combo)
{
    BotPlayer &bot = *this;
    std::vector<Card> &tableHand = table.getHand();
    double current_combo_quality = 0;
    for (int i = 0; i < tableHand.size(); i++)
    {
        if ((tableHand[i].getType() == Card::Picture && tableHand[i].getPictureValue() == 'H') ||
            (tableHand[i].getType() == Card::Digital))
        {
            current_combo_quality += tableHand[i].getQuality();
            combo.push_back(tableHand[i]);
        }
    }
    // Закомментировано из-за неэффективности использования карты Hunter ботом
    // if (current_combo_quality != 0)
    //     current_combo_quality += selectedCard.getQuality();
    if (current_combo_quality > bot.getMaxComboQuality())
    {
        bot.setMaxCombo(combo, current_combo_quality);
        bot.setMaxCard(selectedCard);
    }
}

// Поиск самого выгодного хода для бота
void BotPlayer::search_trick(Player &table)
{
    BotPlayer &bot = *this;
    std::vector<Card> combo{};
    // selectedTrick.clear();
    for (int i = 0; i < hand.size(); i++)
    {
        bot.setSelectedCard(hand[i]);
        if (selectedCard.getType() == Card::Digital)
        {

            if (selectedCard.getDigitalValue() != 2)
                bot.find_digital_combinations(table, combo, 22 - selectedCard.getDigitalValue());
            else
            {
                bot.find_digital_combinations(table, combo, 22 - 2);
                combo.clear();
                find_digital_combinations(table, combo, 22 - 11);
            }
        }
        else
        {
            if (selectedCard.getPictureValue() == 'G' || selectedCard.getPictureValue() == 'L')
            {
                bot.find_picture_combinations(table, combo);
            }
            else
            {
                bot.find_hunter_combinations(table, combo);
            }
        }
        combo.clear();
    }
}

// Ход бота (Весь визуал бота здесь)
void BotPlayer::makeMove(Player &table, game_mode mode)
{
    table.sortHand();
    BotPlayer &bot = *this;
    bot.search_trick(table);
    // print_bot_hand(botHand, botHand.size());
    if (bot.getMaxComboQuality() != 0)
    {
        bot.setSelectedCard(maxCard);
        print_move(selectedCard, maxCombo);
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
        print_card(selectedCard);
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