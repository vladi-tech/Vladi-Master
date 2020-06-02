#ifndef _JsonSimpleValueFactory_hh
#define _JsonSimpleValueFactory_hh

#include "../../JsonObject/JsonObject.cpp"

class JsonSimpleValueFactory
{
public:
    static JsonValue *make(const std::string &);
};
#endif