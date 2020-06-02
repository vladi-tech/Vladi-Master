#ifndef _JsonObject_hh
#define _JsonObject_hh

#include "../JsonPairs/Pair.cpp"

class JsonObject : public JsonValue
{
private:
    std::vector<JsonPair *> objectData;

    

public:
    //Constructors and destructor
    JsonObject();
    JsonObject(const JsonObject &);
    ~JsonObject();

    //Operators
    JsonObject &operator=(const JsonObject &);
    bool operator==(const JsonObject &) const;

    //Additiona functions
    void findByKey(const std::string &,std::vector<const JsonValue *>) const override;
    void setFind(const JsonPath &, const size_t &, const std::string &) override;

    void print() const override;
};
#endif