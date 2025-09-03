#pragma once

#include "card.h"
#include "rules.h"
#include <string>
#include <iostream>
#include <format>
#include <windows.h>

enum InputErrorCodes : short
{
    invalidInput = -1,
    invalidIndex = -2
};

void startConsole();
void clearConsole();
void moveCursorUp(int shift);
void moveCursorRight(std::size_t shift);
void moveCursorDown(int shift);
short input(short min, short max);
void printLine();
void printCard(const Card &card, std::size_t shiftCursor = 0, std::size_t number = 1);
void printCardList(const std::vector<Card> &cards);