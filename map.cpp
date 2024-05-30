#include <iostream>
#include <unordered_map>
#include <vector>

class Map {
    public:
        void readMatrix ();
        void readUnorderedMap ();
        bool checkAdjacent ();

    private:
        std::vector < std::vector <int> > adjancencyMatrix ;
        std::unordered_map < std::string , int > provinceMap ;

};