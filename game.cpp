#include "game.h"

// Передать оставшиеся на столе карты, игроку, который взял последнюю взятку
void Game::processLastTrick(Table &table, Player &player1, Player &player2)
{
    if (lastTrick == player1Turn)
    {
        while (table.getTableSize() > 0)
        {
            player1.addCardToTricks(table.getCardOnTable(0));
            table.removeCardFromTable(table.getCardOnTable(0));
        }
    }
    else if (lastTrick == player2Turn)
        while (table.getTableSize() > 0)
        {
            player2.addCardToTricks(table.getCardOnTable(0));
            table.removeCardFromTable(table.getCardOnTable(0));
        }
}

// Запустить одну партию
void Game::processGame(Deck &deck, Table &table, Player &player1, Player &player2)
{
    for (short i = 0; i < deckSize; i++)
    {
        if (i % 8 == 0)
        {
            deck.dealHand(player1);
            deck.dealHand(player2);
            player1.sortHand();
            player2.sortHand();
        }
        if (turn == player1Turn)
        {
            player1.printAnnouncement();
            player1.makeMove(table, mode);
            if (player1.getIsTrick())
                lastTrick = player1Turn;
            turn = player2Turn;
        }
        else
        {
            player2.printAnnouncement();
            player2.makeMove(table, mode);
            if (player2.getIsTrick())
                lastTrick = player2Turn;
            turn = player1Turn;
        }
    }
}

// Запустить главное меню
void Game::mainMenu()
{
    short mode = inputMenu(0, 3);
    switch (mode)
    {
    case 1:
        this->mode = withBot;
        break;
    case 2:
        this->mode = withOtherPlayer;
        break;
    default:
        exit(0);
        break;
    }
}

// Запустить игру
void Game::startGame()
{
    Deck deck;
    Table table;
    HumanPlayer humanPlayer1(1);
    HumanPlayer humanPlayer2(2);
    BotPlayer botPlayer(1);
    Player *player1 = &humanPlayer1;
    Player *player2;
    if (mode == withBot)
        player2 = &botPlayer;
    else
        player2 = &humanPlayer2;
    deck.shuffle();
    processGame(deck, table, *player1, *player2);
    // std::cout << "Последняя взятка: " << lastTrick << std::endl;
    processLastTrick(table, *player1, *player2);
    (*player1).printTricks();
    (*player2).printTricks();
    (*player1).сalculatePoints();
    (*player2).сalculatePoints();
    printResults((*player1), (*player2));
    printEndGameMessage();
}

// СТРОГО ФУНКЦИИ ВВОДА-ВЫВОДА

// Печать правил
void Game::printRules() const
{
    printLine();
    std::cout << "Правила" << std::endl;
    printLine();
    std::cout.write((char *)rules_txt, rules_txt_len);
}

// Печать главного меню
void Game::printMenu() const
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
short Game::inputMenu(short min, short max) const
{
    while (true)
    {
        printMenu();
        short selectedCardIndex = input(min, max);
        if (selectedCardIndex == invalidIndex)
        {
            std::cout << "Неверный индекс, попробуйте ещё раз!" << std::endl;
        }
        else if (selectedCardIndex == invalidInput)
        {
            std::cout << "Неверный ввод, попробуйте ещё раз!" << std::endl;
        }
        else if (selectedCardIndex == 3)
        {
            printRules();
        }
        else
        {
            return selectedCardIndex;
        }
    }
}

// Печать результатов (*)
void Game::printResults(Player &player1, Player &player2) const
{
    char moreCards;
    bool moreClubs, twentyOfDiamonds, aceOfHearts;
    printLine();
    std::cout << "Результаты: Больше всего карт | Больше всего треф | Двадцатка Буби | Туз черви | Сумма |" << std::endl;
    printLine();
    player1.getPoints(moreCards, moreClubs, twentyOfDiamonds, aceOfHearts);
    std::cout << "Результаты Игрока " << std::to_string(player1.getID()) << ": ";
    std::cout << moreCards
              << moreClubs << " | "
              << twentyOfDiamonds << " | "
              << aceOfHearts << " | "
              << moreCards + moreClubs + twentyOfDiamonds + aceOfHearts << " |"
              << std::endl;
    printLine();
    player2.getPoints(moreCards, moreClubs, twentyOfDiamonds, aceOfHearts);
    if (mode == withBot)
        std::cout << "Результаты Бота " << std::to_string(player2.getID()) << ": ";
    else if (mode == withOtherPlayer)
        std::cout << "Результаты Игрока " << std::to_string(player2.getID()) << ": ";
    std::cout << moreCards
              << moreClubs << " | "
              << twentyOfDiamonds << " | "
              << aceOfHearts << " | "
              << moreCards + moreClubs + twentyOfDiamonds + aceOfHearts << " |"
              << std::endl;
    printLine();
}

void Game::printEndGameMessage() const
{
    std::cout << "Игрока окончена!" << std::endl
              << "Для выхода нажмите Enter";
    std::getchar();
}