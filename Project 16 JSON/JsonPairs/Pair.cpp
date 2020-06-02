#include "Pair.h"

//Constructors and destructor
JsonPair::JsonPair() : pairData{nullptr}
{
}
JsonPair::JsonPair(const JsonPair &other) : name{other.name}, pairData{other.pairData} {}
JsonPair::~JsonPair()
{
    delete pairData;
}

//Operators
JsonPair &JsonPair::operator=(const JsonPair &other)
{
    if (this != &other)
    {
        this->name = other.name;
        this->pairData = other.pairData;
    }

    return *this;
}

//Additional functions
void JsonPair::findByKey(const std::string &key, std::vector<const JsonValue *> listOfValues) const
{
    if (!name.compare(key))
    {
        listOfValues.push_back(this->pairData);
    }

    pairData->findByKey(key, listOfValues);
}
bool JsonPair::compareName(const std::string &other) const
{
    return !(this->name.compare(other));
}

void JsonPair::setFind(const JsonPath &path, const size_t &pathDepth, const std::string &newValue)
{

    pairData->setFind(path, pathDepth, newValue);
}

JsonValueType JsonPair::getType() const
{
    return pairData->getType();
}
const JsonValue *JsonPair::getData() const
{
    return this->pairData;
}
void JsonPair::setData(const std::string &)
{
    delete pairData;
}
void JsonPair::print() const
{
    std::cout << name << " : ";
    pairData->print();
}