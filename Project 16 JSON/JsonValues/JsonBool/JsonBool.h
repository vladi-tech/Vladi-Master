#ifndef _JsonBool_hh
#define _JsonBool_hh
#include "../JsonBaseValue/JsonValue.cpp"

class JsonBool : public JsonValue
{
private:
    bool value;

public:
    //Constructors and Destructor
    JsonBool();
    JsonBool(const JsonBool &other);
    JsonBool(const std::string &_value);
    ~JsonBool();

    //Operators
    JsonBool &operator=(const JsonBool &);

    //Additional functions
    
    void setFind(const JsonPath &, const size_t &, const std::string &) override;

    void print() const override;
};
#endif