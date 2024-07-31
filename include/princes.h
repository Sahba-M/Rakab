#ifndef PRINCES_H
#define PRINCES_H

#include <iostream>

#include "purple.h"

class PrincesCard : public PurpleCard {
    public:
        virtual void useCard ( std::vector <Player> & players , int numPlayer ) override;
        void draw ( int x , int y ) override ;
};


#endif 