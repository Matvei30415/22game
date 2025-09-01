#pragma once

#include "card.h"
#include "player.h"
#include "rules.h"
#include <string>
#include <iostream>
#include <fstream>
#include <utility>
#include <unordered_set>
#include <windows.h>

enum gameMode : short
{
    withBot = 1,
    withOtherPlayer = 2,
};

enum inputErrorCodes : short
{
    invalidInput = -1,
    invalidIndex = -2
};

void clearConsole();

short getInput(short min, short max);

short getTrickInput(std::vector<Card> &tableHand, std::vector<Card> &selectedTrick);

short getCardInput(std::vector<Card> &tableHand, std::vector<Card> &hand);

short getMenuInput(short min, short max);

void passMove();

void printLine();

void movingCursor(short i);

void printCard(Card &card);

void printCardList(std::vector<Card> &cards, short len);

void printHand(std::vector<Card> &hand, short len);

void printBotHand(std::vector<Card> &hand, short len);

void printTable(std::vector<Card> &tableHand, short len);

void printTricks(std::vector<Card> &tricks1, std::vector<Card> &tricks2);

void printResults(Player &player1, Player &player2, gameMode mode);

void printRules();

void printMenu();

void printMove(Card &selectedCard, std::vector<Card> &selectedTrick);

void confirmMove(Card &selectedCard, std::vector<Card> &selectedTrick);