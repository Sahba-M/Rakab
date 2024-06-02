#include <iostream>

#include "purple.h"

PurpleCard::PurpleCard ( std::string name , int priority , int score ) : Card(score)
{
    this->name = name ;
    this->priority = priority ;
}
