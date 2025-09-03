#pragma once

#include "card.h"
#include "rules.h"
#include <string>
#include <iostream>
#include <windows.h>

enum InputErrorCodes : short
{
    invalidInput = -1,
    invalidIndex = -2
};

void clearConsole();
void moveCursor(short i);
short input(short min, short max);
void printLine();
void printCard(const Card &card);
void printCardList(const std::vector<Card> &cards);