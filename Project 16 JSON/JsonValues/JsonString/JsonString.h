#ifndef _JsonString_hh
#define _JsonString_hh

#include <iostream>
#include "../JsonNumericValue/JsonNumericValue.cpp"

class JsonString : public JsonValue
{
private:
    std::string value;

public:
    //Constructors and Destructor
    JsonString();
    JsonString(const JsonString &);
    JsonString(const std::string &);
    ~JsonString();

    //Operators
    JsonString &operator=(const JsonString &);

    //Additional functions
    void setFind(const JsonPath &, const size_t&, const std::string&) override;
    void print() const override;
};
#endif