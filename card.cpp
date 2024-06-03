
#include "card.h"

Card::Card ( int score )
{
    this->score = score ;
}
Card::Card(){}

void Card:: setScore(int score)
{
    this->score = score;
}
int Card:: getScore()
{
    return score;
}