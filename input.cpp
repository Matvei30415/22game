#include "input.h"

// Ввод и проверка корректности ввода
short get_move_input(short min_index, short max_index)
{
    int res = 0;
    std::string tmp;
    getline(std::cin, tmp);
    try
    {
        res = stoi(tmp);
    }
    catch (std::invalid_argument const &ex)
    {
        return invalid_input;
    }
    if (res < min_index || res > max_index)
    {
        return invalid_index;
    }
    return res;
}