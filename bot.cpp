#include "bot.h"

// Нахождение комбинации с цифровыми картами
void find_digital_combinations(card_list &current_hand, card &current_card, short n, card_list &combo, card_list &max_combo, double &max_combo_quality, bool &res, short start)
{
    double current_combo_quality = 0;
    if (n == 0)
    {
        current_combo_quality += current_card.quality;
        for (short i = 0; i < combo.size(); i++)
        {
            current_combo_quality += combo[i].quality;
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
        if (current_hand[i].type == digital_card && current_hand[i].value.digital_cards <= n)
        {
            combo.push_back(current_hand[i]);
            if (current_hand[i].value.digital_cards != 2)
                find_digital_combinations(current_hand, current_card, n - current_hand[i].value.digital_cards, combo, max_combo, max_combo_quality, res, i + 1);
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
bool find_picture_combinations(card_list &current_hand, card &current_card, card_list &max_combo, double max_combo_quality)
{
    bool res = false;
    char current_value = current_card.value.picture_cards == 'G' ? 'L' : 'G';
    for (int i = 0; i < current_hand.size(); i++)
    {
        if (current_hand[i].type == picture_card && current_hand[i].value.picture_cards == current_value)
        {
            if (current_hand[i].quality + current_card.quality > max_combo_quality)
            {
                max_combo_quality = current_hand[i].quality + current_card.quality;
                card_list::clear_card_list(max_combo);
                max_combo.push_back(current_hand[i]);
                res = true;
            }
        }
        else if (current_hand[i].type == digital_card)
            break;
    }
    return res;
}

// Расчёт ценности хода при розыгрше Хантера
bool find_hunter_combinations(card_list &current_hand, card &current_card, card_list &combo, card_list &max_combo, double max_combo_quality)
{
    bool res = false;
    double current_combo_quality = 0;
    for (int i = 0; i < current_hand.size(); i++)
    {
        if ((current_hand[i].type == picture_card && current_hand[i].value.picture_cards == 'H') ||
            (current_hand[i].type == digital_card))
        {
            current_combo_quality += current_hand[i].quality;
            combo.push_back(current_hand[i]);
        }
    }
    if (current_combo_quality != 0)
        current_combo_quality += current_card.quality;
    if (current_combo_quality > max_combo_quality)
    {
        max_combo_quality = current_combo_quality;
        max_combo = combo;
        res = true;
    }
    return res;
}

// Поиск самого выгодного хода для бота
void search_trick(card_list &selected_cards, card_list &table_hand, card_list &current_hand, card_list &max_combo, short &max_combo_card_index)
{
    bool find_new_max_combo = false;
    card_list combo{};
    double max_combo_quality = 0;
    card_list::clear_card_list(selected_cards);
    for (int i = 0; i < current_hand.size(); i++)
    {
        find_new_max_combo = false;
        if (current_hand[i].type == digital_card)
        {
            if (current_hand[i].value.digital_cards != 2)
                find_digital_combinations(table_hand, current_hand[i], 22 - current_hand[i].value.digital_cards, combo, max_combo, max_combo_quality, find_new_max_combo);
            else
            {
                find_digital_combinations(table_hand, current_hand[i], 22 - 2, combo, max_combo, max_combo_quality, find_new_max_combo);
                card_list::clear_card_list(combo);
                if (find_new_max_combo)
                    max_combo_card_index = i;
                find_new_max_combo = false;
                find_digital_combinations(table_hand, current_hand[i], 22 - 11, combo, max_combo, max_combo_quality, find_new_max_combo);
            }
            card_list::clear_card_list(combo);
            if (find_new_max_combo)
                max_combo_card_index = i;
        }
        else
        {
            if (current_hand[i].value.picture_cards == 'G' || current_hand[i].value.picture_cards == 'L')
            {
                find_new_max_combo = find_picture_combinations(table_hand, current_hand[i], max_combo, max_combo_quality);
                card_list::clear_card_list(combo);
                if (find_new_max_combo)
                    max_combo_card_index = i;
            }
            else
            {
                find_new_max_combo = find_hunter_combinations(table_hand, current_hand[i], combo, max_combo, max_combo_quality);
                card_list::clear_card_list(combo);
                if (find_new_max_combo)
                    max_combo_card_index = i;
            }
        }
    }
}

// Ход бота
void process_bot_move(card_list &table_hand, card_list &current_hand, card_list &current_tricks, card_list &selected_cards, bool &is_trick)
{
    card_list card_from_hand{};
    card_list max_combo{};
    short choosen_card_index = -1;
    card_list::sort_card_list(table_hand);
    // print_bot_hand(current_hand, current_hand.size());
    search_trick(selected_cards, table_hand, current_hand, max_combo, choosen_card_index);
    if (choosen_card_index != -1)
    {
        card_from_hand.push_back(current_hand[choosen_card_index]);
        print_card_list(card_from_hand, 1);
        if (current_hand[choosen_card_index].type == picture_card && current_hand[choosen_card_index].value.picture_cards == 'H')
        {
            is_trick = process_hunter_move(table_hand, current_hand, current_tricks, choosen_card_index);
        }
        else
        {
            is_trick = true;
            print_card_list(max_combo, max_combo.size());
            card_list::move_card(current_tricks, current_hand, choosen_card_index);
            for (short i = 0; i < max_combo.size(); i++)
                for (short j = 0; j < table_hand.size(); j++)
                    if (max_combo[i].id == table_hand[j].id)
                        card_list::move_card(current_tricks, table_hand, j);
        }
    }
    else
    {
        is_trick = false;
        choosen_card_index = rand() % current_hand.size();
        card_from_hand.push_back(current_hand[choosen_card_index]);
        print_card_list(card_from_hand, 1);
        if (current_hand[choosen_card_index].type == picture_card && current_hand[choosen_card_index].value.picture_cards == 'H')
        {
            is_trick = process_hunter_move(table_hand, current_hand, current_tricks, choosen_card_index);
        }
        else
        {
            is_trick = false;
            card_list::move_card(table_hand, current_hand, choosen_card_index);
        }
    }
}