
#include "card.h"

Card::Card ( std::string name , int score )
{
    setScore( score );
    setName( name );
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