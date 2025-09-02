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
    void makeMove(Table &table, GameMode mode) override;
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
    // Строго функции ввода-вывода
    void printAnnouncement() override;
    void printHand() override;
    void printTricks() override;

private:
    std::vector<Card> maxCombo;
    Card maxCard;
    double maxComboQuality;
};
