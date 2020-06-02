#include "JsonArray.h"

//Constructors and destructor
JsonArray::JsonArray()
{
    JsonValue::copyData(JsonValueType::Array);
}

JsonArray::JsonArray(const JsonArray &other) : arrayContent{other.arrayContent}
{
    JsonValue::copyData(JsonValueType::Array);
}

JsonArray::~JsonArray()
{
    for (int i = 0; i < arrayContent.size(); ++i)
    {
        delete arrayContent[i];
    }
};

//Operators
JsonArray &JsonArray::operator=(const JsonArray &other)
{
    if (this != &other)
    {
        this->arrayContent = other.arrayContent;
    }

    return *this;
}

bool JsonArray::operator==(const JsonArray &other) const
{
    return this->arrayContent == other.arrayContent;
}

//Additiona functions
void JsonArray::findByKey(const std::string &key, std::vector<const JsonValue *> listOfValues) const
{
    for (int i = 0; i < arrayContent.size(); ++i)
    {
        arrayContent[i]->findByKey(key, listOfValues);
    }
}
void JsonArray::setFind(const JsonPath &path, const size_t &depth, const std::string &newValue)
{
    if (path.getPathPairAt(depth).index >= arrayContent.size())
    {
        std::cout << "Error! Invalid index value for " << path.getPathPairAt(depth).name << " [?]!\n";
    }
    else if (path.getPathPairAt(depth - 1).index != -1 && path.getPathLength() == depth)
    {
        delete arrayContent[(path.getPathPairAt(depth - 1).index)];
        //arrayContent[path.getPathPairAt(depth-1).index] = newValue;
    }

    else
    {
        arrayContent[path.getPathPairAt(depth).index]->setFind(path, depth, newValue);
    }
}

void JsonArray::print() const
{
    std::cout << '[';

    if (arrayContent.size() > 0)
    {
        arrayContent[0]->print();

        for (int i = 1; i < arrayContent.size(); ++i)
        {
            std::cout << ',';
            arrayContent[i]->print();
        }
    }

    std::cout << ']';
}