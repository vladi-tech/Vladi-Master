#include "JsonObject.h"

//Constructors and destructor
JsonObject::JsonObject()
{
    JsonValue::copyData(JsonValueType::Object);
}
JsonObject::JsonObject(const JsonObject &other)
{
    JsonValue::copyData(JsonValueType::Object);
    this->objectData = other.objectData;
}
JsonObject::~JsonObject()
{
    if (objectData.size())
    {
        for (int i = 0; i < objectData.size(); ++i)
        {
            delete objectData[i];
        }
    }
}

//Operators
JsonObject &JsonObject::operator=(const JsonObject &other)
{
    if (this != &other)
    {
        this->objectData = other.objectData;
    }

    return *this;
}
bool JsonObject::operator==(const JsonObject &other) const
{
    return (this->objectData == other.objectData);
}

//Additiona functions
void JsonObject::findByKey(const std::string &key, std::vector<const JsonValue *> listOfValues) const
{
    for (int i = 0; i < objectData.size(); ++i)
    {
        if (!objectData[i]->compareName(key))
        {
            objectData[i]->findByKey(key, listOfValues);
        }
    }
}
void JsonObject::setFind(const JsonPath &path, const size_t &depth, const std::string &newValue)
{
    std::vector<size_t> elementIndex;

    for (int i = 0; i < objectData.size(); ++i)
    {
        if (objectData[i]->compareName(path.getPathPairAt(depth).name))
        {
            elementIndex.push_back(i);
        }
    }

    elementIndex.shrink_to_fit();

    if (!elementIndex.size()) ///If we have no elements with the required name, then the path is not valid
    {
        std::cout << "Error! There is no element named " << path.getPathPairAt(depth).name << "!\n";
        return;
    }
    else if (elementIndex.size() > 1) ///If we have more than one element with the required name, then the path is not valid
    {
        std::cout << "Error! There are more than one elements named " << path.getPathPairAt(depth).name << "!\n";
        return;
    }
    else if (path.getPathPairAt(depth).index > -1 && objectData[elementIndex[0]]->getType() != JsonValueType::Array) ///If the desired element is not an array and we have an index in the path, then invalid
    {

        std::cout << "Error! The desired element(" << path.getPathPairAt(depth).name << ") is not an array. No index expected!";

        return;
    }
    else //If the desired element is valid, then we proceed with tracing the path to the desired element
    {
        if (path.getPathLength() == 1 && path.getPathPairAt(depth).index == -1) //If the path stops here, then we proceed to change the value
        {                                                                       //If the pair previously contained an array, but we want to change all of its content we change it here
            objectData[elementIndex[0]]->setData(newValue);
        }
        else
        { //If the path is longer or we want to change an element of the found pair's array, we continue here
            objectData[elementIndex[0]]->setFind(path, depth + 1, newValue);
        }
    }
}

void JsonObject::print() const
{
    std::cout << "\n{\n";

    for (int i = 0; i < objectData.size(); ++i)
    {
        std::cout << "    ";
        objectData[i]->print();
    }

    std::cout << "\n}\n";
}