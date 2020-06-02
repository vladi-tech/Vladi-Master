#ifndef _Pair_hh
#define _Pair_hh

#include <iostream>
#include <string>
#include "../JsonArray/JsonArray.cpp"

class JsonPair
{
private:
    std::string name;
    JsonValue *pairData;

protected:
public:
    //Constructors and destructor
    JsonPair();
    JsonPair(const JsonPair &);
    ~JsonPair();

    //Operators
    JsonPair &operator=(const JsonPair &);

    //Additional functions
    void findByKey(const std::string &,std::vector<const JsonValue *>) const;
    bool compareName(const std::string &) const;
    void setFind(const JsonPath &, const size_t &, const std::string &);

    JsonValueType getType() const;
    const JsonValue *getData() const;
    void setData(const std::string &);

    size_t getSize() const;
    void print() const;
};
#endif