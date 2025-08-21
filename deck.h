#ifndef DECK_H
#define DECK_H

#include "basic.h"
#include "card.h"
#include <cstdlib>
#include <ctime>

enum
{
    deck_size = 48,
    cards_in_hand = 4,
};

void initialize_deck(std::vector<card> &current_deck);

void shuffle_deck(std::vector<card> &current_deck);

void deal_cards(std::vector<card> &current_deck, std::vector<card> &current_hand_1, std::vector<card> &current_hand_2, short cards_in_the_deck);

#endif