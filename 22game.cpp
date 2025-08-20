#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>

using input_error_codes = enum {
    invalid_input = -1,
    invalid_index = -2
};

using turns = enum {
    player_1 = 1,
    player_2 = 2
};

enum
{
    deck_size = 48,
    cards_in_hand = 4,
};

using type_denomination = enum {
    digital_card,
    picture_card
};

using denomination = union
{
    short digital_cards;
    char picture_cards;
};

struct card
{
    type_denomination type;
    denomination value;
    char suit;
    double quality;
};

using card_list = std::vector<card>;

struct points
{
    char get_more_cards;
    bool get_more_clubs;
    bool get_twenty_of_diamonds;
    bool get_ace_of_hearts;
};

bool is_trick = false;
const std::string line(100, '-');
const card deck_of_cards[deck_size] = {
    {.type = digital_card, {.digital_cards = 4}, .suit = 'G', .quality = 11.0 / 264.0},
    {.type = digital_card, {.digital_cards = 6}, .suit = 'G', .quality = 11.0 / 264.0},
    {.type = digital_card, {.digital_cards = 8}, .suit = 'G', .quality = 11.0 / 264.0},
    {.type = digital_card, {.digital_cards = 10}, .suit = 'G', .quality = 11.0 / 264.0},
    {.type = digital_card, {.digital_cards = 12}, .suit = 'G', .quality = 11.0 / 264.0},
    {.type = digital_card, {.digital_cards = 14}, .suit = 'G', .quality = 11.0 / 264.0},
    {.type = digital_card, {.digital_cards = 16}, .suit = 'G', .quality = 11.0 / 264.0},
    {.type = digital_card, {.digital_cards = 18}, .suit = 'G', .quality = 11.0 / 264.0},
    {.type = digital_card, {.digital_cards = 4}, .suit = 'G', .quality = 11.0 / 264.0},
    {.type = digital_card, {.digital_cards = 6}, .suit = 'G', .quality = 11.0 / 264.0},
    {.type = digital_card, {.digital_cards = 8}, .suit = 'G', .quality = 11.0 / 264.0},
    {.type = digital_card, {.digital_cards = 10}, .suit = 'G', .quality = 11.0 / 264.0},
    {.type = digital_card, {.digital_cards = 12}, .suit = 'G', .quality = 11.0 / 264.0},
    {.type = digital_card, {.digital_cards = 14}, .suit = 'G', .quality = 11.0 / 264.0},
    {.type = digital_card, {.digital_cards = 16}, .suit = 'G', .quality = 11.0 / 264.0},
    {.type = digital_card, {.digital_cards = 18}, .suit = 'G', .quality = 11.0 / 264.0},
    {.type = digital_card, {.digital_cards = 4}, .suit = 'G', .quality = 11.0 / 264.0},
    {.type = digital_card, {.digital_cards = 6}, .suit = 'G', .quality = 11.0 / 264.0},
    {.type = digital_card, {.digital_cards = 8}, .suit = 'G', .quality = 11.0 / 264.0},
    {.type = digital_card, {.digital_cards = 10}, .suit = 'G', .quality = 11.0 / 264.0},
    {.type = digital_card, {.digital_cards = 12}, .suit = 'G', .quality = 11.0 / 264.0},
    {.type = digital_card, {.digital_cards = 14}, .suit = 'G', .quality = 11.0 / 264.0},
    {.type = digital_card, {.digital_cards = 16}, .suit = 'G', .quality = 11.0 / 264.0},
    {.type = digital_card, {.digital_cards = 18}, .suit = 'G', .quality = 11.0 / 264.0},
    {.type = digital_card, {.digital_cards = 4}, .suit = 'C', .quality = 35.0 / 264.0},
    {.type = digital_card, {.digital_cards = 6}, .suit = 'C', .quality = 35.0 / 264.0},
    {.type = digital_card, {.digital_cards = 8}, .suit = 'C', .quality = 35.0 / 264.0},
    {.type = digital_card, {.digital_cards = 10}, .suit = 'C', .quality = 35.0 / 264.0},
    {.type = digital_card, {.digital_cards = 12}, .suit = 'C', .quality = 35.0 / 264.0},
    {.type = digital_card, {.digital_cards = 14}, .suit = 'C', .quality = 35.0 / 264.0},
    {.type = digital_card, {.digital_cards = 16}, .suit = 'C', .quality = 35.0 / 264.0},
    {.type = digital_card, {.digital_cards = 18}, .suit = 'C', .quality = 35.0 / 264.0},
    {.type = picture_card, {.picture_cards = 'L'}, .suit = 'G', .quality = 11.0 / 264.0},
    {.type = picture_card, {.picture_cards = 'G'}, .suit = 'G', .quality = 11.0 / 264.0},
    {.type = picture_card, {.picture_cards = 'L'}, .suit = 'G', .quality = 11.0 / 264.0},
    {.type = picture_card, {.picture_cards = 'G'}, .suit = 'G', .quality = 11.0 / 264.0},
    {.type = picture_card, {.picture_cards = 'L'}, .suit = 'G', .quality = 11.0 / 264.0},
    {.type = picture_card, {.picture_cards = 'G'}, .suit = 'G', .quality = 11.0 / 264.0},
    {.type = picture_card, {.picture_cards = 'L'}, .suit = 'C', .quality = 35.0 / 264.0},
    {.type = picture_card, {.picture_cards = 'G'}, .suit = 'C', .quality = 35.0 / 264.0},
    {.type = picture_card, {.picture_cards = 'H'}, .suit = 'G', .quality = 11.0 / 264.0},
    {.type = picture_card, {.picture_cards = 'H'}, .suit = 'G', .quality = 11.0 / 264.0},
    {.type = picture_card, {.picture_cards = 'H'}, .suit = 'G', .quality = 11.0 / 264.0},
    {.type = digital_card, {.digital_cards = 2}, .suit = 'G', .quality = 11.0 / 264.0},
    {.type = digital_card, {.digital_cards = 2}, .suit = 'G', .quality = 11.0 / 264.0},
    {.type = digital_card, {.digital_cards = 2}, .suit = 'C', .quality = 35.0 / 264.0},
    {.type = digital_card, {.digital_cards = 2}, .suit = 'H', .quality = 275.0 / 264.0},
    {.type = digital_card, {.digital_cards = 20}, .suit = 'D', .quality = 275.0 / 264.0}};

// Иницализация колоды
void initialize_deck(std::vector<card> &current_deck)
{
    for (short i = 0; i < deck_size; i++)
        current_deck[i] = deck_of_cards[i];
}

// Тасовка колоды
void shuffle_deck(std::vector<card> &current_deck)
{
    srand(time(NULL));
    for (short i = deck_size - 1; i > 1; i--)
    {
        short j = rand() % i;
        std::swap(current_deck[i], current_deck[j]);
    }
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

    std::cout << "Ваши карты: " << std::endl;
    print_card_list(current_cards, len);
    std::cout << "Выберите карту: ";
}

// Вывод стола
void print_table(std::vector<card> &current_cards, short len)
{

    std::cout << line << std::endl;
    if (len == 0)
    {
        std::cout << "Стол пуст!" << std::endl;
    }
    else
    {
        std::cout << "Карты на столе: " << std::endl;
    }
    print_card_list(current_cards, len);
}

// Перемещение карты из src в dst, с последующим удалением в src
void move_card(std::vector<card> &dst, std::vector<card> &src, short index = 0)
{
    dst.emplace_back(src[index]);
    src.erase(src.cbegin() + index);
}

// Очистка списка карт
void clear_card_list(std::vector<card> &src)
{
    while (src.size() > 0)
        src.pop_back();
}

// Раздача карт
void deal_cards(std::vector<card> &current_deck, std::vector<card> &current_hand_1, std::vector<card> &current_hand_2, short cards_in_the_deck)
{
    for (short i = 0; i < cards_in_hand; i++)
    {
        move_card(current_hand_1, current_deck);
        move_card(current_hand_2, current_deck);
    }
    cards_in_the_deck -= cards_in_hand * 2;
}

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

// Проверка суммы числовых карт
bool validate_digital_card_sum(std::vector<card> &selected_cards, card &current_selected_card, short sum = 0, short start_index = 0)
{
    for (start_index; start_index < selected_cards.size(); start_index++)
    {
        if (selected_cards[start_index].type != digital_card)
        {
            return false;
        }
        if (selected_cards[start_index].value.digital_cards != 2)
        {
            sum += selected_cards[start_index].value.digital_cards;
        }
        else
        {
            // Если встречаем Туз, воспринимаем как 2 или 11
            return validate_digital_card_sum(selected_cards, current_selected_card, sum + 2, start_index + 1) ||
                   validate_digital_card_sum(selected_cards, current_selected_card, sum + 11, start_index + 1);
        }
    }
    if (sum != 22)
    {
        return false;
    }
    return true;
}

// Проверка корректности взятки
bool validate_trick(std::vector<card> &selected_cards, card &current_selected_card, short size, short sum = 0)
{
    // Проверка числовых карт
    if (current_selected_card.type == digital_card)
    {
        if (current_selected_card.value.digital_cards != 2)
        {
            // Если карта из руки игрока НЕ Туз
            sum += current_selected_card.value.digital_cards;
            return validate_digital_card_sum(selected_cards, current_selected_card, sum);
        }
        else
        {
            // Если карта из руки игрока Туз -> Воспринимаем как 2 или 11
            return validate_digital_card_sum(selected_cards, current_selected_card, sum + 2) ||
                   validate_digital_card_sum(selected_cards, current_selected_card, sum + 11);
        }
    }
    // Проверка Леди + Джентльмен
    else if ((current_selected_card.value.picture_cards == 'G' &&
              (size != 1 || selected_cards[0].value.picture_cards != 'L')) ||
             (current_selected_card.value.picture_cards == 'L' &&
              (size != 1 || selected_cards[0].value.picture_cards != 'G')))
    {
        return false;
    }
    return true;
}

// Обработка взятки
bool process_trick(std::vector<card> &table_hand, std::vector<card> &current_hand, std::vector<card> &current_tricks, std::vector<card> &selected_cards, short current_selected_card_index)
{
    bool valid_trick = validate_trick(selected_cards, current_hand[current_selected_card_index], selected_cards.size());
    if (valid_trick)
    {
        // Если ход корректный, отправляем карты во взятки
        move_card(current_tricks, current_hand, current_selected_card_index);
        while (selected_cards.size() > 0)
        {
            move_card(current_tricks, selected_cards);
        }
    }
    else
    {
        // Если ход не корректный, возвращаем карты на стол
        while (selected_cards.size() > 0)
        {
            move_card(table_hand, selected_cards);
        }
        std::cout << "Некорректный ход!" << std::endl;
    }
    return valid_trick;
}

// Выбор карт для взятки
void select_cards_for_trick(std::vector<card> &selected_cards, std::vector<card> &table_hand, std::vector<card> &current_hand, std::vector<card> &current_tricks)
{
    short selected_card_index = 0;
    while (selected_card_index != invalid_input)
    {
        print_table(table_hand, table_hand.size());
        std::cout << "Выберите карты для взятки: ";
        selected_card_index = get_move_input(1, table_hand.size());
        if (selected_card_index == invalid_index)
        {
            std::cout << "Вы ввели неверный индекс, попробуйте ещё раз!" << std::endl;
        }
        else if (selected_card_index != invalid_input)
        {
            move_card(selected_cards, table_hand, --selected_card_index);
        }
    }
}

// Выбор карты с руки
short select_card_from_hand(std::vector<card> &table_hand, std::vector<card> &current_hand, std::vector<card> &current_tricks)
{
    short chosen_card_index = 0;
    while (chosen_card_index <= 0)
    {
        print_table(table_hand, table_hand.size());
        print_hand(current_hand, current_hand.size());
        chosen_card_index = get_move_input(1, current_hand.size());
        if (chosen_card_index == invalid_input)
        {
            std::cout << "Неверный ввод, попробуйте ещё раз!" << std::endl;
        }
        else if (chosen_card_index == invalid_index)
        {
            std::cout << "Вы ввели неверный индекс, попробуйте ещё раз!" << std::endl;
        }
    }
    chosen_card_index--;
    return chosen_card_index;
}

// Обработка механизма карты Hunter
void process_hunter_move(std::vector<card> &table_hand, std::vector<card> &current_hand, std::vector<card> &current_tricks, short chosen_card_index)
{
    short count_erase = 0;
    for (short i = 0; i < table_hand.size(); i++)
    {
        // Проверяем, что карта не Gentleman или Lady
        if (!(table_hand[i].type == picture_card && (table_hand[i].value.picture_cards == 'G' || table_hand[i].value.picture_cards == 'L')))
        {
            move_card(current_tricks, table_hand, i);
            count_erase++;
            i--;
        }
    }
    // Остаётся на столе, если не взял ни одной числовой карты или Hunter'a
    if (count_erase == 0)
    {
        move_card(table_hand, current_hand, chosen_card_index);
    }
    // Отправляется во взятки, если взял хотя бы одну числовую карту или Hunter'а
    else
    {
        move_card(current_tricks, current_hand, chosen_card_index);
    }
}

// Сортировка текущих карт на столе
void sort_table(std::vector<card> &table_hand)
{
    short count_picture_cards = 0;
    card tmp;
    for (short idx_i = 0; idx_i < table_hand.size(); idx_i++)
    {
        if (table_hand[idx_i].type == picture_card)
        {
            tmp = table_hand[idx_i];
            table_hand.erase(table_hand.cbegin() + idx_i);
            table_hand.insert(table_hand.cbegin(), tmp);
            count_picture_cards++;
            continue;
        }
        for (short idx_j = idx_i + 1; idx_j < table_hand.size(); idx_j++)
        {
            if ((table_hand[idx_i].type == digital_card && table_hand[idx_j].type == digital_card) &&
                ((table_hand[idx_i].value.digital_cards > table_hand[idx_j].value.digital_cards) ||
                 ((table_hand[idx_i].value.digital_cards == table_hand[idx_j].value.digital_cards) &&
                  (table_hand[idx_i].suit != 'G' && table_hand[idx_j].suit == 'G'))))
            {
                std::swap(table_hand[idx_i], table_hand[idx_j]);
            }
        }
    }
    for (short idx_i = 0; idx_i < count_picture_cards; idx_i++)
    {
        for (short idx_j = idx_i + 1; idx_j < count_picture_cards; idx_j++)
        {
            if ((table_hand[idx_i].value.picture_cards == 'L' && table_hand[idx_j].value.picture_cards == 'G') ||
                (table_hand[idx_i].value.picture_cards == 'H') ||
                ((table_hand[idx_i].value.picture_cards == table_hand[idx_j].value.picture_cards) &&
                 (table_hand[idx_i].suit != 'G' && table_hand[idx_j].suit == 'G')))
            {
                std::swap(table_hand[idx_i], table_hand[idx_j]);
            }
        }
    }
}

// Обработка 1 хода
void process_player_move(std::vector<card> &table_hand, std::vector<card> &current_hand, std::vector<card> &current_tricks, std::vector<card> &selected_cards)
{
    short chosen_card_index = select_card_from_hand(table_hand, current_hand, current_tricks);
    // Если стол не пустой и выбранная карта - не Хантер, выбираем карты для взятки
    if (table_hand.size() != 0 && !(current_hand[chosen_card_index].type == picture_card && current_hand[chosen_card_index].value.picture_cards == 'H'))
    {

        select_cards_for_trick(selected_cards, table_hand, current_hand, current_tricks);
        if (selected_cards.size() > 0)
        {
            bool valid_trick = process_trick(table_hand, current_hand, current_tricks, selected_cards, chosen_card_index);
            if (!valid_trick)
            {
                sort_table(table_hand);
                process_player_move(table_hand, current_hand, current_tricks, selected_cards);
                return;
            }
            is_trick = true;
        }
        else
        {
            move_card(table_hand, current_hand, chosen_card_index);
            is_trick = false;
        }
    }
    // Если стол пустой, выкладываем карту на стол
    else if (table_hand.size() == 0)
    {
        move_card(table_hand, current_hand, chosen_card_index);
    }
    // Иначе, выбранная карта = Hunter, запускаем механизм обработки
    else
    {
        process_hunter_move(table_hand, current_hand, current_tricks, chosen_card_index);
    }
    sort_table(table_hand);
}

// Поиск самого выгодного хода (для бота)
void search_trick(std::vector<card> &table_hand, std::vector<card> &selected_cards, short chosen_card_index)
{
}

// Будущий макет под ход (для бота)
void process_bot_move(std::vector<card> &table_hand, std::vector<card> &current_hand, std::vector<card> &current_tricks, std::vector<card> &selected_cards)
{
}

// Передача оставшихся на столе карт, игроку, который взял последнюю взятку
void process_last_trick(turns last_trick, std::vector<card> &table_hand, std::vector<card> &player_1_tricks, std::vector<card> &player_2_tricks)
{
    if (last_trick == player_1)
    {
        while (table_hand.size() > 0)
            move_card(player_1_tricks, table_hand);
    }
    else if (last_trick == player_2)
        while (table_hand.size() > 0)
            move_card(player_2_tricks, table_hand);
}

// Вычисление очков в конце партии
void сalculate_points(points &results, std::vector<card> &current_hand, short len)
{
    if (len > 24)
        results.get_more_cards = 2;
    else if (len == 24)
        results.get_more_cards = 1;
    short sum_clubs = 0;
    for (int i = 0; i < len; i++)
    {
        if (current_hand[i].suit == 'C')
            sum_clubs += 1;
        if (current_hand[i].value.digital_cards == 20 && current_hand[i].suit == 'D')
            results.get_twenty_of_diamonds = true;
        else if (current_hand[i].value.digital_cards == 2 && current_hand[i].suit == 'H')
            results.get_ace_of_hearts = true;
    }
    if (sum_clubs > 5)
        results.get_more_clubs = true;
}

// Печать взяток (только для отладки)
void print_tricks(std::vector<card> &player_1_tricks, std::vector<card> &player_2_tricks)
{
    std::cout << line << std::endl;
    std::cout << "Взятки игрока: " << std::endl;
    print_card_list(player_1_tricks, player_1_tricks.size());
    std::cout << "Взятки бота: " << std::endl;
    print_card_list(player_2_tricks, player_2_tricks.size());
    std::cout << line << std::endl;
}

// Печать результатов
void print_results(points &player_1_results, points &player_2_results)
{
    std::cout << line << std::endl;
    std::cout << "Результаты: Больше всего карт | Больше всего треф | Двадцатка Буби | Туз черви" << std::endl;
    std::cout << "Результаты Игрока: "
              << (short)player_1_results.get_more_cards << " | "
              << player_1_results.get_more_clubs << " | "
              << player_1_results.get_twenty_of_diamonds << " | "
              << player_1_results.get_ace_of_hearts << std::endl;
    std::cout << "Результаты Бота: "
              << (short)player_2_results.get_more_cards << " | "
              << player_2_results.get_more_clubs << " | "
              << player_2_results.get_twenty_of_diamonds << " | "
              << player_2_results.get_ace_of_hearts << std::endl;
}

int main(void)
{
    bool success_move = true;
    turns turn = player_1;
    turns last_trick;
    std::vector<card> current_deck(deck_size);
    std::vector<card> player_1_hand;
    std::vector<card> player_1_tricks;
    std::vector<card> player_2_hand;
    std::vector<card> player_2_tricks;
    std::vector<card> table_hand;
    std::vector<card> selected_cards;
    points player_1_results{};
    points player_2_results{};
    initialize_deck(current_deck);
    shuffle_deck(current_deck);
    for (short i = 0; i < deck_size; i++)
    {
        if (i % 8 == 0 && success_move == true)
        {
            deal_cards(current_deck, player_1_hand, player_2_hand, current_deck.size());
        }
        if (turn == player_1)
        {
            std::cout << line << std::endl;
            std::cout << "Ход игрока 1" << std::endl;
            process_player_move(table_hand, player_1_hand, player_1_tricks, selected_cards);
            if (is_trick)
                last_trick = player_1;
            turn = player_2;
        }
        else
        {
            std::cout << line << std::endl;
            std::cout << "Ход игрока 2" << std::endl;
            process_player_move(table_hand, player_2_hand, player_2_tricks, selected_cards);
            if (is_trick)
                last_trick = player_2;
            turn = player_1;
        }
    }
    process_last_trick(last_trick, table_hand, player_1_tricks, player_2_tricks);
    print_tricks(player_1_tricks, player_2_tricks);
    сalculate_points(player_1_results, player_1_tricks, player_1_tricks.size());
    сalculate_points(player_2_results, player_2_tricks, player_2_tricks.size());
    print_results(player_1_results, player_2_results);
    return 0;
}