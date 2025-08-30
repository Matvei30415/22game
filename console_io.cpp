#include "console_io.h"

static const std::string line(100, '-');

// Очистка консоли
void clear_console()
{
    // system("cls");
    std::cout << "\033[2J\033[1;1H";
}

// Ввод и проверка корректности ввода
short get_move_input(short min_index, short max_index)
{
    int res = 0;
    std::string tmp;
    std::getline(std::cin, tmp);
    clear_console();
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

// Передача хода
void pass_move()
{
    std::string tmp;
    clear_console();
    std::cout << "Передайте ход другому игроку, затем нажмите Enter";
    std::getline(std::cin, tmp);
    clear_console();
}

// Печать линии
void print_line()
{
    std::cout << line << std::endl;
}

// Перемещение курсора для печати
void moving_cursor(short i)
{
    if (i == 0)
        return;
    std::cout << "\033[" << 11 * i << 'C';
}

// Печать карты
void print_card(Card &current_card)
{
    printf("+--------+\n");
    printf("|%c       |\n", current_card.getSuit());
    printf("|        |\n");
    if (current_card.getType() == Card::Digital)
        if (current_card.getDigitalValue() == 2)
            printf("|   A    |\n");
        else if (current_card.getDigitalValue() > 9)
            printf("|   %hd   |\n", current_card.getDigitalValue());
        else
            printf("|   %hd    |\n", current_card.getDigitalValue());
    else
        printf("|   %c    |\n", current_card.getPictureValue());
    printf("|        |\n");
    printf("|       %c|\n", current_card.getSuit());
    printf("+--------+\n");
    printf("    %hd    \n", 1);
}

// Печать карт (произовольная)
void print_card_list(CardList &current_cards, short len)
{
    for (short i = 0; i < len; i++)
    {
        moving_cursor(i % 10);
        printf("+--------+\n");
        moving_cursor(i % 10);
        printf("|%c       |\n", current_cards[i].getSuit());
        moving_cursor(i % 10);
        printf("|        |\n");
        moving_cursor(i % 10);
        if (current_cards[i].getType() == Card::Digital)
            if (current_cards[i].getDigitalValue() == 2)
                printf("|   A    |\n");
            else if (current_cards[i].getDigitalValue() > 9)
                printf("|   %hd   |\n", current_cards[i].getDigitalValue());
            else
                printf("|   %hd    |\n", current_cards[i].getDigitalValue());
        else
            printf("|   %c    |\n", current_cards[i].getPictureValue());
        moving_cursor(i % 10);
        printf("|        |\n");
        moving_cursor(i % 10);
        printf("|       %c|\n", current_cards[i].getSuit());
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
void print_hand(CardList &current_cards, short len)
{
    print_line();
    std::cout << "Ваши карты: " << std::endl;
    print_card_list(current_cards, len);
    std::cout << "Выберите карту: ";
}

// Вывод руки бота (для отладки)
void print_bot_hand(CardList &current_cards, short len)
{
    print_line();
    std::cout << "Карты бота: " << std::endl;
    print_card_list(current_cards, len);
}

// Вывод стола
void print_table(CardList &current_cards, short len)
{
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
void print_tricks(CardList &player_1_tricks, CardList &player_2_tricks)
{
    print_line();
    std::cout << "Взятки игрока " << std::endl;
    print_line();
    print_card_list(player_1_tricks, player_1_tricks.size());
    print_line();
    std::cout << "Взятки бота " << std::endl;
    print_line();
    print_card_list(player_2_tricks, player_2_tricks.size());
}

// Печать результатов
void print_results(Points &player_1_results, Points &player_2_results, game_mode mode)
{
    char more_cards;
    bool more_clubs, twenty_of_diamons, ace_of_hearts;
    print_line();
    std::cout << "Результаты: Больше всего карт | Больше всего треф | Двадцатка Буби | Туз черви | Сумма" << std::endl;
    print_line();
    player_1_results.get_points(more_cards, more_clubs, twenty_of_diamons, ace_of_hearts);
    if (mode == with_bot)
        std::cout << "Результаты Игрока: ";
    else if (mode == with_other_player)
        std::cout << "Результаты Игрока 1: ";
    std::cout << (short)more_cards << " | "
              << more_clubs << " | "
              << twenty_of_diamons << " | "
              << ace_of_hearts << " | "
              << (short)more_cards + more_clubs + twenty_of_diamons + ace_of_hearts
              << std::endl;
    print_line();
    player_2_results.get_points(more_cards, more_clubs, twenty_of_diamons, ace_of_hearts);
    if (mode == with_bot)
        std::cout << "Результаты Бота: ";
    else if (mode == with_other_player)
        std::cout << "Результаты Игрока 2: ";
    std::cout << (short)more_cards << " | "
              << more_clubs << " | "
              << twenty_of_diamons << " | "
              << ace_of_hearts << " | "
              << (short)more_cards + more_clubs + twenty_of_diamons + ace_of_hearts
              << std::endl;
}

// Печать правил
void print_rules()
{
    std::string rule_str;
    std::ifstream ifs("rules.txt");
    if (!(ifs.is_open()))
    {
        std::cout << "Ошибка при открытии правил" << std::endl;
        return;
    }
    print_line();
    std::cout << "Правила" << std::endl;
    print_line();
    while (std::getline(ifs, rule_str))
        std::cout << rule_str << std::endl;
    ifs.close();
}

// Печать главного меню
void print_menu()
{
    print_line();
    std::cout << "22game" << std::endl;
    print_line();
    std::cout << "Главное меню" << std::endl;
    print_line();
    std::cout << "1. Начать игру с ботом" << std::endl;
    std::cout << "2. Начать игру с другим игроком (локально)" << std::endl;
    std::cout << "3. Правила" << std::endl;
    std::cout << "0. Выход" << std::endl;
    std::cout << "Выберите пункт меню: ";
}

// Печать хода
void print_move(Card &selected_card, CardList &selected_cards)
{
    short size = selected_cards.size();
    print_card(selected_card);
    if (size != 0)
        print_card_list(selected_cards, size);
}

// Подтверждение хода
void confirm_move(Card &selected_card, CardList &selected_cards)
{
    pass_move();
    print_line();
    std::cout << "Ход предыдущего игрока" << std::endl;
    print_line();
    print_move(selected_card, selected_cards);
}