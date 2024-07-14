#include <string>

#ifndef CARD_H
#define CARD_H

class Card { //The card class is a parent class

     friend std::ifstream & operator>> ( std::istream & input , Card & card );
     friend std::ostream & operator<< ( std::ostream & output , const Card & card );

   
    public:
        Card( std::string name );
        Card();
        virtual ~Card();
        void setName(std::string name);
        std::string getName();
        bool operator== (const Card & other);
  
    private:
        std::string name;
};
#endif 

