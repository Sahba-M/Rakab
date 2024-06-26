
#include "card.h"

Card::Card ( std::string name )
{
    setName( name );
}
Card::Card(){}
Card::~Card() = default;

void Card::setName (std::string name)
{
    this->name = name;
}
std::string Card::getName()
{
    return name ;
}
bool  Card::operator== (const Card & other)
{
    return this->name == other.name;
}

