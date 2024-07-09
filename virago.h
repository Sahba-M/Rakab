#include "purple.h"

#ifndef VIRAGO_H
#define VIRAGO_H
class ViragoCard : public PurpleCard
{
    public:
        virtual void useCard ( std::vector <Player> & players, int numPlayer ) override ; // we don't use index here


};

#endif 
