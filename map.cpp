#include <iostream>
#include <unordered_map>
#include <vector>
#include <fstream>

class Map
{
public:
    void readMatrix()
    {
        std::ifstream input("matrix");
        if (!input.is_open())
            std::cerr << "Unable to open file !" << std::endl;
        int number;
        while (input)
        {
            std::vector<int> row;
            for (int i = 0; i < 3; i++)
            {
                if (input >> number)
                {
                    row.push_back(number);
                }
            }
            if (!row.empty())
            {
                adjacencyMatrix.push_back(row);
            }
        }
        input.close();
    }
    void readUnorderedMap()
    {
        std::ifstream input;
        input.open("map.txt");
        if (!input.is_open())
            std::cerr << "Unable to open file !" << std::endl;
        std::string key;
        int value;

        while (input)
        {
            if (input >> value >> key)
            {
                provinceMap[key] = value;
            }
        }
        input.close();
    }
    bool checkAdjacent(const std::string &p1, const std::string &p2)
    {
        int index1 = provinceMap[p1];
        int index2 = provinceMap[p2];
        return adjacencyMatrix[index1][index2] == 1;
    }

private:
    std::vector<std::vector<int>> adjacencyMatrix;
    std::unordered_map<std::string, int> provinceMap;
};
