#include "consoleIO.h"

static const std::string line(110, '-');

void startConsole()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
}

// Очистка консоли
void clearConsole()
{
    system("cls");
    // std::cout << "\033[2J\033[1;1H";
}

// Перемещение курсора для печати
void moveCursorUp(int shift)
{
    if (shift == 0)
        return;
    std::cout << "\033[" << shift << 'A';
}

// Перемещение курсора для печати
void moveCursorRight(std::size_t shift)
{
    if (shift == 0)
        return;
    // 11 - размер карты в терминале
    std::cout << "\033[" << shift << 'C';
}

// Перемещение курсора для печати
void moveCursorDown(int shift)
{
    if (shift == 0)
        return;
    std::cout << "\033[" << shift << 'B';
}

// Печать линии
void printLine()
{
    std::cout << line << std::endl;
}

// Произвольный ввод (от и до включительно)
short input(short min, short max)
{
    short res = 0;
    std::string tmp;
    std::getline(std::cin, tmp);
    clearConsole();
    if (tmp == "756989716978")
    {
        std::cout << "Вы стали [БОЛЬШАЯ ШИШКА]!";
        exit(0);
    }
    try
    {
        res = stoi(tmp);
    }
    catch (std::invalid_argument const &ex)
    {
        return invalidInput;
    }
    if (res < min || res > max)
    {
        return invalidIndex;
    }
    return res;
}

// Печать произвольной карты
void printCard(const Card &card, std::size_t shiftCursor, std::size_t number)
{
    char suit = (char)card.getSuit();
    moveCursorRight(shiftCursor);
    std::cout << "+--------+" << std::endl;
    moveCursorRight(shiftCursor);
    std::cout << std::format("|{}       |", suit) << std::endl;
    moveCursorRight(shiftCursor);
    std::cout << "|        |" << std::endl;
    moveCursorRight(shiftCursor);
    if (card.getKind() == Card::CardKind::Digital)
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
void printCardList(const std::vector<Card> &cards)
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