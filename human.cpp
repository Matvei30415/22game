#include "human.h"

// Проверка суммы числовых карт
bool HumanPlayer::validateDigitalCardSum(short sum, short start)
{
    HumanPlayer &player = *this;
    for (start; start < selectedTrick.size(); start++)
    {
        if (selectedTrick[start].getType() != Card::Digital)
        {
            return false;
        }
        if (selectedTrick[start].getDigitalValue() != 2)
        {
            sum += selectedTrick[start].getDigitalValue();
        }
        else
        {
            // Если встречаем Туз, воспринимаем как 2 или 11
            return validateDigitalCardSum(sum + 2, start + 1) ||
                   validateDigitalCardSum(sum + 11, start + 1);
        }
    }
    if (sum != 22)
    {
        return false;
    }
    return true;
}

// Проверка корректности взятки
bool HumanPlayer::validateTrick()
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
            return validateDigitalCardSum(sum);
        }
        else
        {
            // Если карта из руки игрока Туз -> Воспринимаем как 2 или 11
            return validateDigitalCardSum(sum + 2) ||
                   validateDigitalCardSum(sum + 11);
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
bool HumanPlayer::processTrick(Table &table)
{
    HumanPlayer &player = *this;
    std::vector<Card> &tableHand = table.getHand();
    bool validTrick = player.validateTrick();
    if (validTrick)
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
    return validTrick;
}

// Обработка 1 хода (Весь визуал игрока здесь, основное внимание)
void HumanPlayer::makeMove(Table &table, gameMode mode)
{
    table.sortHand();
    HumanPlayer &player = *this;
    std::vector<Card> &tableHand = table.getHand();
    short selectedCardIndex = getCardInput(tableHand, hand);
    player.setSelectedCard(hand[selectedCardIndex]);
    player.setIsTrick(false);

    // Если стол не пустой и выбранная карта - не Хантер, выбираем карты для взятки
    if (tableHand.size() != 0 &&
        !(selectedCard.getType() == Card::Picture &&
          selectedCard.getPictureValue() == 'H'))
    {
        std::vector<Card> tableHandCopy = tableHand;
        short selectedTrickCardIndex = 0;
        while (selectedTrickCardIndex != invalidInput)
        {

            selectedTrickCardIndex = getTrickInput(tableHandCopy, selectedTrick);
            if (selectedTrickCardIndex != invalidInput)
            {
                selectedTrick.push_back(tableHandCopy[selectedTrickCardIndex]);
                tableHandCopy.erase(begin(tableHandCopy) + selectedTrickCardIndex);
            }
        }

        if (selectedTrick.size() > 0)
        {
            bool validTrick = player.processTrick(table);
            if (!validTrick)
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
    if (mode == withOtherPlayer)
    {
        confirmMove(selectedCard, selectedTrick);
    }
    player.clearSelectedTrick();
}