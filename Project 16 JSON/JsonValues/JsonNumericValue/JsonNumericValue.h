#ifndef _JsonNumericValue_hh
#define _JsonNumericValue_hh

#include <cmath>
#include "../JsonBool/JsonBool.cpp"

class JsonNumericValue : public JsonValue
{
private:
    double value;

public:
    //Constructors and Destructor
    JsonNumericValue();
    JsonNumericValue(const JsonNumericValue &);
    JsonNumericValue(const std::string &);
    ~JsonNumericValue();

    //Operators
    JsonNumericValue &operator=(const JsonNumericValue &);

    //Additional functions

    void setFind(const JsonPath &, const size_t &, const std::string &) override;

    void print() const override;
};
#endif