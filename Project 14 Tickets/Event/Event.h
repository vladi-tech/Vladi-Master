#ifndef _Event_hh
#define _Event_hh

#include "..\Hall\Hall.cpp"
#include<vector>

struct Seat
{
    size_t seatRow;
    size_t seatNumber;

    Seat()
    {
        seatRow = 0;
        seatNumber = 0;
    }

    Seat(const size_t &_seatRow, const size_t &_seatNumber) : seatRow{_seatRow}, seatNumber{_seatNumber} {};

    Seat(const Seat &other) : seatRow{other.seatRow}, seatNumber{other.seatNumber} {};

    bool operator==(const Seat &other)
    {
        return ((this->seatRow == other.seatRow) && (this->seatNumber == other.seatNumber));
    }
};

class Event
{
private:
    std::string eventName;
    char eventDate[11]; //The Iso 8601 format is YYYY-MM-DD, hence we need 10 fields in order to store the date
    Hall eventHall;

    std::vector<Seat> bookedSeats;

    std::vector<Seat> soldSeats;

public:
    //Constructors and Destructors:
    Event();
    Event(const Event &);
    Event(const std::string&, const char *, const Hall &);
    Event(const std::string&, const char *, const Hall &, const std::vector<Seat>, const std::vector<Seat>);
    ~Event();

    //Operators:
    Event &operator=(const Event &);
    bool operator==(const Event &) const;

    //Setters and Getters:
    char *getName() const;
    char *getDate() const;
    char *getHallNumber() const;
    size_t getNumberSoldSeats() const;
    double getAttendacePercentage() const;

    //Additional functions:

    bool checkIfBooked(const size_t &, const size_t &);
    bool checkIfSold(const size_t &, const size_t &);

    bool unbookSeat(const size_t &, const size_t &);
    void printFreeSeats() const;
    void bookSeat(const size_t &, const size_t &);
    void sellSeat(const size_t &, const size_t &);
    void print() const;

    bool loadData(std ::fstream &);
    bool seedData(std::fstream &);
};

#endif