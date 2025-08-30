#pragma once

#include "card.h"
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

void process_last_trick(turn last_trick, Player &table, Player &player_1, Player &player_2);

void process_game(Deck &current_deck, game_mode mode, Player &table,
                  Player &player_1, Player &player_2,
                  std::vector<Card> &selected_cards, turn &last_trick);

void start_game(game_mode mode);