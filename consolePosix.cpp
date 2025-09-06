#include <iostream>

// Черновой вариант файла (Не тестировался на Linux)

void startConsole()
{
}

// Очистка консоли
void clearConsole()
{
    system("clear");
    // std::cout << "\033[2J\033[H";
}

// Перемещение курсора для печати
void moveCursorUp(int shift)
{
    if (shift == 0)
        return;
    std::cout << "\033[" << shift << 'A';
}

// Перемещение курсора для печати
void moveCursorRight(std::size_t shift)
{
    if (shift == 0)
        return;
    // 11 - размер карты в терминале
    std::cout << "\033[" << shift << 'C';
}

// Перемещение курсора для печати
void moveCursorDown(int shift)
{
    if (shift == 0)
        return;
    std::cout << "\033[" << shift << 'B';
}