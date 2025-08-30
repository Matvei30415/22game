#include "hunter.h"
#include "player.h"

// Обработка механизма карты Hunter
bool process_hunter_move(Player &table, Player &player, short selected_card_index)
{
    bool is_trick = false;
    short count_erase = 0;
    CardList &table_hand = table.getHand();
    CardList &current_hand = player.getHand();
    CardList &current_tricks = player.getTricks();
    for (short i = 0; i < table_hand.size(); i++)
    {
        // Проверяем, что карта не Gentleman или Lady
        if (!(table_hand[i].getType() == Card::Picture && (table_hand[i].getPictureValue() == 'G' || table_hand[i].getPictureValue() == 'L')))
        {
            player.addCardToTrick(table_hand[i]);
            table.removeCardFromHand(i);
            count_erase++;
            i--;
        }
    }
    // Остаётся на столе, если не взял ни одной числовой карты или Hunter'a
    if (count_erase == 0)
    {
        table.addCardToHand(current_hand[selected_card_index]);
        player.removeCardFromHand(selected_card_index);
    }
    // Отправляется во взятки, если взял хотя бы одну числовую карту или Hunter'а
    else
    {
        is_trick = true;
        player.addCardToTrick(current_hand[selected_card_index]);
        player.removeCardFromHand(selected_card_index);
    }
    return is_trick;
}