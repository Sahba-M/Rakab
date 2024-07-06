#include <iostream>

#include "purple.h"

class leaderCard :public PurpleCard{
     
     public:
        leaderCard();
        virtual void useCard ( std::vector <Player> & players , int numPlayer ) override;

};