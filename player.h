#include <iostream>

class Player {
    public:
        Player();
        Player ( int age , std::string name , std::string color );
        void setName ( std::string name );
        void setAge ( int age );
        void setColor ( std::string color );
        int getAge() const ;
        std::string getName() const ;
        std::string getColor() const ;

    private:
        int age ;
        std::string name ;
        std::string color ;

};