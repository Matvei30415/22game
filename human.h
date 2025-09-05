#pragma once

#include "card.h"
#include "deck.h"
#include "table.h"
#include "player.h"

class HumanPlayer : public Player
{
public:
    HumanPlayer(short id) : Player(id)
    {
        name = "Игрок " + std::to_string(id);
    }
    std::string getTypeName() const override { return "Human"; }
    void preMoveActions(const Table &table, const std::size_t &selectedCardIndex,
                        const std::vector<std::size_t> &selectedTrickIndexes);
    bool makeMove(Table &table) override;
    bool processTrick(Table &table);
    bool validateTrick() const;
    bool validateDigitalCardSum(short sum = 0, std::size_t start = 0) const;
};
