#pragma once

#include "card_list.h"
#include "points.h"
#include "console_io.h"
#include "hunter.h"
#include "deck.h"
#include "bot.h"
#include "player.h"
#include "game_mode.h"

enum turn
{
    player_1 = 1,
    player_2 = 2
};

class member
{
public:
    card_list hand;
    card_list tricks;
    points results;
    bool is_trick;
};

void process_last_trick(turn last_trick, card_list &table_hand, card_list &player_1_tricks, card_list &player_2_tricks);

void process_game(card_list &current_deck, game_mode mode, card_list &table_hand, card_list &player_1_hand, card_list &player_2_hand,
                  card_list &player_1_tricks, card_list &player_2_tricks, card_list &selected_cards, turn &last_trick);

void start_game(game_mode mode);