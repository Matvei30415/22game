#include "game.h"

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
    process_game(current_deck, with_bot, table_hand, player_1_hand, player_2_hand, player_1_tricks, player_2_tricks, selected_cards, last_trick);
    process_last_trick(last_trick, table_hand, player_1_tricks, player_2_tricks);
    print_tricks(player_1_tricks, player_2_tricks);
    сalculate_points(player_1_results, player_1_tricks, player_1_tricks.size());
    сalculate_points(player_2_results, player_2_tricks, player_2_tricks.size());
    print_results(player_1_results, player_2_results);
    return 0;
}