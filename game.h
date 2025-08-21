#ifndef GAME_H
#define GAME_H

#include "card.h"
#include "basic.h"
#include "deck.h"
#include "bot.h"
#include "player.h"

enum turns {
    player_1 = 1,
    player_2 = 2
};

enum game_mode {
    with_other_player = 1,
    with_bot = 2
};

void process_last_trick(turns last_trick, std::vector<card> &table_hand, std::vector<card> &player_1_tricks, std::vector<card> &player_2_tricks);

void process_game(std::vector<card> &current_deck, game_mode mode, std::vector<card> &table_hand, std::vector<card> &player_1_hand, std::vector<card> &player_2_hand, std::vector<card> &player_1_tricks, std::vector<card> &player_2_tricks, std::vector<card> &selected_cards, turns &last_trick);


#endif