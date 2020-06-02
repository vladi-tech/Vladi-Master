#include "JsonBool.h"

//Constructors and Destructor
JsonBool::JsonBool()
{
    JsonValue::copyData(JsonValueType::Bool);
    value = true;
}
JsonBool::JsonBool(const JsonBool &other) : value{other.value}
{
    JsonValue::copyData(JsonValueType::Bool);
}
JsonBool::JsonBool(const std::string &_value)
{
    JsonValue::copyData(JsonValueType::Bool);
    if (_value.compare("true") == 0)
    {
        value = true;
    }

    value = false;
}
JsonBool::~JsonBool()
{
}

//Operators
JsonBool &JsonBool::operator=(const JsonBool &other)
{
    if (this != &other)
    {
        this->value = other.value;
    }

    return *this;
}

//Additional functions

void JsonBool::setFind(const JsonPath &path, const size_t &index, const std::string &newValue)
{
    std::cout << "Error! The path is too long, a boolean value is not a dictionary!\n";
}

void JsonBool::print() const
{
    std::cout << std::boolalpha << value;
}