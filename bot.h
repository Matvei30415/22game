#pragma once

#include "consoleIO.h"
#include "table.h"
#include "player.h"

class BotPlayer : public Player
{
public:
    BotPlayer(std::string name) : Player(name) { maxComboQuality = 0; }
    void makeMove(Table &table, gameMode mode) override;
    void searchTrick(Table &table);
    void findDigitalCombo(Table &table, std::vector<Card> &combo, short n, short start = 0);
    void findPictureCombo(Table &table, std::vector<Card> &combo);
    void findHunterCombo(Table &table, std::vector<Card> &combo);
    void setMaxCombo(std::vector<Card> &combo, double quality);
    void setMaxCard(Card &card);
    std::vector<Card> &getMaxCombo();
    Card &getMaxCard();
    double getMaxComboQuality();
    void clearMaxCombo();

private:
    std::vector<Card> maxCombo;
    Card maxCard;
    double maxComboQuality;
};
