#ifndef _Ticket_hh
#define _Ticket_hh
#include "..\Event\Event.cpp"

class Ticket
{
private:
    std::string eventName;
    char eventDate[11];
    Seat ticketSeat;
    std::string note;
    char uniqueCode[16]; ///The code will be seat,row,YYMMDD, first letter of event, last letter of event and random number from 1-999, exaple: 1810200625Ne805

    void generateUniqueNumber();

public:
    //Constructors and Destructor:
    Ticket();
    Ticket(const Ticket &);
    Ticket(const std::string&, const char *, const size_t &, const size_t &, const char *);
    ~Ticket();

    //Operators:
    Ticket &operator=(const Ticket &);
    bool operator==(const Ticket &) const;
    bool operator==(const char *) const;

    //Setters and getters:
    char *getDate() const;
    size_t getRow() const;
    size_t getSeatNumber() const;

    //Additional functions:
    void print() const;
    bool checkIfFor(const char *, const char *) const;
    bool compareByData(const char *, const char *, const size_t &, const size_t &) const;
    bool checkInPeriod(const char *, const char *) const;

    bool loadData(std ::fstream &);
    bool seedData(std::fstream &);
};

#endif