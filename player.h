#pragma once

#include "card.h"
#include "points.h"
#include "game_mode.h"
#include "console_io.h"
#include <algorithm>
class Player
{
public:
    Player(std::string name);
    virtual void makeMove(Player &table, game_mode mode) = 0;
    void setSelectedCard(const Card &card);
    void setIsTrick(bool isTrick);
    bool getIsTrick();
    std::vector<Card> &getHand();
    std::vector<Card> &getTricks();
    Card &getSelectedCard();
    std::vector<Card> &getSelectedTrick();
    void sortHand();
    void addCardToHand(const Card &card);
    void addCardToTricks(const Card &card);
    void addTrickToTricks(const std::vector<Card> &trick);
    void removeCardFromHand(Card &card);
    void removeTrickFromHand(std::vector<Card> &trick);
    void clearSelectedTrick();
    void makeHunterMove(Player &table);

protected:
    std::string name;
    bool isTrick;
    std::vector<Card> hand;
    std::vector<Card> tricks;
    Card selectedCard;
    std::vector<Card> selectedTrick;
    Points results;
};
