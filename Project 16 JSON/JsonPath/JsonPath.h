#ifndef _JsonPath_hh
#define _JsonPath_hh

struct pathPair
{
    std::string name;
    size_t index;

    pathPair(const std::string &, const size_t &);
};

class JsonPath
{
private:
    std::vector<pathPair> depthLevels;

public:
    //Construcors and destructor
    JsonPath() = delete;
    JsonPath(const std::string &);
    ~JsonPath() = default;

    //Operators
    //Additional functions
    size_t getPathLength() const;
    pathPair getPathPairAt(const size_t&) const;
};
#endif