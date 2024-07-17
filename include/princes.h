#include <iostream>

#include "purple.h"

class PrincesCard : public PurpleCard {
    public:
        virtual void useCard ( std::vector <Player> & players , int numPlayer ) override;
};