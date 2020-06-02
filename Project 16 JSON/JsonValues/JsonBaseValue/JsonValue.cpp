#include "JsonValue.h"

void JsonValue::copyData(const JsonValueType &dataType)
{
    this->type = dataType;
}

//Constructors and destructors
JsonValue::JsonValue() : type{JsonValueType::Null} {}

//Additional Functions
JsonValueType JsonValue::getType() const
{
    return this->type;
}

void JsonValue::findByKey(const std::string &key,std::vector<const JsonValue *> listOfValues) const
{
    return;
}