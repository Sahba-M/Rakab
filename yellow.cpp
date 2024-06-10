#include <string>

#include "yellow.h"

YellowCard::YellowCard ( std::string name ) : Card (name)
{
    setScore ( stoi (name) );
} 
// std::string YellowCard::displayName()
// {
//     return "PurpleCard";
// }