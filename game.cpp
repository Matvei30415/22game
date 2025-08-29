#include "game.h"

// Передача оставшихся на столе карт, игроку, который взял последнюю взятку
void process_last_trick(turn last_trick, card_list &table_hand, card_list &player_1_tricks, card_list &player_2_tricks)
{
    if (last_trick == player_1)
    {
        while (table_hand.size() > 0)
            card_list::move_card(player_1_tricks, table_hand);
    }
    else if (last_trick == player_2)
        while (table_hand.size() > 0)
            card_list::move_card(player_2_tricks, table_hand);
}

// Запуск одной партии
void process_game(card_list &current_deck, game_mode mode, card_list &table_hand, card_list &player_1_hand, card_list &player_2_hand,
                  card_list &player_1_tricks, card_list &player_2_tricks, card_list &selected_cards, turn &last_trick)
{
    bool is_trick = false;
    bool success_move = true;
    turn current_turn = player_1;
    for (short i = 0; i < deck_size; i++)
    {
        if (i % 8 == 0 && success_move == true)
        {
            deal_cards(current_deck, player_1_hand, player_2_hand);
            card_list::sort_card_list(player_1_hand);
            card_list::sort_card_list(player_2_hand);
        }
        if (current_turn == player_1)
        {
            print_line();
            std::cout << "Ход игрока 1" << std::endl;
            print_line();
            process_player_move(table_hand, player_1_hand, player_1_tricks, is_trick, mode);
            if (is_trick)
                last_trick = player_1;
            current_turn = player_2;
        }
        else
        {
            switch (mode)
            {
            case with_other_player:
                print_line();
                std::cout << "Ход игрока 2" << std::endl;
                print_line();
                process_player_move(table_hand, player_2_hand, player_2_tricks, is_trick, mode);
                break;
            case with_bot:
                print_line();
                std::cout << "Ход бота" << std::endl;
                print_line();
                process_bot_move(table_hand, player_2_hand, player_2_tricks, is_trick);
                break;
            }
            if (is_trick)
                last_trick = player_2;
            current_turn = player_1;
        }
        // std::cout << "Последняя взятка: " << last_trick << std::endl;
    }
}

void start_game(game_mode mode)
{
    bool success_move = true;
    turn current_turn = player_1;
    turn last_trick;
    card_list current_deck(deck_size);
    card_list player_1_hand;
    card_list player_1_tricks;
    card_list player_2_hand;
    card_list player_2_tricks;
    card_list table_hand;
    card_list selected_cards;
    points player_1_results{};
    points player_2_results{};
    initialize_deck(current_deck);
    shuffle_deck(current_deck);
    process_game(current_deck, mode, table_hand, player_1_hand, player_2_hand, player_1_tricks, player_2_tricks, selected_cards, last_trick);
    process_last_trick(last_trick, table_hand, player_1_tricks, player_2_tricks);
    print_tricks(player_1_tricks, player_2_tricks);
    сalculate_points(player_1_results, player_1_tricks, player_1_tricks.size());
    сalculate_points(player_2_results, player_2_tricks, player_2_tricks.size());
    print_results(player_1_results, player_2_results, mode);
}