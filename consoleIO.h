#pragma once

#include "card.h"
#include "rules.h"
#include <string>
#include <iostream>
#include <fstream>
#include <utility>
#include <unordered_set>
#include <windows.h>

enum InputErrorCodes : short
{
    invalidInput = -1,
    invalidIndex = -2
};

void clearConsole();
short input(short min, short max);
void printLine();
void movingCursor(short i);
void printCard(Card &card);
void printCardList(std::vector<Card> &cards);