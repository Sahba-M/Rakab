#ifndef SCARECROW_H
#define SCARECROW_H

#include "purple.h"

class ScarecrowCard : public PurpleCard {

    public:
        ScarecrowCard ();
        void useThisCard ( Player & player );
};

#endif