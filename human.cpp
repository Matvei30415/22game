#include "human.h"

// Проверка суммы числовых карт
bool HumanPlayer::validate_digital_card_sum(short sum, short start_index)
{
    HumanPlayer &player = *this;
    for (start_index; start_index < selectedTrick.size(); start_index++)
    {
        if (selectedTrick[start_index].getType() != Card::Digital)
        {
            return false;
        }
        if (selectedTrick[start_index].getDigitalValue() != 2)
        {
            sum += selectedTrick[start_index].getDigitalValue();
        }
        else
        {
            // Если встречаем Туз, воспринимаем как 2 или 11
            return validate_digital_card_sum(sum + 2, start_index + 1) ||
                   validate_digital_card_sum(sum + 11, start_index + 1);
        }
    }
    if (sum != 22)
    {
        return false;
    }
    return true;
}

// Проверка корректности взятки
bool HumanPlayer::validate_trick()
{
    short sum = 0;
    HumanPlayer &player = *this;
    // Проверка числовых карт
    if (selectedCard.getType() == Card::Digital)
    {
        if (selectedCard.getDigitalValue() != 2)
        {
            // Если карта из руки игрока НЕ Туз
            sum += selectedCard.getDigitalValue();
            return validate_digital_card_sum(sum);
        }
        else
        {
            // Если карта из руки игрока Туз -> Воспринимаем как 2 или 11
            return validate_digital_card_sum(sum + 2) ||
                   validate_digital_card_sum(sum + 11);
        }
    }
    // Проверка Леди + Джентльмен
    else if ((selectedCard.getPictureValue() == 'G' &&
              (selectedTrick.size() != 1 || selectedTrick[0].getPictureValue() != 'L')) ||
             (selectedCard.getPictureValue() == 'L' &&
              (selectedTrick.size() != 1 || selectedTrick[0].getPictureValue() != 'G')))
    {
        return false;
    }
    return true;
}

// Обработка взятки
bool HumanPlayer::process_trick(Player &table)
{
    HumanPlayer &player = *this;
    std::vector<Card> &tableHand = table.getHand();
    bool valid_trick = player.validate_trick();
    if (valid_trick)
    {
        // Если ход корректный, отправляем карты во взятки
        player.addCardToTricks(selectedCard);
        player.removeCardFromHand(selectedCard);
        player.addTrickToTricks(selectedTrick);
        table.removeTrickFromHand(selectedTrick);
    }
    else
    {
        // Если ход не корректный, возвращаем карты на стол
        player.clearSelectedTrick();
    }
    return valid_trick;
}

// Обработка 1 хода (Весь визуал игрока здесь, основное внимание)
void HumanPlayer::makeMove(Player &table, game_mode mode)
{
    table.sortHand();
    HumanPlayer &player = *this;
    std::vector<Card> &tableHand = table.getHand();
    short selected_card_index = get_card_input(tableHand, hand);
    player.setSelectedCard(hand[selected_card_index]);
    player.setIsTrick(false);

    // Если стол не пустой и выбранная карта - не Хантер, выбираем карты для взятки
    if (tableHand.size() != 0 &&
        !(selectedCard.getType() == Card::Picture &&
          selectedCard.getPictureValue() == 'H'))
    {
        std::vector<Card> table_hand_copy = tableHand;
        short selected_trick_index = 0;
        while (selected_trick_index != -1)
        {

            selected_trick_index = get_trick_input(table_hand_copy, selectedTrick);
            if (selected_trick_index != -1)
            {
                selectedTrick.push_back(table_hand_copy[selected_trick_index]);
                table_hand_copy.erase(begin(table_hand_copy) + selected_trick_index);
            }
        }

        if (selectedTrick.size() > 0)
        {
            bool valid_trick = player.process_trick(table);
            if (!valid_trick)
            {
                std::cout << "Некорректный ход!" << std::endl;
                this->makeMove(table, mode);
                return;
            }
            player.setIsTrick(true);
        }
        else
        {
            table.addCardToHand(selectedCard);
            player.removeCardFromHand(selectedCard);
            player.setIsTrick(false);
        }
    }
    // Если стол пустой, выкладываем карту на стол
    else if (tableHand.size() == 0)
    {
        table.addCardToHand(selectedCard);
        player.removeCardFromHand(selectedCard);
        player.setIsTrick(false);
    }
    // Иначе, выбранная карта = Hunter, запускаем механизм обработки
    else
    {
        player.makeHunterMove(table);
    }
    if (mode == with_other_player)
    {
        confirm_move(selectedCard, selectedTrick);
    }
    player.clearSelectedTrick();
}