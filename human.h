#pragma once

#include "card.h"
#include "consoleIO.h"
#include "table.h"
#include "player.h"

class HumanPlayer : public Player
{
public:
    HumanPlayer(short id) : Player(id)
    {
        name = "Игрок " + std::to_string(id);
    }
    void makeMove(Table &table, GameMode mode) override;
    bool processTrick(Table &table);
    bool validateTrick() const;
    bool validateDigitalCardSum(short sum = 0, std::size_t start = 0) const;

    // Строго функции ввода-вывода
public:
    void printAnnouncement() const override;
    void printHand() const override;
    void printTricks() const override;

private:
    short inputCard(const Table &table) const;
    short inputTrick(const Table &table) const;
    void printNotValidMoveMessage() const;
    void printPriviousMoveMessage() const;
    void printPassMoveMessage() const;
};
