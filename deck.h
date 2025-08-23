#pragma once

#include "card_list.h"
#include <cstdlib>
#include <ctime>

enum
{
    deck_size = 48,
    cards_in_hand = 4
};

void initialize_deck(card_list &current_deck);

void shuffle_deck(card_list &current_deck);

void deal_cards(card_list &current_deck, card_list &current_hand_1, card_list &current_hand_2, short cards_in_the_deck);