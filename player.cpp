#include "player.h"

// Проверка суммы числовых карт
bool validate_digital_card_sum(card_list &selected_cards, card &current_selected_card, short sum, short start_index)
{
    for (start_index; start_index < selected_cards.size(); start_index++)
    {
        if (selected_cards[start_index].type != digital_card)
        {
            return false;
        }
        if (selected_cards[start_index].value.digital_cards != 2)
        {
            sum += selected_cards[start_index].value.digital_cards;
        }
        else
        {
            // Если встречаем Туз, воспринимаем как 2 или 11
            return validate_digital_card_sum(selected_cards, current_selected_card, sum + 2, start_index + 1) ||
                   validate_digital_card_sum(selected_cards, current_selected_card, sum + 11, start_index + 1);
        }
    }
    if (sum != 22)
    {
        return false;
    }
    return true;
}

// Проверка корректности взятки
bool validate_trick(card_list &selected_cards, card &current_selected_card, short size, short sum)
{
    // Проверка числовых карт
    if (current_selected_card.type == digital_card)
    {
        if (current_selected_card.value.digital_cards != 2)
        {
            // Если карта из руки игрока НЕ Туз
            sum += current_selected_card.value.digital_cards;
            return validate_digital_card_sum(selected_cards, current_selected_card, sum);
        }
        else
        {
            // Если карта из руки игрока Туз -> Воспринимаем как 2 или 11
            return validate_digital_card_sum(selected_cards, current_selected_card, sum + 2) ||
                   validate_digital_card_sum(selected_cards, current_selected_card, sum + 11);
        }
    }
    // Проверка Леди + Джентльмен
    else if ((current_selected_card.value.picture_cards == 'G' &&
              (size != 1 || selected_cards[0].value.picture_cards != 'L')) ||
             (current_selected_card.value.picture_cards == 'L' &&
              (size != 1 || selected_cards[0].value.picture_cards != 'G')))
    {
        return false;
    }
    return true;
}

// Обработка взятки
bool process_trick(card_list &table_hand, card_list &current_hand, card_list &current_tricks, card_list &selected_cards, short &current_selected_card_index)
{
    bool valid_trick = validate_trick(selected_cards, current_hand[current_selected_card_index], selected_cards.size());
    if (valid_trick)
    {
        // Если ход корректный, отправляем карты во взятки
        card_list::move_card(current_tricks, current_hand, current_selected_card_index);
        for (short i = 0; i < selected_cards.size(); i++)
        {
            card_list::copy_card(current_tricks, selected_cards, i);
        }
    }
    else
    {
        // Если ход не корректный, возвращаем карты на стол
        while (selected_cards.size() > 0)
        {
            card_list::move_card(table_hand, selected_cards);
        }
        std::cout << "Некорректный ход!" << std::endl;
    }
    return valid_trick;
}

// Выбор карт для взятки
void select_cards_for_trick(card_list &selected_cards, card_list &table_hand, card_list &current_hand, card_list &current_tricks)
{
    short selected_card_index = 0;
    while (selected_card_index != invalid_input)
    {
        print_table(table_hand, table_hand.size());
        std::cout << "Выберите карты для взятки: ";
        selected_card_index = get_move_input(1, table_hand.size());
        if (selected_card_index == invalid_index)
        {
            std::cout << "Неверный индекс, попробуйте ещё раз!" << std::endl;
        }
        else if (selected_card_index != invalid_input)
        {
            card_list::move_card(selected_cards, table_hand, --selected_card_index);
        }
    }
}

// Выбор карты с руки
short select_card_from_hand(card_list &table_hand, card_list &current_hand, card_list &current_tricks)
{
    short selected_card_index = 0;
    while (selected_card_index <= 0)
    {
        print_table(table_hand, table_hand.size());
        print_hand(current_hand, current_hand.size());
        selected_card_index = get_move_input(1, current_hand.size());
        if (selected_card_index == invalid_input)
        {
            std::cout << "Неверный ввод, попробуйте ещё раз!" << std::endl;
        }
        else if (selected_card_index == invalid_index)
        {
            std::cout << "Неверный индекс, попробуйте ещё раз!" << std::endl;
        }
    }
    selected_card_index--;
    return selected_card_index;
}

// Обработка 1 хода
void process_player_move(card_list &table_hand, card_list &current_hand, card_list &current_tricks, card_list &selected_cards, bool &is_trick, const game_mode mode)
{
    card_list::clear_card_list(selected_cards);
    card_list::sort_card_list(table_hand);
    short selected_card_index = select_card_from_hand(table_hand, current_hand, current_tricks);
    card selected_card = current_hand[selected_card_index];
    // Если стол не пустой и выбранная карта - не Хантер, выбираем карты для взятки
    if (table_hand.size() != 0 && !(current_hand[selected_card_index].type == picture_card && current_hand[selected_card_index].value.picture_cards == 'H'))
    {

        select_cards_for_trick(selected_cards, table_hand, current_hand, current_tricks);
        if (selected_cards.size() > 0)
        {
            bool valid_trick = process_trick(table_hand, current_hand, current_tricks, selected_cards, selected_card_index);
            if (!valid_trick)
            {
                process_player_move(table_hand, current_hand, current_tricks, selected_cards, is_trick, mode);
                return;
            }
            is_trick = true;
        }
        else
        {
            card_list::move_card(table_hand, current_hand, selected_card_index);
            is_trick = false;
        }
    }
    // Если стол пустой, выкладываем карту на стол
    else if (table_hand.size() == 0)
    {
        card_list::move_card(table_hand, current_hand, selected_card_index);
        is_trick = false;
    }
    // Иначе, выбранная карта = Hunter, запускаем механизм обработки
    else
    {
        is_trick = process_hunter_move(table_hand, current_hand, current_tricks, selected_card_index);
    }
    if (mode == with_other_player)
    {
        confirm_move(selected_card, selected_cards);
    }
    card_list::clear_card_list(selected_cards);
}