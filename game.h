#pragma once

#include "card_list.h"
#include "points.h"
#include "console_io.h"
#include "hunter.h"
#include "deck.h"
#include "bot.h"
#include "player.h"
#include "game_mode.h"
#include "human.h"

enum turn
{
    player_1_turn = 1,
    player_2_turn = 2
};

class member
{
public:
    CardList hand;
    CardList tricks;
    Points results;
    bool is_trick;
};

void process_last_trick(turn last_trick, CardList &table_hand, CardList &player_1_tricks, CardList &player_2_tricks);

void process_game(Deck &current_deck, game_mode mode, CardList &table_hand, CardList &player_1_hand, CardList &player_2_hand,
                  CardList &player_1_tricks, CardList &player_2_tricks, CardList &selected_cards, turn &last_trick);

void start_game(game_mode mode);