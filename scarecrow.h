#include "purple.h"

#ifndef SCARECROW_H
#define SCARECROW_H

class ScarecrowCard : public PurpleCard {

    public:
        ScarecrowCard ();
        virtual void useCard(std::vector <Player> players, int numPlayer = 0 ) override;

    private:

};

#endif