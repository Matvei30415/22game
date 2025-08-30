#include "human.h"

// Проверка суммы числовых карт
bool validate_digital_card_sum(CardList &selected_cards, Card &current_selected_card, short sum, short start_index)
{
    for (start_index; start_index < selected_cards.size(); start_index++)
    {
        if (selected_cards[start_index].getType() != Card::Digital)
        {
            return false;
        }
        if (selected_cards[start_index].getDigitalValue() != 2)
        {
            sum += selected_cards[start_index].getDigitalValue();
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
bool validate_trick(CardList &selected_cards, Card &current_selected_card, short size, short sum)
{
    // Проверка числовых карт
    if (current_selected_card.getType() == Card::Digital)
    {
        if (current_selected_card.getDigitalValue() != 2)
        {
            // Если карта из руки игрока НЕ Туз
            sum += current_selected_card.getDigitalValue();
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
    else if ((current_selected_card.getPictureValue() == 'G' &&
              (size != 1 || selected_cards[0].getPictureValue() != 'L')) ||
             (current_selected_card.getPictureValue() == 'L' &&
              (size != 1 || selected_cards[0].getPictureValue() != 'G')))
    {
        return false;
    }
    return true;
}

// Обработка взятки
bool process_trick(Player &table, Player &player, CardList &selected_cards, short &current_selected_card_index)
{
    bool valid_trick = validate_trick(selected_cards, player.getHand()[current_selected_card_index], selected_cards.size());
    CardList &table_hand = table.getHand();
    CardList &player_hand = player.getHand();
    CardList &player_tricks = player.getTricks();
    if (valid_trick)
    {
        // Если ход корректный, отправляем карты во взятки
        player.addCardToTrick(player_hand[current_selected_card_index]);
        player.removeCardFromHand(current_selected_card_index);
        player.addTrick(selected_cards);
    }
    else
    {
        // Если ход не корректный, возвращаем карты на стол
        while (selected_cards.size() > 0)
        {
            table.addCardToHand(selected_cards[0]);
            selected_cards.remove(0);
        }
    }
    return valid_trick;
}

// Выбор карт для взятки
void select_cards_for_trick(CardList &selected_cards, Player &table, Player &player)
{
    short selected_card_index = 0;
    CardList &table_hand = table.getHand();
    while (selected_card_index != invalid_input)
    {
        print_table(table.getHand(), table.getHand().size());
        std::cout << "Выберите карты для взятки: ";
        selected_card_index = get_move_input(1, table.getHand().size());
        if (selected_card_index == invalid_index)
        {
            std::cout << "Неверный индекс, попробуйте ещё раз!" << std::endl;
        }
        else if (selected_card_index != invalid_input)
        {
            --selected_card_index;
            selected_cards.add(table_hand[selected_card_index]);
            table.removeCardFromHand(selected_card_index);
        }
    }
}

// Выбор карты с руки
short select_card_from_hand(CardList &table_hand, CardList &current_hand, CardList &current_tricks)
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
void HumanPlayer::makeMove(Player &table, game_mode mode)
{
    CardList selected_cards;
    table.sortHand();
    Player &player = *this;
    CardList &table_hand = table.getHand();
    CardList &player_hand = player.getHand();
    CardList &player_tricks = player.getTricks();
    short selected_card_index = select_card_from_hand(table_hand, player_hand, player_tricks);
    Card selected_card = player_hand[selected_card_index];

    // Если стол не пустой и выбранная карта - не Хантер, выбираем карты для взятки
    if (table.getHand().size() != 0 && !(player_hand[selected_card_index].getType() == Card::Picture &&
                                         player_hand[selected_card_index].getPictureValue() == 'H'))
    {

        select_cards_for_trick(selected_cards, table, player);
        if (selected_cards.size() > 0)
        {
            bool valid_trick = process_trick(table, player, selected_cards, selected_card_index);
            if (!valid_trick)
            {
                std::cout << "Некорректный ход!" << std::endl;
                this->makeMove(table, mode);
                return;
            }
            is_trick = true;
        }
        else
        {
            table.addCardToHand(player_hand[selected_card_index]);
            player.removeCardFromHand(selected_card_index);
            is_trick = false;
        }
    }
    // Если стол пустой, выкладываем карту на стол
    else if (table_hand.size() == 0)
    {
        table.addCardToHand(player_hand[selected_card_index]);
        player.removeCardFromHand(selected_card_index);
        is_trick = false;
    }
    // Иначе, выбранная карта = Hunter, запускаем механизм обработки
    else
    {
        is_trick = process_hunter_move(table, player, selected_card_index);
    }
    if (mode == with_other_player)
    {
        confirm_move(selected_card, selected_cards);
    }
}