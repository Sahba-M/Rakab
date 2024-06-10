#include <iostream>

#include "purple.h"



class Princes :public PurpleCard
{
    public:
        virtual void setPriority() override;
        void setPower();


    private:
        int power;
    

};