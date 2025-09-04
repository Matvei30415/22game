#pragma once

#include "card.h"
#include "rules.h"
#include "table.h"
#include "player.h"
#include <string>
#include <iostream>
#include <format>


void startConsole();
void clearConsole();
void moveCursorUp(int shift);
void moveCursorRight(std::size_t shift);
void moveCursorDown(int shift);
class ConsoleView
{
public:
    bool input(std::size_t &res, std::size_t min, std::size_t max) const;
    void printLine() const;
    void printCard(const Card &card, std::size_t shiftCursor = 0, std::size_t number = 1) const;
    void printCardList(const std::vector<Card> &cards) const;
    void printTable(const Table &table) const;
    void printSelectedCard(const Player &player) const;
    void printMove(const Player &player) const;
    void printAnnouncement(const Player &player) const;
    void printHand(const Player &player) const;
    void printTricks(const Player &player) const;
    void printSelection(const std::vector<std::size_t> &selectedTrickIndexes, const std::size_t tableSize) const;
    std::size_t inputCard(const Player &human, const Table &table) const;
    std::vector<std::size_t> inputTrick(const Table &table) const;
    void printNotValidMoveMessage() const;
    void printPriviousMoveMessage() const;
    void printPassMoveMessage() const;
    void printResults(const Player &player1, const Player &player2) const;
    void printRules() const;
    void printMenu() const;
    void printEndGameMessage() const;
    std::size_t inputMenu(std::size_t min, std::size_t max) const;
};
