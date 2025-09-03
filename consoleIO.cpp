#include "consoleIO.h"

static const std::string line(100, '-');

// Очистка консоли
void clearConsole()
{
    system("cls");
    // std::cout << "\033[2J\033[1;1H";
}

// Перемещение курсора для печати
void moveCursor(short i)
{
    if (i == 0)
        return;
    // 11 - размер карты в терминале
    std::cout << "\033[" << 11 * i << 'C';
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
void printCard(const Card &card)
{
    printf("+--------+\n");
    printf("|%c       |\n", card.getSuit());
    printf("|        |\n");
    if (card.getType() == Card::Digital)
        if (card.getDigitalValue() == 2)
            printf("|   A    |\n");
        else if (card.getDigitalValue() > 9)
            printf("|   %hd   |\n", card.getDigitalValue());
        else
            printf("|   %hd    |\n", card.getDigitalValue());
    else
        printf("|   %c    |\n", card.getPictureValue());
    printf("|        |\n");
    printf("|       %c|\n", card.getSuit());
    printf("+--------+\n");
    printf("    %hd    \n", 1);
}

// Печать произвольного списка карт
void printCardList(const std::vector<Card> &cards)
{
    short len = cards.size();
    for (short i = 0; i < len; i++)
    {
        moveCursor(i % 10);
        printf("+--------+\n");
        moveCursor(i % 10);
        printf("|%c       |\n", cards[i].getSuit());
        moveCursor(i % 10);
        printf("|        |\n");
        moveCursor(i % 10);
        if (cards[i].getType() == Card::Digital)
            if (cards[i].getDigitalValue() == 2)
                printf("|   A    |\n");
            else if (cards[i].getDigitalValue() > 9)
                printf("|   %hd   |\n", cards[i].getDigitalValue());
            else
                printf("|   %hd    |\n", cards[i].getDigitalValue());
        else
            printf("|   %c    |\n", cards[i].getPictureValue());
        moveCursor(i % 10);
        printf("|        |\n");
        moveCursor(i % 10);
        printf("|       %c|\n", cards[i].getSuit());
        moveCursor(i % 10);
        printf("+--------+\n");
        moveCursor(i % 10);
        if (i < 9)
            printf("    %hd    \n", i + 1);
        else
            printf("    %hd   \n", i + 1);
        if ((i + 1) % 10 == 0 && i != 0 && (i + 1) != len)
            printf("\n\n\n\n\n\n\n\n");
        std::cout << "\033[8A";
    }
    std::cout << "\033[8B";
}