#pragma once

#include "card.h"
#include "consoleIO.h"
#include "table.h"
#include "player.h"

class BotPlayer : public Player
{
public:
    BotPlayer(short ID) : Player(ID)
    {
        name = "Бот " + std::to_string(ID);
        maxComboQuality = 0;
    }
    void makeMove(Table &table, const GameMode mode) override;
    void searchTrick(const Table &table);
    void findDigitalCombo(const Table &table, std::vector<Card> &combo, short n, short start = 0);
    void findPictureCombo(const Table &table, std::vector<Card> &combo);
    void findHunterCombo(const Table &table, std::vector<Card> &combo);
    void setMaxCombo(const std::vector<Card> &combo, const double quality);
    void setMaxCard(const Card &card);
    const std::vector<Card> &getMaxCombo() const;
    const Card &getMaxCard() const;
    const double getMaxComboQuality() const;
    void clearMaxCombo();

private:
    std::vector<Card> maxCombo;
    Card maxCard;
    double maxComboQuality;

    // Строго функции ввода-вывода
public:
    void printAnnouncement() const override;
    void printHand() const override;
    void printTricks() const override;
};
