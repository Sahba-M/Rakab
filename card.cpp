
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
void Card::setName (std::string name)
{
    this->name = name;
}
std::string Card::getName()
{
    return name ;
}
bool Card::operator== (const Card & other)
{
    return this->name == other.name ;
}
std::istream & operator>> ( std::istream & input , Card & card )
{
    input >> card.name ;
    card.setName(card.name);
    return input ;
}
