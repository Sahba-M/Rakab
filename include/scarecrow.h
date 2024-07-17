#include "purple.h"

#ifndef SCARECROW_H
#define SCARECROW_H

class ScarecrowCard : public PurpleCard {

    public:
        ScarecrowCard ();
        void useThisCard ( Player & player );
};

#endif