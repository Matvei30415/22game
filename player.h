#pragma once

#include "card_list.h"
#include "points.h"
#include "game_mode.h"
#include "console_io.h"
#include "hunter.h"

class Player {
public:
    Player(std::string &name);
    virtual void makeMove(Player &table, game_mode mode) = 0;
    void setHand(CardList &src);
    CardList& getHand();
    CardList& getTricks();
    bool getIsTrick();
    void sortHand();
    void addCardToHand(const Card& card);
    void addCardToTrick(const Card& card);
    void addTrick(const CardList& trick);
    void removeCardFromHand(short index);
    void moveCardFromHandTo(CardList &dst, short index = 0);
protected:
    std::string name;
    bool is_trick;
    CardList hand;
    CardList tricks;
    Points results;
};

