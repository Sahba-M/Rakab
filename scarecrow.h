#include "purple.h"

#ifndef SCARECROW_H
#define SCARECROW_H

class ScarecrowCard : public PurpleCard {

    public:
        ScarecrowCard ();
        virtual void useCard(Player &player) override;

    private:

};

#endif