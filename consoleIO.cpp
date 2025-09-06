#include "consoleIO.h"
#include <iostream>
#include <string>
#include <format>
#include <algorithm>

static const std::string line(110, '-');

// Произвольный ввод (от и до включительно)
bool ConsoleView::input(std::size_t &res, std::size_t min, std::size_t max) const
{
    std::string tmp;
    std::getline(std::cin, tmp);
    clearConsole();
    if (tmp == "756989716978")
    {
        std::cout << "Вы стали [БОЛЬШАЯ ШИШКА]!";
        std::getchar();
        exit(0);
    }
    try
    {
        res = stoi(tmp);
    }
    catch (std::invalid_argument const &ex)
    {
        return false;
    }
    if (res < min || res > max)
    {
        return false;
    }
    return true;
}

// Печать линии
void ConsoleView::printLine() const
{
    std::cout << line << std::endl;
}

// Печать произвольной карты
void ConsoleView::printCard(const Card &card, std::size_t shiftCursor, std::size_t number) const
{
    char suit = (char)card.getSuit();
    moveCursorRight(shiftCursor);
    std::cout << "+--------+" << std::endl;
    moveCursorRight(shiftCursor);
    std::cout << std::format("|{}       |", suit) << std::endl;
    moveCursorRight(shiftCursor);
    std::cout << "|        |" << std::endl;
    moveCursorRight(shiftCursor);
    if (card.getKind() == Card::Kind::Digital)
    {
        int value = card.getDigitalValue();
        if (value == 2)
            std::cout << "|   A    |" << std::endl;
        else if (value > 9)
            std::cout << std::format("|   {}   |", value) << std::endl;
        else
            std::cout << std::format("|   {}    |", value) << std::endl;
    }
    else
    {
        char value = (char)card.getPictureValue();
        std::cout << std::format("|   {}    |", value) << std::endl;
    }
    moveCursorRight(shiftCursor);
    std::cout << "|        |" << std::endl;
    moveCursorRight(shiftCursor);
    std::cout << std::format("|       {}|", suit) << std::endl;
    moveCursorRight(shiftCursor);
    std::cout << "+--------+" << std::endl;
    moveCursorRight(shiftCursor);
    if (number < 9)
        std::cout << std::format("    {}    ", number) << std::endl;
    else
        std::cout << std::format("    {}   ", number) << std::endl;
}

// Печать произвольного списка карт
void ConsoleView::printCardList(const std::vector<Card> &cards) const
{
    std::size_t len = cards.size();
    for (std::size_t i = 0; i < len; i++)
    {
        printCard(cards[i], i % 10 * 11, i + 1);
        if ((i + 1) % 10 == 0 && i != 0 && (i + 1) != len)
            std::cout << "\n\n\n\n\n\n\n\n";
        moveCursorUp(8);
    }
    moveCursorDown(8);
}

// Печать карт на столе
void ConsoleView::printTable(const Table &table) const
{
    if (table.getTableSize() == 0)
    {
        std::cout << "Стол пуст!" << std::endl;
        return;
    }
    else
    {
        std::cout << "Карты на столе: " << std::endl;
    }
    printCardList(table.getCardsOnTable());
}

// Печать выбранной карты
void ConsoleView::printSelectedCard(const Player &player) const
{
    printCard(player.getSelectedCard());
}

// Печать хода
void ConsoleView::printMove(const Player &player) const
{
    std::size_t size = player.getSelectedTrick().size();
    printSelectedCard(player);
    if (size != 0)
        printCardList(player.getSelectedTrick());
}

// Печать анонса хода
void ConsoleView::printAnnouncement(const Player &player) const
{
    printLine();
    if (player.getTypeName() == "Bot")
        std::cout << "Ход бота " << std::to_string(player.getID()) << std::endl;
    else if (player.getTypeName() == "Human")
        std::cout << "Ход игрока " << std::to_string(player.getID()) << std::endl;
    printLine();
}

// Печать руки
void ConsoleView::printHand(const Player &player) const
{
    printLine();
    if (player.getTypeName() == "Bot")
        std::cout << "Карты бота: " << std::endl;
    else if (player.getTypeName() == "Human")
        std::cout << "Ваши карты: " << std::endl;
    printCardList(player.getHand());
}

// Печать взяток
void ConsoleView::printTricks(const Player &player) const
{
    printLine();
    if (player.getTypeName() == "Bot")
        std::cout << "Взятки бота " << std::to_string(player.getID()) << ":" << std::endl;
    else if (player.getTypeName() == "Human")
        std::cout << "Взятки игрока " << std::to_string(player.getID()) << ":" << std::endl;
    printLine();
    printCardList(player.getTricks());
}

// Печать сообщения о неправильном ходе
void ConsoleView::printNotValidMoveMessage() const
{
    std::cout << "Некорректный ход!" << std::endl;
}

// Печать сообщения о передаче хода
void ConsoleView::printPassMoveMessage() const
{
    clearConsole();
    std::cout << "Передайте ход другому игроку, затем нажмите Enter";
    std::getchar();
    clearConsole();
}

// Печать хода предыдущего игрока
void ConsoleView::printPreviousMoveMessage() const
{

    printLine();
    std::cout << "Ход предыдущего игрока" << std::endl;
    printLine();
}

// Печать выбора
void ConsoleView::printSelection(const std::vector<std::size_t> &selectedTrickIndexes, const std::size_t tableSize) const
{
    bool flag = false;
    for (std::size_t i = 0; i < tableSize; i++)
    {
        for (std::size_t j = 0; j < selectedTrickIndexes.size(); j++)
        {
            if (selectedTrickIndexes[j] == i)
            {
                std::cout << "    ✓      ";
                flag = true;
            }
            else if (selectedTrickIndexes[j] > i)
            {
                if (!flag)
                    std::cout << "           ";
                flag = false;
                break;
            }
        }
    }
    std::cout << std::endl;
}

// Ввод карты с руки
std::size_t ConsoleView::inputCard(const Player &human, const Table &table) const
{
    std::size_t selectedCardIndex;
    while (true)
    {
        printTable(table);
        printHand(human);
        std::cout << "Выберите карту: ";
        bool successInput = input(selectedCardIndex, 1, human.getHand().size());
        if (!successInput)
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
std::vector<std::size_t> ConsoleView::inputTrick(const Table &table) const
{
    std::size_t tableSize;
    std::size_t selectedCardIndex;
    std::vector<std::size_t> selectedTrickIndexes;
    while (true)
    {
        tableSize = table.getTableSize();
        std::sort(selectedTrickIndexes.begin(), selectedTrickIndexes.end());
        printTable(table);
        printSelection(selectedTrickIndexes, tableSize);
        std::cout << "Выберите карты для взятки: ";
        bool successInput = input(selectedCardIndex, 1, tableSize);
        if (!successInput)
        {
            return selectedTrickIndexes;
        }
        else
        {
            selectedCardIndex--;
            for (size_t i = 0; i < selectedTrickIndexes.size(); i++)
            {
                if (selectedCardIndex == selectedTrickIndexes[i])
                {
                    selectedTrickIndexes.erase(begin(selectedTrickIndexes) + i);
                    successInput = false;
                    break;
                }
            }
            if (successInput)
                selectedTrickIndexes.push_back(selectedCardIndex);
        }
    }
}

// Печать правил
void ConsoleView::printRules() const
{
    printLine();
    std::cout << "Правила" << std::endl;
    printLine();
    std::cout.write((char *)rules_txt, rules_txt_len);
    std::cout << "Для возврата в меню нажмите Enter";
    std::getchar();
}

// Печать главного меню
void ConsoleView::printMenu() const
{
    printLine();
    std::cout << "22game" << std::endl;
    printLine();
    std::cout << "Главное меню" << std::endl;
    printLine();
    std::cout << "1. Начать игру с ботом" << std::endl;
    std::cout << "2. Начать игру с другим игроком (локально)" << std::endl;
    std::cout << "3. Правила" << std::endl;
    std::cout << "0. Выход" << std::endl;
    std::cout << "Выберите пункт меню: ";
}

// Ввод пунктов меню
std::size_t ConsoleView::inputMenu(std::size_t min, std::size_t max) const
{
    std::size_t selectedCardIndex;
    while (true)
    {
        printMenu();
        bool successInput = input(selectedCardIndex, min, max);
        if (!successInput)
        {
            std::cout << "Неверный ввод, попробуйте ещё раз!" << std::endl;
        }
        else
        {
            if (selectedCardIndex == 3)
            {
                printRules();
            }
            else
            {
                return selectedCardIndex;
            }
        }
    }
}

// Печать результатов (*)
void ConsoleView::printResults(const Player &player1, const Player &player2) const
{
    short moreCards, moreClubs, twentyOfDiamonds, aceOfHearts;
    printLine();
    std::cout << "Результаты: Больше всего карт | Больше всего треф | Двадцатка Буби | Туз черви | Сумма |" << std::endl;
    printLine();
    player1.getPoints(moreCards, moreClubs, twentyOfDiamonds, aceOfHearts);
    std::cout << "Результаты Игрока " << std::to_string(player1.getID()) << ": ";
    std::cout << moreCards << " | "
              << moreClubs << " | "
              << twentyOfDiamonds << " | "
              << aceOfHearts << " | "
              << moreCards + moreClubs + twentyOfDiamonds + aceOfHearts << " |"
              << std::endl;
    printLine();
    player2.getPoints(moreCards, moreClubs, twentyOfDiamonds, aceOfHearts);
    if (player2.getTypeName() == "Bot")
        std::cout << "Результаты Бота " << std::to_string(player2.getID()) << ": ";
    else if (player2.getTypeName() == "Human")
        std::cout << "Результаты Игрока " << std::to_string(player2.getID()) << ": ";
    std::cout << moreCards << " | "
              << moreClubs << " | "
              << twentyOfDiamonds << " | "
              << aceOfHearts << " | "
              << moreCards + moreClubs + twentyOfDiamonds + aceOfHearts << " |"
              << std::endl;
    printLine();
}

void ConsoleView::printEndGameMessage() const
{
    std::cout << "Игрока окончена!" << std::endl;
}

void ConsoleView::printEndGameConfirm() const
{
    std::cout << "Для выхода нажмите Enter" << std::endl;
    std::getchar();
}