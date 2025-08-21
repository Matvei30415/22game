#include "deck.h"

const card deck_of_cards[deck_size] = {
    {.id = 1, .type = digital_card, {.digital_cards = 4}, .suit = 'G', .quality = 11.0 / 264.0},
    {.id = 2, .type = digital_card, {.digital_cards = 6}, .suit = 'G', .quality = 11.0 / 264.0},
    {.id = 3, .type = digital_card, {.digital_cards = 8}, .suit = 'G', .quality = 11.0 / 264.0},
    {.id = 4, .type = digital_card, {.digital_cards = 10}, .suit = 'G', .quality = 11.0 / 264.0},
    {.id = 5, .type = digital_card, {.digital_cards = 12}, .suit = 'G', .quality = 11.0 / 264.0},
    {.id = 6, .type = digital_card, {.digital_cards = 14}, .suit = 'G', .quality = 11.0 / 264.0},
    {.id = 7, .type = digital_card, {.digital_cards = 16}, .suit = 'G', .quality = 11.0 / 264.0},
    {.id = 8, .type = digital_card, {.digital_cards = 18}, .suit = 'G', .quality = 11.0 / 264.0},
    {.id = 9, .type = digital_card, {.digital_cards = 4}, .suit = 'G', .quality = 11.0 / 264.0},
    {.id = 10, .type = digital_card, {.digital_cards = 6}, .suit = 'G', .quality = 11.0 / 264.0},
    {.id = 11, .type = digital_card, {.digital_cards = 8}, .suit = 'G', .quality = 11.0 / 264.0},
    {.id = 12, .type = digital_card, {.digital_cards = 10}, .suit = 'G', .quality = 11.0 / 264.0},
    {.id = 13, .type = digital_card, {.digital_cards = 12}, .suit = 'G', .quality = 11.0 / 264.0},
    {.id = 14, .type = digital_card, {.digital_cards = 14}, .suit = 'G', .quality = 11.0 / 264.0},
    {.id = 15, .type = digital_card, {.digital_cards = 16}, .suit = 'G', .quality = 11.0 / 264.0},
    {.id = 16, .type = digital_card, {.digital_cards = 18}, .suit = 'G', .quality = 11.0 / 264.0},
    {.id = 17, .type = digital_card, {.digital_cards = 4}, .suit = 'G', .quality = 11.0 / 264.0},
    {.id = 18, .type = digital_card, {.digital_cards = 6}, .suit = 'G', .quality = 11.0 / 264.0},
    {.id = 19, .type = digital_card, {.digital_cards = 8}, .suit = 'G', .quality = 11.0 / 264.0},
    {.id = 20, .type = digital_card, {.digital_cards = 10}, .suit = 'G', .quality = 11.0 / 264.0},
    {.id = 21, .type = digital_card, {.digital_cards = 12}, .suit = 'G', .quality = 11.0 / 264.0},
    {.id = 22, .type = digital_card, {.digital_cards = 14}, .suit = 'G', .quality = 11.0 / 264.0},
    {.id = 23, .type = digital_card, {.digital_cards = 16}, .suit = 'G', .quality = 11.0 / 264.0},
    {.id = 24, .type = digital_card, {.digital_cards = 18}, .suit = 'G', .quality = 11.0 / 264.0},
    {.id = 25, .type = digital_card, {.digital_cards = 4}, .suit = 'C', .quality = 35.0 / 264.0},
    {.id = 26, .type = digital_card, {.digital_cards = 6}, .suit = 'C', .quality = 35.0 / 264.0},
    {.id = 27, .type = digital_card, {.digital_cards = 8}, .suit = 'C', .quality = 35.0 / 264.0},
    {.id = 28, .type = digital_card, {.digital_cards = 10}, .suit = 'C', .quality = 35.0 / 264.0},
    {.id = 29, .type = digital_card, {.digital_cards = 12}, .suit = 'C', .quality = 35.0 / 264.0},
    {.id = 30, .type = digital_card, {.digital_cards = 14}, .suit = 'C', .quality = 35.0 / 264.0},
    {.id = 31, .type = digital_card, {.digital_cards = 16}, .suit = 'C', .quality = 35.0 / 264.0},
    {.id = 32, .type = digital_card, {.digital_cards = 18}, .suit = 'C', .quality = 35.0 / 264.0},
    {.id = 33, .type = picture_card, {.picture_cards = 'L'}, .suit = 'G', .quality = 11.0 / 264.0},
    {.id = 34, .type = picture_card, {.picture_cards = 'G'}, .suit = 'G', .quality = 11.0 / 264.0},
    {.id = 35, .type = picture_card, {.picture_cards = 'L'}, .suit = 'G', .quality = 11.0 / 264.0},
    {.id = 36, .type = picture_card, {.picture_cards = 'G'}, .suit = 'G', .quality = 11.0 / 264.0},
    {.id = 37, .type = picture_card, {.picture_cards = 'L'}, .suit = 'G', .quality = 11.0 / 264.0},
    {.id = 38, .type = picture_card, {.picture_cards = 'G'}, .suit = 'G', .quality = 11.0 / 264.0},
    {.id = 39, .type = picture_card, {.picture_cards = 'L'}, .suit = 'C', .quality = 35.0 / 264.0},
    {.id = 40, .type = picture_card, {.picture_cards = 'G'}, .suit = 'C', .quality = 35.0 / 264.0},
    {.id = 41, .type = picture_card, {.picture_cards = 'H'}, .suit = 'G', .quality = 11.0 / 264.0},
    {.id = 42, .type = picture_card, {.picture_cards = 'H'}, .suit = 'G', .quality = 11.0 / 264.0},
    {.id = 43, .type = picture_card, {.picture_cards = 'H'}, .suit = 'G', .quality = 11.0 / 264.0},
    {.id = 44, .type = digital_card, {.digital_cards = 2}, .suit = 'G', .quality = 11.0 / 264.0},
    {.id = 45, .type = digital_card, {.digital_cards = 2}, .suit = 'G', .quality = 11.0 / 264.0},
    {.id = 46, .type = digital_card, {.digital_cards = 2}, .suit = 'C', .quality = 35.0 / 264.0},
    {.id = 47, .type = digital_card, {.digital_cards = 2}, .suit = 'H', .quality = 275.0 / 264.0},
    {.id = 48, .type = digital_card, {.digital_cards = 20}, .suit = 'D', .quality = 275.0 / 264.0}};

// Иницализация колоды
void initialize_deck(std::vector<card> &current_deck)
{
    for (short i = 0; i < deck_size; i++)
        current_deck[i] = deck_of_cards[i];
}

// Тасовка колоды
void shuffle_deck(std::vector<card> &current_deck)
{
    srand(time(NULL));
    for (short i = deck_size - 1; i > 1; i--)
    {
        short j = rand() % i;
        std::swap(current_deck[i], current_deck[j]);
    }
}

// Раздача карт
void deal_cards(std::vector<card> &current_deck, std::vector<card> &current_hand_1, std::vector<card> &current_hand_2, short cards_in_the_deck)
{
    for (short i = 0; i < cards_in_hand; i++)
    {
        move_card(current_hand_1, current_deck);
        move_card(current_hand_2, current_deck);
    }
    cards_in_the_deck -= cards_in_hand * 2;
}