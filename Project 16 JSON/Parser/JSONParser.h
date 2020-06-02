#ifndef _JsonParser_hh
#define _JsonParser_hh

#include <fstream>
#include "../JsonFactories/JsonValueFactory/JsonSimpleValueFactory.cpp"

class Parser
{
private:
    std::string fileData;

    size_t numberOfObjects;
    JsonPair *objectsInFile;

    //Additional functions to be called leter in startParser
    void inputSave();
    void inputSet();
    void inputCreate();
    void inputDelete();
    void InputMove();

    //Functions to validate the file

    bool isLeftSeparator(const char &) const;
    bool isRightSeparator(const char &) const;
    bool isSeparator(const char &) const;

    //Functions with validation
    void validateBraceCount(const std::string &, std::vector<std::string> &) const;
    void validateCrochetCount(const std::string &, std::vector<std::string> &) const;
    void validateSeparators(const size_t &, const std::string &, std::vector<std::string> &) const;

public:
    //Constructors and Destructor
    Parser();
    Parser(const Parser &);
    ~Parser();

    //Operators
    Parser &operator=(const Parser &);

    //Functions from the task guidelines
    void help() const;
    void validate() const;
    void print() const;
    void search(const std::string &) const;
    void set(const std::string &, const std::string &);
    void create(const std::string &, const std::string &);
    void deleteData(const std::string &);
    void move(const std ::string &, const std::string &);

    //File manipulation functions
    bool loadData(std::fstream &);
    bool seedData(std::fstream &);
    void open(const char *);
    void close();
    void save(const char *);
    void saveAs(const char *);

    //Main interactive function
    void startParser();
};

#endif