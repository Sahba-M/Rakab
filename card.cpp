#include <iostream>
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
std::istream &operator>> (std::istream &input, Card &card)
{
    input >> card.name;
    return input;
}
// std::istream& operator>>(std::istream& in, std::shared_ptr<Card>& card) {
//     std::string name;
//     in >> name; // ورودی گرفتن از جریان ورودی (cin)

//     // ایجاد شیء Card و آن را به شیء shared_ptr ارجاع داده شده ارسال می کند
//     card = std::make_shared<Card>(name);
//     return in;
// }


