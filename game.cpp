#include "game.h"

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

// Запуск одной партии
void process_game(std::vector<card> &current_deck, game_mode mode, std::vector<card> &table_hand, std::vector<card> &player_1_hand, std::vector<card> &player_2_hand, std::vector<card> &player_1_tricks, std::vector<card> &player_2_tricks, std::vector<card> &selected_cards, turns &last_trick)
{
    bool is_trick = false;
    bool success_move = true;
    turns turn = player_1;
    for (short i = 0; i < deck_size; i++)
    {
        if (i % 8 == 0 && success_move == true)
        {
            deal_cards(current_deck, player_1_hand, player_2_hand, current_deck.size());
            sort_card_list(player_1_hand);
            sort_card_list(player_2_hand);
        }
        if (turn == player_1)
        {
            std::cout << line << std::endl;
            std::cout << "Ход игрока 1" << std::endl;
            process_player_move(table_hand, player_1_hand, player_1_tricks, selected_cards, is_trick);
            if (is_trick)
                last_trick = player_1;
            turn = player_2;
        }
        else
        {
            switch (mode)
            {
            case with_other_player:
                std::cout << line << std::endl;
                std::cout << "Ход игрока 2" << std::endl;
                std::cout << line << std::endl;
                process_player_move(table_hand, player_2_hand, player_2_tricks, selected_cards, is_trick);
                break;
            case with_bot:
                std::cout << line << std::endl;
                std::cout << "Ход бота" << std::endl;
                std::cout << line << std::endl;
                process_bot_move(table_hand, player_2_hand, player_2_tricks, selected_cards, is_trick);
                break;
            }
            if (is_trick)
                last_trick = player_2;
            turn = player_1;
        }
    }
}

void start_game(game_mode mode)
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
    process_game(current_deck, mode, table_hand, player_1_hand, player_2_hand, player_1_tricks, player_2_tricks, selected_cards, last_trick);
    process_last_trick(last_trick, table_hand, player_1_tricks, player_2_tricks);
    print_tricks(player_1_tricks, player_2_tricks);
    сalculate_points(player_1_results, player_1_tricks, player_1_tricks.size());
    сalculate_points(player_2_results, player_2_tricks, player_2_tricks.size());
    print_results(player_1_results, player_2_results);
}