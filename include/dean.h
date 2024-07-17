#ifndef DEAN_H
#define DEAN_H

#include "purple.h"

class DeanCard : public PurpleCard
{
    public:
        DeanCard();
        virtual void useCard ( std::vector <Player> & players , int numPlayer ) override ; // we don't use index here
        int findMaxScore ( std::vector <Player> players ); 
        std::vector<int> findMaxPlayer ( std::vector <Player> players );
        


};


#endif 
