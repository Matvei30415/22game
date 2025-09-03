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
void HumanPlayer::makeMove(Table &table, GameMode mode)
{
    table.sortCardsOnTable();
    HumanPlayer &player = *this;
    std::size_t selectedCardIndex = player.inputCard(table);
    player.setSelectedCard(hand[selectedCardIndex]);
    player.setIsTrick(false);

    // Если стол не пустой и выбранная карта - не Хантер, выбираем карты для взятки
    if (table.getTableSize() != 0 &&
        !(selectedCard.getKind() == Card::CardKind::Picture &&
          selectedCard.getPictureValue() == Card::Picture::Hunter))
    {
        // (*)
        Table tableCopy(table.getCardsOnTable());
        short selectedTrickCardIndex = 0;
        while (true)
        {
            selectedTrickCardIndex = player.inputTrick(tableCopy);
            if (selectedTrickCardIndex != invalidInput)
            {
                selectedTrick.push_back(tableCopy.getCardOnTable(selectedTrickCardIndex));
                tableCopy.removeCardFromTable(tableCopy.getCardOnTable(selectedTrickCardIndex));
            }
            else
            {
                break;
            }
        }

        if (selectedTrick.size() > 0)
        {
            bool validTrick = player.processTrick(table);
            if (!validTrick)
            {
                player.printNotValidMoveMessage();
                this->makeMove(table, mode);
                return;
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
    if (mode == withOtherPlayer)
    {
        player.printPassMoveMessage();
        player.printPriviousMoveMessage();
        player.printMove();
    }
    player.clearSelectedTrick();
}

// СТРОГО ФУНКЦИИ ВВОДА-ВЫВОДА

// Печать анонса хода
void HumanPlayer::printAnnouncement() const
{
    printLine();
    std::cout << "Ход игрока " << std::to_string(id) << std::endl;
    printLine();
}

// Печать руки
void HumanPlayer::printHand() const
{
    printLine();
    std::cout << "Ваши карты: " << std::endl;
    printCardList(hand);
    std::cout << "Выберите карту: ";
}

// Печать взяток
void HumanPlayer::printTricks() const
{
    printLine();
    std::cout << "Взятки игрока " << std::endl;
    printLine();
    printCardList(tricks);
}

// Печать сообщения о неправильном ходе
void HumanPlayer::printNotValidMoveMessage() const
{
    std::cout << "Некорректный ход!" << std::endl;
}

// Печать сообщения о передаче хода
void HumanPlayer::printPassMoveMessage() const
{
    clearConsole();
    std::cout << "Передайте ход другому игроку, затем нажмите Enter";
    std::getchar();
    clearConsole();
}

// Печать хода предыдущего игрока
void HumanPlayer::printPriviousMoveMessage() const
{

    printLine();
    std::cout << "Ход предыдущего игрока" << std::endl;
    printLine();
}

// Ввод карты с руки
short HumanPlayer::inputCard(const Table &table) const
{
    while (true)
    {
        table.printTable();
        this->printHand();
        short selectedCardIndex = input(1, hand.size());
        if (selectedCardIndex == invalidIndex)
        {
            std::cout << "Неверный индекс, попробуйте ещё раз!" << std::endl;
        }
        else if (selectedCardIndex == invalidInput)
        {
            std::cout << "Неверный ввод, попробуйте ещё раз!" << std::endl;
        }
        else
        {
            selectedCardIndex--;
            return selectedCardIndex;
        }
    }
}

// Ввод карты со стола для взятки
short HumanPlayer::inputTrick(const Table &table) const
{
    while (true)
    {
        table.printTable();
        std::cout << "Выберите карты для взятки: ";
        short selectedCardIndex = input(1, table.getTableSize());
        if (selectedCardIndex == invalidIndex)
        {
            std::cout << "Неверный индекс, попробуйте ещё раз!" << std::endl;
        }
        else if (selectedCardIndex == invalidInput)
        {
            return invalidInput;
        }
        else
        {
            selectedCardIndex--;
            return selectedCardIndex;
        }
    }
}
