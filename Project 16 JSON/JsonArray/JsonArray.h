#ifndef _JsonArray_hh
#define _JsonArray_hh

#include <vector>
#include "../JsonValues/JsonString/JsonString.cpp"

class JsonArray : public JsonValue
{
private:
    std::vector<JsonValue *> arrayContent;

public:
    //Constructors and destructor
    JsonArray();
    JsonArray(const JsonArray &);
    ~JsonArray();

    //Operators
    JsonArray &operator=(const JsonArray &);
    bool operator==(const JsonArray &) const;

    //Additiona functions
    void findByKey(const std::string &,std::vector<const JsonValue *>) const override;
    void setFind(const JsonPath &, const size_t&, const std::string&) override;
    
    void print() const override;
};
#endif