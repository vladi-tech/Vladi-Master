#include "JsonPath.h"

pathPair::pathPair(const std::string &_name, const size_t &_index = -1)
{
    this->name = _name;
    this->index = _index;
}

//Constructors and destructor
JsonPath::JsonPath(const std::string &inputPath)
{
    for (int i = 0; i < inputPath.size(); ++i)
    {
        std::string currPathLevel;
        size_t index = -1;

        for (; i < inputPath.size() && inputPath[i] != '.'; ++i)
        {
            currPathLevel.push_back(inputPath[i]);

            if (inputPath[i] == '[')
            {
                ++i; //We skip '['
                index = 0;
                while (inputPath[i] != ']')
                {
                    index *= 10;
                    index += (inputPath[i] - '0');
                }

                ++i; //We skip ']'
            }
        }

        pathPair temp(currPathLevel, index);
        depthLevels.push_back(temp);
    }
}

//Additional functions
size_t JsonPath::getPathLength() const
{
    return depthLevels.size();
}
pathPair JsonPath::getPathPairAt(const size_t &index) const
{
    return depthLevels[index];
}