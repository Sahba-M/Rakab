#include <iostream>
#include "control.h"

int main()
{
    Control control ;
    control.setCards();
    control.shuffleCards(); 
    control.controlNumber();
    control.getInformation();

    
    return 0;
}