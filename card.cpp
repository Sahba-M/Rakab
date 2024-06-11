
#include "card.h"

Card::Card ( std::string name , int score )
{
    setScore( score );
    setName( name );
}
Card::Card(){}
Card::~Card() = default;

void Card:: setScore(int score)
{
    this->score = score;
}
int Card:: getScore()
{
    return score;
}
void Card::setName (std::string name)
{
    this->name = name;
}
std::string Card::getName()
{
    return name ;
}



