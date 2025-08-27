#include "hunter.h"

// Обработка механизма карты Hunter
bool process_hunter_move(card_list &table_hand, card_list &current_hand, card_list &current_tricks, short selected_card_index)
{
    bool is_trick = false;
    short count_erase = 0;
    for (short i = 0; i < table_hand.size(); i++)
    {
        // Проверяем, что карта не Gentleman или Lady
        if (!(table_hand[i].type == picture_card && (table_hand[i].value.picture_cards == 'G' || table_hand[i].value.picture_cards == 'L')))
        {
            card_list::move_card(current_tricks, table_hand, i);
            count_erase++;
            i--;
        }
    }
    // Остаётся на столе, если не взял ни одной числовой карты или Hunter'a
    if (count_erase == 0)
    {
        card_list::move_card(table_hand, current_hand, selected_card_index);
    }
    // Отправляется во взятки, если взял хотя бы одну числовую карту или Hunter'а
    else
    {
        is_trick = true;
        card_list::move_card(current_tricks, current_hand, selected_card_index);
    }
    return is_trick;
}