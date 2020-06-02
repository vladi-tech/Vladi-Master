#include "JsonNumericValue.h"

//Constructors and Destructor
JsonNumericValue::JsonNumericValue()
{
    JsonValue::copyData(JsonValueType::Numeric);
    this->value = 0.0;
}
JsonNumericValue::JsonNumericValue(const JsonNumericValue &other) : value{other.value}
{
    JsonValue::copyData(JsonValueType::Numeric);
}
JsonNumericValue::JsonNumericValue(const std::string &_value)
{
    JsonValue::copyData(JsonValueType::Numeric);
    value = 0.0;
    int i = 0;

    for (; i < _value.length() && _value[i] != '.'; ++i)
    {
        value *= 10;
        value += (_value[i] - '0');
    }
    ++i;
    for (int j = 1; i < _value.length(); ++i, ++j)
    {
        value += ((_value[i] - '0') * pow(10, -j));
    }
}
JsonNumericValue::~JsonNumericValue()
{
}

JsonNumericValue &JsonNumericValue::operator=(const JsonNumericValue &other)
{
    if (this != &other)
    {
        this->value = other.value;
    }

    return *this;
}

//Additional functions

void JsonNumericValue::setFind(const JsonPath &path, const size_t &index, const std::string &newValue)
{
    std::cout << "Error! The path is too long, a numeric value is not a dictionary!\n";
}

void JsonNumericValue::print() const
{
    std::cout << value;
}