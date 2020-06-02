#include "JsonSimpleValueFactory.h"

JsonValue *JsonSimpleValueFactory::make(const std::string &valueToCreate)
{
    if (!(valueToCreate.compare("true") && valueToCreate.compare("false")))
    {
        return new JsonBool(valueToCreate);
    }
    else if (valueToCreate[0] == '"')
    {
        return new JsonString(valueToCreate);
    }
    else if (valueToCreate[0] >= '0' && valueToCreate[0] <= '9')
    {
        return new JsonNumericValue(valueToCreate);
    }

    return nullptr;
}