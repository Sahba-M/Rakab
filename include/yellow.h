#ifndef YELLOW_H
#define YELLOW_H

#include "card.h"
#include "asset.h"

class YellowCard : public Card {
    
    public:
        YellowCard( std::string name );
        virtual void draw ( int x , int y );

       
}; 

#endif