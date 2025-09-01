#include "consoleIO.h"

static const std::string line(100, '-');

// Очистка консоли
void clearConsole()
{
    system("cls");
    // std::cout << "\033[2J\033[1;1H";
}

// Ввод и проверка корректности ввода
short getInput(short min, short max)
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

short getTrickInput(std::vector<Card> &tableHand, std::vector<Card> &selectedTrick)
{
    printTable(tableHand, tableHand.size());
    std::cout << "Выберите карты для взятки: ";
    short selectedCardIndex = getInput(1, tableHand.size());
    if (selectedCardIndex == invalidIndex)
    {
        std::cout << "Неверный индекс, попробуйте ещё раз!" << std::endl;
        return getTrickInput(tableHand, selectedTrick);
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

short getCardInput(std::vector<Card> &tableHand, std::vector<Card> &hand)
{
    printTable(tableHand, tableHand.size());
    printHand(hand, hand.size());
    short selectedCardIndex = getInput(1, hand.size());
    if (selectedCardIndex == invalidIndex)
    {
        std::cout << "Неверный индекс, попробуйте ещё раз!" << std::endl;
        return getCardInput(tableHand, hand);
    }
    else if (selectedCardIndex == invalidInput)
    {
        std::cout << "Неверный ввод, попробуйте ещё раз!" << std::endl;
        return getCardInput(tableHand, hand);
    }
    else
    {
        selectedCardIndex--;
        return selectedCardIndex;
    }
}

short getMenuInput(short min, short max)
{
    printMenu();
    short selectedCardIndex = getInput(min, max);
    if (selectedCardIndex == invalidIndex)
    {
        std::cout << "Неверный индекс, попробуйте ещё раз!" << std::endl;
        return getMenuInput(min, max);
    }
    else if (selectedCardIndex == invalidInput)
    {
        std::cout << "Неверный ввод, попробуйте ещё раз!" << std::endl;
        return getMenuInput(min, max);
    }
    else if (selectedCardIndex == 3)
    {
        printRules();
        return getMenuInput(min, max);
    }
    else
    {
        return selectedCardIndex;
    }
}

// Передача хода
void passMove()
{
    std::string tmp;
    clearConsole();
    std::cout << "Передайте ход другому игроку, затем нажмите Enter";
    std::getline(std::cin, tmp);
    clearConsole();
}

// Печать линии
void printLine()
{
    std::cout << line << std::endl;
}

// Перемещение курсора для печати
void movingCursor(short i)
{
    if (i == 0)
        return;
    std::cout << "\033[" << 11 * i << 'C';
}

// Печать карты
void printCard(Card &card)
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

// Печать карт (произовольная)
void printCardList(std::vector<Card> &cards, short len)
{
    for (short i = 0; i < len; i++)
    {
        movingCursor(i % 10);
        printf("+--------+\n");
        movingCursor(i % 10);
        printf("|%c       |\n", cards[i].getSuit());
        movingCursor(i % 10);
        printf("|        |\n");
        movingCursor(i % 10);
        if (cards[i].getType() == Card::Digital)
            if (cards[i].getDigitalValue() == 2)
                printf("|   A    |\n");
            else if (cards[i].getDigitalValue() > 9)
                printf("|   %hd   |\n", cards[i].getDigitalValue());
            else
                printf("|   %hd    |\n", cards[i].getDigitalValue());
        else
            printf("|   %c    |\n", cards[i].getPictureValue());
        movingCursor(i % 10);
        printf("|        |\n");
        movingCursor(i % 10);
        printf("|       %c|\n", cards[i].getSuit());
        movingCursor(i % 10);
        printf("+--------+\n");
        movingCursor(i % 10);
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

// Вывод руки
void printHand(std::vector<Card> &hand, short len)
{
    printLine();
    std::cout << "Ваши карты: " << std::endl;
    printCardList(hand, len);
    std::cout << "Выберите карту: ";
}

// Вывод руки бота (для отладки)
void printBotHand(std::vector<Card> &hand, short len)
{
    printLine();
    std::cout << "Карты бота: " << std::endl;
    printCardList(hand, len);
}

// Вывод стола
void printTable(std::vector<Card> &tableHand, short len)
{
    if (len == 0)
    {
        std::cout << "Стол пуст!" << std::endl;
        return;
    }
    else
    {
        std::cout << "Карты на столе: " << std::endl;
    }
    printCardList(tableHand, len);
}

// Печать взяток (только для отладки)
void printTricks(std::vector<Card> &tricks1, std::vector<Card> &tricks2)
{
    printLine();
    std::cout << "Взятки игрока " << std::endl;
    printLine();
    printCardList(tricks1, tricks1.size());
    printLine();
    std::cout << "Взятки бота " << std::endl;
    printLine();
    printCardList(tricks2, tricks2.size());
}

// Печать результатов
void printResults(Player &player1, Player &player2, gameMode mode)
{
    char moreCards;
    bool moreClubs, twentyOfDiamonds, aceOfHearts;
    printLine();
    std::cout << "Результаты: Больше всего карт | Больше всего треф | Двадцатка Буби | Туз черви | Сумма" << std::endl;
    printLine();
    player1.getPoints(moreCards, moreClubs, twentyOfDiamonds, aceOfHearts);
    if (mode == withBot)
        std::cout << "Результаты Игрока: ";
    else if (mode == withOtherPlayer)
        std::cout << "Результаты Игрока 1: ";
    std::cout << (short)moreCards << " | "
              << moreClubs << " | "
              << twentyOfDiamonds << " | "
              << aceOfHearts << " | "
              << (short)moreCards + moreClubs + twentyOfDiamonds + aceOfHearts
              << std::endl;
    printLine();
    player2.getPoints(moreCards, moreClubs, twentyOfDiamonds, aceOfHearts);
    if (mode == withBot)
        std::cout << "Результаты Бота: ";
    else if (mode == withOtherPlayer)
        std::cout << "Результаты Игрока 2: ";
    std::cout << (short)moreCards << " | "
              << moreClubs << " | "
              << twentyOfDiamonds << " | "
              << aceOfHearts << " | "
              << (short)moreCards + moreClubs + twentyOfDiamonds + aceOfHearts
              << std::endl;
}

// Печать правил
void printRules()
{
    printLine();
    std::cout << "Правила" << std::endl;
    printLine();
    std::cout.write((char*)rules_txt, rules_txt_len);
}

// Печать главного меню
void printMenu()
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

// Печать хода
void printMove(Card &selectedCard, std::vector<Card> &selectedTrick)
{
    short size = selectedTrick.size();
    printCard(selectedCard);
    if (size != 0)
        printCardList(selectedTrick, size);
}

// Подтверждение хода
void confirmMove(Card &selectedCard, std::vector<Card> &selectedTrick)
{
    passMove();
    printLine();
    std::cout << "Ход предыдущего игрока" << std::endl;
    printLine();
    printMove(selectedCard, selectedTrick);
}