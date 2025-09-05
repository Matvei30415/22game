#include "game.h"

// Передать оставшиеся на столе карты, игроку, который взял последнюю взятку
void Game::processLastTrick(Table &table, Player &player1, Player &player2)
{
    if (lastTrick == Game::Turn::player1)
    {
        while (table.getTableSize() > 0)
        {
            player1.addCardToTricks(table.getCardOnTable(0));
            table.removeCardFromTable(table.getCardOnTable(0));
        }
    }
    else if (lastTrick == Game::Turn::player2)
        while (table.getTableSize() > 0)
        {
            player2.addCardToTricks(table.getCardOnTable(0));
            table.removeCardFromTable(table.getCardOnTable(0));
        }
}

// Запустить одну партию
void Game::processGame(ConsoleView &view, Deck &deck, Table &table, Player &player1, Player &player2)
{
    Player *player = &player1;
    std::size_t selectedCardIndex;
    std::vector<std::size_t> selectedTrickIndexes;
    bool successMove = true;
    for (std::size_t i = 0; i < kDeckSize; i++)
    {
        if (i % 8 == 0 && successMove)
        {
            deck.dealHand(player1);
            deck.dealHand(player2);
            player1.sortHand();
            player2.sortHand();
        }
        table.sortCardsOnTable();

        if (turn == Game::Turn::player1 || (turn == Game::Turn::player2 && mode == Game::Mode::withOtherPlayer))
        {
            view.printAnnouncement(*player);
            // view.printHand(player2); // Печать руки бота (для отладки)
            selectedCardIndex = view.inputCard(*player, table);
            if (table.getTableSize() != 0 &&
                !((*player).getHand()[selectedCardIndex].getKind() == Card::Kind::Picture &&
                  (*player).getHand()[selectedCardIndex].getPictureValue() == Card::Picture::Hunter))
            {
                selectedTrickIndexes = view.inputTrick(table);
            }
            static_cast<HumanPlayer*>(player)->preMoveActions(table, selectedCardIndex, selectedTrickIndexes);
            successMove = (*player).makeMove(table);
            if (!successMove)
            {
                view.printNotValidMoveMessage();
                i--;
                continue;
            }
            if (mode == Game::Mode::withOtherPlayer)
            {
                view.printPassMoveMessage();
                view.printPreviousMoveMessage();
                view.printMove(*player);
            }
        }
        else if (turn == Game::Turn::player2 && mode == Game::Mode::withBot)
        {
            view.printAnnouncement((*player));
            static_cast<BotPlayer*>(player)->preMoveActions(player1.getHand(), deck.getDeckCards());
            successMove = (*player).makeMove(table);
            view.printMove((*player));
        }
        if (turn == Game::Turn::player1)
        {
            if ((*player).getIsTrick())
                lastTrick = Game::Turn::player1;
            turn = Game::Turn::player2;
            player = &player2;
        }
        else
        {
            if ((*player).getIsTrick())
                lastTrick = Game::Turn::player2;
            turn = Game::Turn::player1;
            player = &player1;
        }
    }
}

// Запустить главное меню
void Game::mainMenu(ConsoleView &view)
{
    std::size_t mode = view.inputMenu(0, 3);
    switch (mode)
    {
    case 1:
        this->mode = Game::Mode::withBot;
        break;
    case 2:
        this->mode = Game::Mode::withOtherPlayer;
        break;
    default:
        exit(0);
        break;
    }
}

// Запустить игру
void Game::startGame(ConsoleView &view)
{
    Deck deck;
    Table table;
    HumanPlayer humanPlayer1(1);
    HumanPlayer humanPlayer2(2);
    BotPlayer botPlayer(1);
    Player *player1 = &humanPlayer1;
    Player *player2;
    if (mode == Game::Mode::withBot)
        player2 = &botPlayer;
    else
        player2 = &humanPlayer2;
    deck.shuffle();
    processGame(view, deck, table, *player1, *player2);
    // std::cout << "Последняя взятка: " << lastTrick << std::endl;
    processLastTrick(table, *player1, *player2);
    view.printTricks(*player1);
    view.printTricks(*player2);
    (*player1).calculatePoints();
    (*player2).calculatePoints();
    view.printEndGameMessage();
    view.printResults((*player1), (*player2));
    view.printEndGameConfirm();
}