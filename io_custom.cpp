#include "io_custom.h"

// Ввод и проверка корректности ввода
short get_move_input(short min_index, short max_index)
{
    int res = 0;
    std::string tmp;
    std::getline(std::cin, tmp);
    std::cout << "\033[2J\033[1;1H";
    if (tmp == "756989716978")
    {
        std::cout << "Вы стали [БОЛЬШАЯ ШИШКА]!";
        exit(0);
    }
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

// Перемещение курсора для печати
void moving_cursor(short i)
{
    if (i == 0)
        return;
    std::cout << "\033[" << 11 * i << 'C';
}

// Печать карт (произовольная)
void print_card_list(std::vector<card> &current_cards, short len)
{
    for (short i = 0; i < len; i++)
    {
        moving_cursor(i % 10);
        printf("+--------+\n");
        moving_cursor(i % 10);
        printf("|%c       |\n", current_cards[i].suit);
        moving_cursor(i % 10);
        printf("|        |\n");
        moving_cursor(i % 10);
        if (current_cards[i].type == digital_card)
            if (current_cards[i].value.digital_cards == 2)
                printf("|   A    |\n");
            else if (current_cards[i].value.digital_cards > 9)
                printf("|   %hd   |\n", current_cards[i].value.digital_cards);
            else
                printf("|   %hd    |\n", current_cards[i].value.digital_cards);
        else
            printf("|   %c    |\n", current_cards[i].value.picture_cards);
        moving_cursor(i % 10);
        printf("|        |\n");
        moving_cursor(i % 10);
        printf("|       %c|\n", current_cards[i].suit);
        moving_cursor(i % 10);
        printf("+--------+\n");
        moving_cursor(i % 10);
        if (i < 9)
            printf("    %hd    \n", i + 1);
        else
            printf("    %hd   \n", i + 1);
        if ((i + 1) % 10 == 0 && i != 0 && (i + 1) != len)
            printf("\n\n\n\n\n\n\n\n");
        std::cout << "\033[8A";
    }
    std::cout << "\033[8B";
}

// Вывод руки
void print_hand(std::vector<card> &current_cards, short len)
{
    std::cout << line << std::endl;
    std::cout << "Ваши карты: " << std::endl;
    print_card_list(current_cards, len);
    std::cout << "Выберите карту: ";
}

// Вывод руки бота (для отладки)
void print_bot_hand(std::vector<card> &current_cards, short len)
{
    std::cout << line << std::endl;
    std::cout << "Карты бота: " << std::endl;
    print_card_list(current_cards, len);
}

// Вывод стола
void print_table(std::vector<card> &current_cards, short len)
{

    std::cout << line << std::endl;
    if (len == 0)
    {
        std::cout << "Стол пуст!" << std::endl;
        return;
    }
    else
    {
        std::cout << "Карты на столе: " << std::endl;
    }
    print_card_list(current_cards, len);
}

// Печать взяток (только для отладки)
void print_tricks(std::vector<card> &player_1_tricks, std::vector<card> &player_2_tricks)
{
    std::cout << line << std::endl;
    std::cout << "Взятки игрока " << std::endl;
    std::cout << line << std::endl;
    print_card_list(player_1_tricks, player_1_tricks.size());
    std::cout << line << std::endl;
    std::cout << "Взятки бота " << std::endl;
    std::cout << line << std::endl;
    print_card_list(player_2_tricks, player_2_tricks.size());
}

// Печать результатов
void print_results(points &player_1_results, points &player_2_results)
{
    std::cout << line << std::endl;
    std::cout << "Результаты: Больше всего карт | Больше всего треф | Двадцатка Буби | Туз черви | Сумма" << std::endl;
    std::cout << line << std::endl;
    std::cout << "Результаты Игрока: "
              << (short)player_1_results.get_more_cards << " | "
              << player_1_results.get_more_clubs << " | "
              << player_1_results.get_twenty_of_diamonds << " | "
              << player_1_results.get_ace_of_hearts << " | "
              << (short)player_1_results.get_more_cards + player_1_results.get_more_clubs +
                     player_1_results.get_twenty_of_diamonds + player_1_results.get_ace_of_hearts
              << std::endl;
    std::cout << line << std::endl;
    std::cout << "Результаты Бота: "
              << (short)player_2_results.get_more_cards << " | "
              << player_2_results.get_more_clubs << " | "
              << player_2_results.get_twenty_of_diamonds << " | "
              << player_2_results.get_ace_of_hearts << " | "
              << (short)player_2_results.get_more_cards + player_2_results.get_more_clubs +
                     player_2_results.get_twenty_of_diamonds + player_2_results.get_ace_of_hearts
              << std::endl;
}

void print_rules()
{
    std::string rule_str;
    std::ifstream ifs("rules.txt");
    if (!(ifs.is_open()))
    {
        std::cout << "Ошибка при открытии правил" << std::endl;
        return;
    }
    std::cout << line << std::endl;
    std::cout << "Правила" << std::endl;
    std::cout << line << std::endl;
    while (std::getline(ifs, rule_str))
        std::cout << rule_str << std::endl;
    ifs.close();
}

void print_menu()
{
    std::cout << line << std::endl;
    std::cout << "22game" << std::endl;
    std::cout << line << std::endl;
    std::cout << "Главное меню" << std::endl;
    std::cout << line << std::endl;
    std::cout << "1. Начать игру с ботом" << std::endl;
    std::cout << "2. Начать игру с другим игроком (локально)" << std::endl;
    std::cout << "3. Правила" << std::endl;
    std::cout << "0. Выход" << std::endl;
    std::cout << "Выберите пункт меню: ";
}