#ifndef _JsonValue_hh
#define _JsonValue_hh

#include <iostream>
#include "../../JsonPath/JsonPath.cpp"

enum JsonValueType
{
    Null,
    Bool,
    Numeric,
    String,
    Array,
    Object
};

class JsonValue
{
private:
    JsonValueType type;

protected:
    void copyData(const JsonValueType &);

public:
    //Constructors and destructors
    JsonValue();
    ~JsonValue() = default;
    //Functions to assist those from the task requirements
    JsonValueType getType() const;

    virtual void findByKey(const std::string &, std::vector<const JsonValue *>) const;
    virtual void setFind(const JsonPath &, const size_t &, const std::string &) = 0;

    virtual void print() const = 0;
};
#endif