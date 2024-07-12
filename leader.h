#include <iostream>

#include "purple.h"

class LeaderCard :public PurpleCard{
     
     public:
        LeaderCard();
        virtual void useCard ( std::vector <Player> & players , int numPlayer ) override;

};