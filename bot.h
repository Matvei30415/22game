#pragma once

#include "card.h"
#include "deck.h"
#include "consoleIO.h"
#include "table.h"
#include "player.h"

class BotPlayer : public Player
{
public:
    struct AVGStat
    {
        short comboNumber;
        short minComboNumber;
        std::size_t minComboNumberIndex;
    };
    BotPlayer(short id) : Player(id)
    {
        name = "Бот " + std::to_string(id);
        maxComboQuality = 0;
    }
    std::string getTypeName() const override { return "Bot"; }
    void preMoveActions(const std::vector<Card> &playerHand, const std::vector<Card> &deckCards);
    bool makeMove(Table &table) override;
    void selectNonComboCard();
    void searchTrick(const std::vector<Card> &tableHand);
    void findDigitalCombo(const std::vector<Card> &tableHand, std::vector<Card> &combo, short n, std::size_t start = 0);
    void findPictureCombo(const std::vector<Card> &tableHand, std::vector<Card> &combo);
    void findHunterCombo(const std::vector<Card> &tableHand, std::vector<Card> &combo);
    void setMaxCombo(const std::vector<Card> &combo, const double quality);
    void setMaxCard(const Card &card);
    const std::vector<Card> &getMaxCombo() const;
    const Card &getMaxCard() const;
    double getMaxComboQuality() const;
    void clearMaxCombo();
    void clearComboNumber();
    void clearModifiedDeck();

private:
    std::vector<Card> maxCombo;
    std::vector<Card> modifiedDeck;
    Card maxCard;
    double maxComboQuality;
    AVGStat statistics;
};
