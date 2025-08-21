#include "basic.h"

const std::string line(100, '-');

// Перемещение карты из src в dst, с последующим удалением в src
void move_card(std::vector<card> &dst, std::vector<card> &src, short index)
{
    dst.emplace_back(src[index]);
    src.erase(src.cbegin() + index);
}

// Очистка списка карт
void clear_card_list(std::vector<card> &src)
{
    while (src.size() > 0)
        src.pop_back();
}

// Сортировка текущих карт на столе
void sort_card_list(std::vector<card> &src)
{
    short count_picture_cards = 0;
    card tmp;
    for (short idx_i = 0; idx_i < src.size(); idx_i++)
    {
        if (src[idx_i].type == picture_card)
        {
            tmp = src[idx_i];
            src.erase(src.cbegin() + idx_i);
            src.insert(src.cbegin(), tmp);
            count_picture_cards++;
            continue;
        }
        for (short idx_j = idx_i + 1; idx_j < src.size(); idx_j++)
        {
            if ((src[idx_i].type == digital_card && src[idx_j].type == digital_card) &&
                ((src[idx_i].value.digital_cards > src[idx_j].value.digital_cards) ||
                 ((src[idx_i].value.digital_cards == src[idx_j].value.digital_cards) &&
                  (src[idx_i].suit != 'G' && src[idx_j].suit == 'G'))))
            {
                std::swap(src[idx_i], src[idx_j]);
            }
        }
    }
    for (short idx_i = 0; idx_i < count_picture_cards; idx_i++)
    {
        for (short idx_j = idx_i + 1; idx_j < count_picture_cards; idx_j++)
        {
            if ((src[idx_i].value.picture_cards == 'L' && src[idx_j].value.picture_cards == 'G') ||
                (src[idx_i].value.picture_cards == 'H') ||
                ((src[idx_i].value.picture_cards == src[idx_j].value.picture_cards) &&
                 (src[idx_i].suit != 'G' && src[idx_j].suit == 'G')))
            {
                std::swap(src[idx_i], src[idx_j]);
            }
        }
    }
}