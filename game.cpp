#include "game.h"

// Передача оставшихся на столе карт, игроку, который взял последнюю взятку
void processLastTrick(Turn lastTrick, Table &table, Player &player1, Player &player2)
{
    std::vector<Card> &tableHand = table.getHand();
    if (lastTrick == player1Turn)
    {
        while (tableHand.size() > 0)
        {
            player1.addCardToTricks(tableHand[0]);
            table.removeCardFromHand(tableHand[0]);
        }
    }
    else if (lastTrick == player2Turn)
        while (tableHand.size() > 0)
        {
            player2.addCardToTricks(tableHand[0]);
            table.removeCardFromHand(tableHand[0]);
        }
}

// Запуск одной партии
void processGame(Deck &deck, gameMode mode, Table &table,
                  Player &player1, Player &player2, Turn &lastTrick)
{
    Turn turn = player1Turn;
    for (short i = 0; i < deckSize; i++)
    {
        if (i % 8 == 0)
        {
            deck.dealHand(player1.getHand());
            deck.dealHand(player2.getHand());
            player1.sortHand();
            player2.sortHand();
        }
        if (turn == player1Turn)
        {
            printLine();
            std::cout << "Ход игрока 1" << std::endl;
            printLine();
            player1.makeMove(table, mode);
            if (player1.getIsTrick())
                lastTrick = player1Turn;
            turn = player2Turn;
        }
        else
        {
            switch (mode)
            {
            case withOtherPlayer:
                printLine();
                std::cout << "Ход игрока 2" << std::endl;
                printLine();
                break;
            case withBot:
                printLine();
                std::cout << "Ход бота" << std::endl;
                printLine();
                break;
            }
            player2.makeMove(table, mode);
            if (player2.getIsTrick())
                lastTrick = player2Turn;
            turn = player1Turn;
        }
        // std::cout << "Последняя взятка: " << lastTrick << std::endl;
    }
}

void startGame(gameMode mode)
{
    Turn turn = player1Turn;
    Turn lastTrick;
    Deck deck;
    Table table;
    HumanPlayer player1("Игрок 1");
    HumanPlayer humanPlayer2("Игрок 2");
    BotPlayer botPlayer("Бот");
    Player *player2;
    if (mode == withBot)
        player2 = &botPlayer;
    else
        player2 = &humanPlayer2;
    deck.shuffle();
    processGame(deck, mode, table, player1, *player2, lastTrick);
    processLastTrick(lastTrick, table, player1, (*player2));
    printTricks(player1.getTricks(), (*player2).getTricks());
    player1.сalculatePoints();
    (*player2).сalculatePoints();
    printResults(player1, (*player2), mode);
}