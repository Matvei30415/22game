#include "points.h"

// Вычисление очков в конце партии
void Points::сalculate_points(std::vector<Card> &tricks)
{
    short len = tricks.size();
    if (len > 24)
        this->more_cards = 2;
    else if (len == 24)
        this->more_cards = 1;
    short sum_clubs = 0;
    for (int i = 0; i < len; i++)
    {
        if (tricks[i].getSuit() == 'C')
            sum_clubs += 1;
        if (tricks[i].getDigitalValue() == 20 && tricks[i].getSuit() == 'D')
            this->twenty_of_diamonds = true;
        else if (tricks[i].getDigitalValue() == 2 && tricks[i].getSuit() == 'H')
            this->ace_of_hearts = true;
    }
    if (sum_clubs > 5)
        this->more_clubs = true;
}

// Геттер результатов
void Points::get_points(char &more_cards, bool &more_clubs, bool &twenty_of_diamonds, bool &ace_of_hearts)
{
    more_cards = this->more_cards;
    more_clubs = this->more_clubs;
    twenty_of_diamonds = this->twenty_of_diamonds;
    ace_of_hearts = this->ace_of_hearts;
}