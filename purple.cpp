#include <iostream>

#include "purple.h"

PurpleCard::PurpleCard (){}
PurpleCard::PurpleCard ( std::string name )
{
    setName(name);
}
// std::string PurpleCard::displayName()
// {
//     return "YellowCard";
// }