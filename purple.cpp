#include <iostream>

#include "purple.h"

PurpleCard::PurpleCard ( std::string name )
{
    setName(name);
}
void PurpleCard::setName(std::string name)
{
    this->name=name;
}