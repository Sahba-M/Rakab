#include <iostream>
#include <string>
#include <memory>
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
// std::istream &operator>> (std::istream &input, Card &card)
// {
//     input >> card.name;
//     return input;
// }
std::istream & operator>> (std::istream & input , std::shared_ptr<Card> & card) {
    std::string name;
    input >> name; 
    card = std::make_shared<Card>(name);
    return input;
}
std::ostream & operator<< ( std::ostream & output , const Card & card ) 
{
    output << card.name;
    return output;
}




