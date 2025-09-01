#pragma once

#include "card.h"
#include "table.h"

enum gameMode : short;

struct Points
{
    char moreCards;
    bool moreClubs;
    bool twentyOfDiamonds;
    bool aceOfHearts;
};

class Player : public Table
{
public:
    Player(std::string name);
    virtual void makeMove(Table &table, gameMode mode) = 0;
    void setSelectedCard(const Card &card);
    void setIsTrick(bool isTrick);
    bool getIsTrick();
    std::vector<Card> &getTricks();
    Card &getSelectedCard();
    std::vector<Card> &getSelectedTrick();
    void addCardToTricks(const Card &card);
    void addTrickToTricks(const std::vector<Card> &trick);
    void clearSelectedTrick();
    void makeHunterMove(Table &table);
    void сalculatePoints();
    void getPoints(char &moreCards, bool &moreClubs, bool &twentyOfDiamonds, bool &aceOfHearts);
protected:
    std::string name;
    bool isTrick;
    std::vector<Card> tricks;
    Card selectedCard;
    std::vector<Card> selectedTrick;
    Points results;
};
