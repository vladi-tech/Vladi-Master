#include "JsonString.h"

//Constructors and Destructor
JsonString::JsonString()
{
    JsonValue::copyData(JsonValueType::String);
}
JsonString::JsonString(const JsonString &other) : value{other.value}
{
    JsonValue::copyData(JsonValueType::String);
}
JsonString::JsonString(const std::string &_value)
{
    JsonValue::copyData(JsonValueType::String);
    this->value = _value;
}
JsonString::~JsonString()
{
}
//Operators
JsonString &JsonString::operator=(const JsonString &other)
{
    if (this != &other)
    {
        this->value = other.value;
    }

    return *this;
}

void JsonString::setFind(const JsonPath &path, const size_t &index, const std::string &newValue)
{
    std::cout << "Error! The path is too long, a string value is not a dictionary!\n";
}

void JsonString::print() const
{
    std::cout << value;
}