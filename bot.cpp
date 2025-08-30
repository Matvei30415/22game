#include "bot.h"

// Нахождение комбинации с цифровыми картами
void find_digital_combinations(std::vector<Card> &current_hand, Card &current_card, short n, std::vector<Card> &combo, std::vector<Card> &max_combo, double &max_combo_quality, bool &res, short start)
{
    double current_combo_quality = 0;
    if (n == 0)
    {
        current_combo_quality += current_card.getQuality();
        for (short i = 0; i < combo.size(); i++)
        {
            current_combo_quality += combo[i].getQuality();
        }
        if (current_combo_quality > max_combo_quality)
        {
            max_combo_quality = current_combo_quality;
            max_combo = combo;
            res = true;
        }
    }

    for (short i = start; i < current_hand.size(); i++)
    {
        if (current_hand[i].getType() == Card::Digital && current_hand[i].getDigitalValue() <= n)
        {
            combo.push_back(current_hand[i]);
            if (current_hand[i].getDigitalValue() != 2)
                find_digital_combinations(current_hand, current_card, n - current_hand[i].getDigitalValue(), combo, max_combo, max_combo_quality, res, i + 1);
            else
            {
                find_digital_combinations(current_hand, current_card, n - 2, combo, max_combo, max_combo_quality, res, i + 1);
                find_digital_combinations(current_hand, current_card, n - 11, combo, max_combo, max_combo_quality, res, i + 1);
            }
            combo.pop_back();
        }
    }
}

// Нахождение комбинации с лицами
bool find_picture_combinations(std::vector<Card> &current_hand, Card &current_card, std::vector<Card> &max_combo, double max_combo_quality)
{
    bool res = false;
    char current_value = current_card.getPictureValue() == 'G' ? 'L' : 'G';
    for (int i = 0; i < current_hand.size(); i++)
    {
        if (current_hand[i].getType() == Card::Picture && current_hand[i].getPictureValue() == current_value)
        {
            if (current_hand[i].getQuality() + current_card.getQuality() > max_combo_quality)
            {
                max_combo_quality = current_hand[i].getQuality() + current_card.getQuality();
                max_combo.clear();
                max_combo.push_back(current_hand[i]);
                res = true;
            }
        }
        else if (current_hand[i].getType() == Card::Digital)
            break;
    }
    return res;
}

// Расчёт ценности хода при розыгрше Хантера
bool find_hunter_combinations(std::vector<Card> &current_hand, Card &current_card, std::vector<Card> &combo, std::vector<Card> &max_combo, double max_combo_quality)
{
    bool res = false;
    double current_combo_quality = 0;
    for (int i = 0; i < current_hand.size(); i++)
    {
        if ((current_hand[i].getType() == Card::Picture && current_hand[i].getPictureValue() == 'H') ||
            (current_hand[i].getType() == Card::Digital))
        {
            current_combo_quality += current_hand[i].getQuality();
            combo.push_back(current_hand[i]);
        }
    }
    if (current_combo_quality != 0)
        current_combo_quality += current_card.getQuality();
    if (current_combo_quality > max_combo_quality)
    {
        max_combo_quality = current_combo_quality;
        max_combo = combo;
        res = true;
    }
    return res;
}

// Поиск самого выгодного хода для бота
short search_trick(std::vector<Card> &selected_cards, std::vector<Card> &table_hand, std::vector<Card> &current_hand, std::vector<Card> &max_combo)
{
    bool find_new_max_combo = false;
    std::vector<Card> combo{};
    double max_combo_quality = 0;
    short max_combo_card_index = -1;
    selected_cards.clear();
    for (int i = 0; i < current_hand.size(); i++)
    {
        find_new_max_combo = false;
        if (current_hand[i].getType() == Card::Digital)
        {
            if (current_hand[i].getDigitalValue() != 2)
                find_digital_combinations(table_hand, current_hand[i], 22 - current_hand[i].getDigitalValue(), combo, max_combo, max_combo_quality, find_new_max_combo);
            else
            {
                find_digital_combinations(table_hand, current_hand[i], 22 - 2, combo, max_combo, max_combo_quality, find_new_max_combo);
                combo.clear();
                if (find_new_max_combo)
                    max_combo_card_index = i;
                find_new_max_combo = false;
                find_digital_combinations(table_hand, current_hand[i], 22 - 11, combo, max_combo, max_combo_quality, find_new_max_combo);
            }
            combo.clear();
            if (find_new_max_combo)
                max_combo_card_index = i;
        }
        else
        {
            if (current_hand[i].getPictureValue() == 'G' || current_hand[i].getPictureValue() == 'L')
            {
                find_new_max_combo = find_picture_combinations(table_hand, current_hand[i], max_combo, max_combo_quality);
                combo.clear();
                if (find_new_max_combo)
                    max_combo_card_index = i;
            }
            else
            {
                find_new_max_combo = find_hunter_combinations(table_hand, current_hand[i], combo, max_combo, max_combo_quality);
                combo.clear();
                if (find_new_max_combo)
                    max_combo_card_index = i;
            }
        }
    }
    return max_combo_card_index;
}

// Ход бота
void BotPlayer::makeMove(Player &table, game_mode mode)
{
    std::vector<Card> selected_cards;
    table.sortHand();
    std::vector<Card> max_combo{};
    Player &bot = *this;
    std::vector<Card> &table_hand = table.getHand();
    std::vector<Card> &current_hand = this->getHand();
    std::vector<Card> &current_tricks = this->getTricks();
    short selected_card_index = search_trick(selected_cards, table_hand, current_hand, max_combo);
    // print_bot_hand(current_hand, current_hand.size());
    if (selected_card_index != -1)
    {
        print_move(current_hand[selected_card_index], max_combo);
        if (current_hand[selected_card_index].getType() == Card::Picture && current_hand[selected_card_index].getPictureValue() == 'H')
        {
            is_trick = process_hunter_move(table, *this, selected_card_index);
        }
        else
        {
            is_trick = true;
            bot.addCardToTrick(current_hand[selected_card_index]);
            bot.removeCardFromHand(selected_card_index);
            for (short i = 0; i < max_combo.size(); i++)
                for (short j = 0; j < table_hand.size(); j++)
                    if (max_combo[i].getID() == table_hand[j].getID())
                    {
                        bot.addCardToTrick(table_hand[j]);
                        table.removeCardFromHand(j);
                    }
        }
    }
    else
    {
        selected_card_index = rand() % current_hand.size();
        print_card(current_hand[selected_card_index]);
        if (current_hand[selected_card_index].getType() == Card::Picture && current_hand[selected_card_index].getPictureValue() == 'H')
        {
            is_trick = process_hunter_move(table, *this, selected_card_index);
        }
        else
        {
            is_trick = false;
            table.addCardToHand(current_hand[selected_card_index]);
            bot.removeCardFromHand(selected_card_index);
        }
    }
}