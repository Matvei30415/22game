#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <string>
#include <utility>

using input_error_codes = enum {
    invalid_input = -1,
    invalid_index = -2
};

short get_move_input(short min_index, short max_index);

#endif