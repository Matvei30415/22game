#include "human.h"

// Проверить суммы числовых карт
bool HumanPlayer::validateDigitalCardSum(short sum, std::size_t start) const
{
    for (; start < selectedTrick.size(); start++)
    {
        if (selectedTrick[start].getKind() != Card::CardKind::Digital)
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

// Проверить корректность взятки
bool HumanPlayer::validateTrick() const
{
    short sum = 0;
    // Проверка числовых карт
    if (selectedCard.getKind() == Card::CardKind::Digital)
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
    else if ((selectedCard.getPictureValue() == Card::Picture::Gentleman &&
              (selectedTrick.size() != 1 ||
               selectedTrick[0].getPictureValue() != Card::Picture::Lady)) ||
             (selectedCard.getPictureValue() == Card::Picture::Lady &&
              (selectedTrick.size() != 1 ||
               selectedTrick[0].getPictureValue() != Card::Picture::Gentleman)))
    {
        return false;
    }
    return true;
}

// Обработать взятку
bool HumanPlayer::processTrick(Table &table)
{
    HumanPlayer &player = *this;
    bool validTrick = player.validateTrick();
    if (validTrick)
    {
        // Если ход корректный, отправляем карты во взятки
        player.addCardToTricks(selectedCard);
        player.removeCardFromHand(selectedCard);
        player.addTrickToTricks(selectedTrick);
        table.removeTrickFromTable(selectedTrick);
    }
    else
    {
        // Если ход не корректный, возвращаем карты на стол
        player.clearSelectedTrick();
    }
    return validTrick;
}

// Ход игрока
bool HumanPlayer::makeMove(Table &table, std::size_t &selectedCardIndex, std::vector<std::size_t> &selectedTrickIndexes)
{
    HumanPlayer &player = *this;
    player.setIsTrick(false);
    player.clearSelectedTrick();
    player.setSelectedCard(player.getHand()[selectedCardIndex]);
    for (std::size_t i = 0; i < selectedTrickIndexes.size(); i++)
        player.addCardToSelectedTrick(table.getCardOnTable(selectedTrickIndexes[i]));
    // Если стол не пустой и выбранная карта - не Хантер, выбираем карты для взятки
    if (table.getTableSize() != 0 &&
        !(selectedCard.getKind() == Card::CardKind::Picture &&
          selectedCard.getPictureValue() == Card::Picture::Hunter))
    {
        if (selectedTrick.size() > 0)
        {
            bool validTrick = player.processTrick(table);
            if (!validTrick)
            {
                return false;
            }
            player.setIsTrick(true);
        }
        else
        {
            table.addCardToTable(selectedCard);
            player.removeCardFromHand(selectedCard);
            player.setIsTrick(false);
        }
    }
    // Если стол пустой, выкладываем карту на стол
    else if (table.getTableSize() == 0)
    {
        table.addCardToTable(selectedCard);
        player.removeCardFromHand(selectedCard);
        player.setIsTrick(false);
    }
    // Иначе, выбранная карта = Hunter, запускаем механизм обработки
    else
    {
        player.makeHunterMove(table);
    }
    return true;
}