#include<vector>
#include "card.h"

#ifndef CONTROL_H
#define CONTROL_H
class Control {
    public:
        Control(); 
        void setCards();
    private:
        std::vector<Card> cards;
};

#endif