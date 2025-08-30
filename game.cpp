#include "game.h"

// Передача оставшихся на столе карт, игроку, который взял последнюю взятку
void process_last_trick(turn last_trick, Player &table, Player &player_1, Player &player_2)
{
    CardList &table_hand = table.getHand();
    if (last_trick == player_1_turn)
    {
        while (table_hand.size() > 0)
        {
            player_1.addCardToTrick(table_hand[0]);
            table.removeCardFromHand(0);
        }
    }
    else if (last_trick == player_2_turn)
        while (table_hand.size() > 0)
        {
            player_2.addCardToTrick(table_hand[0]);
            table.removeCardFromHand(0);
        }
}

// Запуск одной партии
void process_game(Deck &current_deck, game_mode mode, Player &table,
                  Player &player_1, Player &player_2,
                  CardList &selected_cards, turn &last_trick)
{
    bool success_move = true;
    turn current_turn = player_1_turn;
    for (short i = 0; i < deck_size; i++)
    {
        if (i % 8 == 0 && success_move == true)
        {
            current_deck.dealHand(player_1.getHand());
            current_deck.dealHand(player_2.getHand());
            player_1.sortHand();
            player_2.sortHand();
        }
        if (current_turn == player_1_turn)
        {
            print_line();
            std::cout << "Ход игрока 1" << std::endl;
            print_line();
            player_1.makeMove(table, mode);
            if (player_1.getIsTrick())
                last_trick = player_1_turn;
            current_turn = player_2_turn;
        }
        else
        {
            switch (mode)
            {
            case with_other_player:
                print_line();
                std::cout << "Ход игрока 2" << std::endl;
                print_line();
                player_2.makeMove(table, mode);
                break;
            case with_bot:
                print_line();
                std::cout << "Ход бота" << std::endl;
                print_line();
                player_2.makeMove(table, mode);
                break;
            }
            if (player_2.getIsTrick())
                last_trick = player_2_turn;
            current_turn = player_1_turn;
        }
        // std::cout << "Последняя взятка: " << last_trick << std::endl;
    }
}

void start_game(game_mode mode)
{
    bool success_move = true;
    turn current_turn = player_1_turn;
    turn last_trick;
    Deck current_deck;
    HumanPlayer player_1("Игрок 1");
    HumanPlayer human_player_2("Игрок 2");
    BotPlayer bot_player_2("Бот");
    Player *player_2;
    if (mode == with_bot)
        player_2 = &bot_player_2;
    else
        player_2 = &human_player_2;
    HumanPlayer table("Стол");
    CardList selected_cards;
    Points player_1_results{};
    Points player_2_results{};
    current_deck.shuffle();
    process_game(current_deck, mode, table, player_1, *player_2, selected_cards, last_trick);
    process_last_trick(last_trick, table, player_1, (*player_2));
    print_tricks(player_1.getTricks(), (*player_2).getTricks());
    player_1_results.сalculate_points(player_1.getTricks());
    player_2_results.сalculate_points((*player_2).getTricks());
    print_results(player_1_results, player_2_results, mode);
}