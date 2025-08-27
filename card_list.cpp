#include "card_list.h"

// Конструктор для класса card_list
card_list::card_list(short size) {
    this->resize(size);
}

// Перемещение карты из src в dst, с последующим удалением в src
void card_list::move_card(card_list &dst, card_list &src, short index)
{
    dst.emplace_back(src[index]);
    src.erase(src.cbegin() + index);
}

// Копирование карты из src в dst, без последующего удаления в src
void card_list::copy_card(card_list &dst, card_list &src, short index)
{
    dst.emplace_back(src[index]);
}

// Очистка списка карт
void card_list::clear_card_list(card_list &src)
{
    while (src.size() > 0)
        src.pop_back();
}

// Сортировка текущих карт на столе
void card_list::sort_card_list(card_list &src)
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