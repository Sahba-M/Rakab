#ifndef SCARECROW_H
#define SCARECROW_H

#include "purple.h"

class ScarecrowCard : public PurpleCard {

    public:
        ScarecrowCard ();
        void useThisCard ( Player & player );
        // void draw ( int x , int y ) override ;
};

#endif