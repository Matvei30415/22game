#pragma once

#include "console_io.h"
#include "player.h"

class BotPlayer : public Player
{
public:
    BotPlayer(std::string name) : Player(name) { maxComboQuality = 0; }
    void makeMove(Player &table, game_mode mode) override;
    void search_trick(Player &table);
    void find_digital_combinations(Player &table, std::vector<Card> &combo, short n, short start = 0);
    void find_picture_combinations(Player &table, std::vector<Card> &combo);
    void find_hunter_combinations(Player &table, std::vector<Card> &combo);
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
