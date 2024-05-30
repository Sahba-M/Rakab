#include <iostream>
#include <unordered_map>
#include <vector>
#include <fstream>

class Map {
    public:
        void readMatrix ()
        {
            std::ifstream input ("matrix") ; 
            if (!input.is_open()) 
                std::cerr << "Unable to open file !" << std::endl ;
            int number;
            while (input) 
            {
                std::vector <int> row;
                for ( int i = 0 ; i < 3 ; i++ ) 
                {
                    if ( input >> number )   
                    {
                    row.push_back(number);
                    }
                }
                if (!row.empty()) 
                {
                adjancencyMatrix.push_back(row);
                }
            }
            input.close();  
        }
        void readUnorderedMap ();
        bool checkAdjacent ();

    private:
        std::vector < std::vector <int> > adjancencyMatrix ;
        std::unordered_map < std::string , int > provinceMap ;

};