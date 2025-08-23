#include "points.h"

// Вычисление очков в конце партии
void сalculate_points(points &results, card_list &current_hand, short len)
{
    if (len > 24)
        results.get_more_cards = 2;
    else if (len == 24)
        results.get_more_cards = 1;
    short sum_clubs = 0;
    for (int i = 0; i < len; i++)
    {
        if (current_hand[i].suit == 'C')
            sum_clubs += 1;
        if (current_hand[i].value.digital_cards == 20 && current_hand[i].suit == 'D')
            results.get_twenty_of_diamonds = true;
        else if (current_hand[i].value.digital_cards == 2 && current_hand[i].suit == 'H')
            results.get_ace_of_hearts = true;
    }
    if (sum_clubs > 5)
        results.get_more_clubs = true;
}