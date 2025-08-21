#include "hunter.h"

// Обработка механизма карты Hunter
bool process_hunter_move(std::vector<card> &table_hand, std::vector<card> &current_hand, std::vector<card> &current_tricks, short chosen_card_index)
{
    bool is_trick = false;
    short count_erase = 0;
    for (short i = 0; i < table_hand.size(); i++)
    {
        // Проверяем, что карта не Gentleman или Lady
        if (!(table_hand[i].type == picture_card && (table_hand[i].value.picture_cards == 'G' || table_hand[i].value.picture_cards == 'L')))
        {
            move_card(current_tricks, table_hand, i);
            count_erase++;
            i--;
        }
    }
    // Остаётся на столе, если не взял ни одной числовой карты или Hunter'a
    if (count_erase == 0)
    {
        move_card(table_hand, current_hand, chosen_card_index);
    }
    // Отправляется во взятки, если взял хотя бы одну числовую карту или Hunter'а
    else
    {
        is_trick = true;
        move_card(current_tricks, current_hand, chosen_card_index);
    }
    return is_trick;
}