#pragma once

#include "card.h"
#include "consoleIO.h"
#include "table.h"
#include "player.h"



class HumanPlayer : public Player
{
public:
    HumanPlayer(short ID) : Player(ID)
    {
        name = "Игрок " + std::to_string(ID);
    }
    void makeMove(Table &table, GameMode mode) override;
    bool processTrick(Table &table);
    bool validateTrick();
    bool validateDigitalCardSum(short sum = 0, short start_index = 0);
    // Строго функции ввода-вывода
    void printAnnouncement() override;
    void printHand() override;
    void printTricks() override;
    short inputCard(Table &table);
    short inputTrick(Table &table);
    void printNotValidMove();
    void confirmMove();

private:
    // Строго функции ввода-вывода
    void passMove();
};
