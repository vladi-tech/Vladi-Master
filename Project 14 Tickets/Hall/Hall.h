#ifndef _Hall_hh
#define _Hall_hh

#include <iostream>
#include <cstring>

class Hall
{
private:
    std::string hallNumber;
    size_t numberRows;
    size_t seatsPerRow;

public:
    //Constructors and Destrutor
    Hall();

    Hall(const Hall &);

    Hall(const std::string&, const size_t &, const size_t &);

    ~Hall();

    //Operators
    Hall &operator=(const Hall &);

    bool operator==(const Hall &) const;
    bool operator==(const char *) const;

    //Setters and Getters

    char *getNumber() const;
    size_t getNumberRows() const;
    size_t getSeatsPerRow() const;

    //Additional Functions
    const char *getName() const;
    void print() const;

    bool loadData(std ::fstream &);
    bool seedData(std::fstream &);
};

#endif