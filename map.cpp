#include <iostream>
#include <unordered_map>
#include <vector>

class Map {
    public:
        void setMatrix ();
        void setMap ();
        bool checkAdjacent ();

    private:
        std::vector < std::vector <int> > adjancencyMatrix ;
        std::unordered_map < std::string , int > provinceMap ;

};