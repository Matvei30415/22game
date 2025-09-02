#pragma once

#include "card.h"
#include "table.h"

// (*)
enum GameMode : short
{
    withBot = 1,
    withOtherPlayer = 2,
};

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
    Player(short ID);
    virtual void makeMove(Table &table, GameMode mode) = 0;
    void setSelectedCard(const Card &card);
    void setSelectedTrick(const std::vector<Card> &cards);
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
    short ID;
    std::string name;
    bool isTrick;
    std::vector<Card> tricks;
    Card selectedCard;
    std::vector<Card> selectedTrick;
    Points results;

    // Строго функции ввода-вывода
public:
    virtual void printAnnouncement() = 0;
    virtual void printHand() = 0;
    virtual void printTricks() = 0;

protected:
    void printSelectedCard();
    void printMove();
};
