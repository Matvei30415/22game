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
    short moreCards;
    short moreClubs;
    short twentyOfDiamonds;
    short aceOfHearts;
};

class Player
{
public:
    Player(short id);
    virtual void makeMove(Table &table, GameMode mode) = 0;
    void setSelectedCard(const Card &card);
    void setSelectedTrick(const std::vector<Card> &cards);
    void setIsTrick(const bool isTrick);
    short getID() const;
    bool getIsTrick() const;
    const std::vector<Card> &getHand() const;
    const std::vector<Card> &getTricks() const;
    const Card &getSelectedCard() const;
    const std::vector<Card> &getSelectedTrick() const;
    void sortHand();
    void addCardToHand(const Card &card);
    void addCardToTricks(const Card &card);
    void addTrickToTricks(const std::vector<Card> &cards);
    void removeCardFromHand(const Card &card);
    void removeTrickFromHand(const std::vector<Card> &trick);
    void clearSelectedTrick();
    void makeHunterMove(Table &table);
    void сalculatePoints();
    void getPoints(char &moreCards, bool &moreClubs, bool &twentyOfDiamonds, bool &aceOfHearts);

protected:
    short id;
    std::string name;
    bool isTrick;
    std::vector<Card> hand;
    std::vector<Card> tricks;
    Card selectedCard;
    std::vector<Card> selectedTrick;
    Points results;

    // Строго функции ввода-вывода
public:
    virtual void printAnnouncement() const = 0;
    virtual void printHand() const = 0;
    virtual void printTricks() const = 0;

protected:
    void printSelectedCard() const;
    void printMove() const;
};
