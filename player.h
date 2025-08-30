#pragma once

#include "card.h"
#include "points.h"
#include "game_mode.h"
#include "console_io.h"
#include "hunter.h"

class Player {
public:
    Player(std::string &name);
    virtual void makeMove(Player &table, game_mode mode) = 0;
    std::vector<Card>& getHand();
    std::vector<Card>& getTricks();
    bool getIsTrick();
    void sortHand();
    void addCardToHand(const Card& card);
    void addCardToTrick(const Card& card);
    void addTrick(const std::vector<Card>& trick);
    void removeCardFromHand(short index);
    void moveCardFromHandTo(std::vector<Card> &dst, short index = 0);
protected:
    std::string name;
    bool is_trick;
    std::vector<Card> hand;
    std::vector<Card> tricks;
    Points results;
};

