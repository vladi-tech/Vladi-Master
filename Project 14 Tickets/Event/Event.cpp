#include "Event.h"

//Constructors and Destructors:
Event::Event()
{
    strcpy(eventDate, "2000-01-01");
}

Event::Event(const Event &other) : eventName{other.eventName}, eventHall{other.eventHall}, bookedSeats{other.bookedSeats}, soldSeats{other.soldSeats}
{
    strcpy(this->eventDate, other.eventDate);
    eventName.shrink_to_fit();
    bookedSeats.shrink_to_fit();
    soldSeats.shrink_to_fit();
}

Event::Event(const std::string &_eventName, const char *_eventDate, const Hall &_eventHall) : eventName{_eventName}, eventHall{_eventHall}
{
    strcpy(this->eventDate, _eventDate);
    eventName.shrink_to_fit();
}

Event::Event(const std::string &_eventName, const char *_eventDate, const Hall &_eventHall, std::vector<Seat> _bookedSeats, std::vector<Seat> _soldSeats) : eventName{_eventName},
                                                                                                                                                            eventHall{_eventHall}, bookedSeats{bookedSeats}, soldSeats{soldSeats}

{
    eventName.shrink_to_fit();
    bookedSeats.shrink_to_fit();
    soldSeats.shrink_to_fit();
    strcpy(this->eventDate, _eventDate);
}

Event::~Event()
{
}

//Operators:
Event &Event::operator=(const Event &other)
{
    if (this != &other)
    {
        this->eventName = other.eventName;

        strcpy(this->eventDate, other.eventDate);

        this->eventHall = other.eventHall;

        this->bookedSeats = other.bookedSeats;

        this->soldSeats = other.soldSeats;
    }

    return *this;
}
bool Event::operator==(const Event &other) const
{
    return ((!this->eventName.compare(other.eventName)) && (strcmp(this->eventDate, other.eventDate) == 0) && (this->eventHall == other.eventHall));
}

//Additional functions:
char *Event::getName() const
{
    char *result = new char[this->eventName.length() + 1];
    strcpy(result, eventName.c_str());
    return result;
}

char *Event::getDate() const
{
    char *result = new char[11];
    strcpy(result, this->eventDate);
    return result;
}

char *Event::getHallNumber() const
{
    return this->eventHall.getNumber();
}

size_t Event::getNumberSoldSeats() const
{
    return this->soldSeats.size();
}

double Event::getAttendacePercentage() const
{
    double coefficient = double(this->soldSeats.size() / (1.0 * (this->eventHall.getNumberRows() * this->eventHall.getSeatsPerRow())));
    return coefficient;
}

//Additional functions:

void Event::print() const
{
    std::cout << std::endl
              << "Event: "
              << eventName
              << std::endl
              << "Date: "
              << eventDate
              << std::endl
              << "Hall: "
              << eventHall.getNumber()
              << std::endl;
}

bool Event::checkIfBooked(const size_t &row, const size_t &number)
{
    if (row < 0 || eventHall.getNumberRows() < row || number < 0 || eventHall.getSeatsPerRow() < number)
    {
        std::cout << std::endl
                  << "Invalid row or seat data, rows are "
                  << eventHall.getNumberRows()
                  << " and the number of seats per row is "
                  << eventHall.getSeatsPerRow() << ".";

        return 1;
    }

    for (int i = 0; i < bookedSeats.size(); ++i)
    {
        if (bookedSeats[i].seatRow == row && bookedSeats[i].seatNumber == number)
        {
            return 1;
        }
    }

    return 0;
}

bool Event::checkIfSold(const size_t &row, const size_t &number)
{

    for (int i = 0; i < soldSeats.size(); ++i)
    {
        if (soldSeats[i].seatRow == row && soldSeats[i].seatNumber == number)
        {
            return 1;
        }
    }

    return 0;
}

bool Event::unbookSeat(const size_t &row, const size_t &number)
{
    if (row < 0 || eventHall.getNumberRows() < row || number < 0 || eventHall.getSeatsPerRow() < number)
    {
        std::cout << std::endl
                  << "Invalid row or seat data, rows are "
                  << eventHall.getNumberRows()
                  << " and the number of seats per row is "
                  << eventHall.getSeatsPerRow() << ".\n";

        return 0;
    }

    for (int i = 0; i < bookedSeats.size(); ++i)
    {
        if (bookedSeats[i].seatRow == row && bookedSeats[i].seatNumber == number)
        {
            bookedSeats[i].seatRow = bookedSeats[bookedSeats.size() - 1].seatRow; //We will transfer the data of the last seat to the current one, then removing the excessive copy
            bookedSeats[i].seatNumber = bookedSeats[bookedSeats.size() - 1].seatNumber;

            bookedSeats.pop_back();

            std::cout << std::endl
                      << "Seat successfully unbooked!"
                      << std::endl;
            return 1;
        }
    }

    std::cout << std::endl
              << "The requested seat has not been booked yet!"
              << std::endl;
    return 0;
}

void Event::printFreeSeats() const
{
    bool seatDistribution[eventHall.getNumberRows()][eventHall.getSeatsPerRow()];

    for (int i = 0; i < eventHall.getNumberRows(); ++i)
    {
        for (int j = 0; j < eventHall.getSeatsPerRow(); ++j)
        {
            seatDistribution[i][j] = true;
        }
    }

    for (int i = 0; i < soldSeats.size(); i++)
    {
        seatDistribution[soldSeats[i].seatRow - 1][soldSeats[i].seatNumber - 1] = false;
    }
    for (int i = 0; i < bookedSeats.size(); i++)
    {
        seatDistribution[bookedSeats[i].seatRow - 1][bookedSeats[i].seatNumber - 1] = false;
    }

    std::cout << std::endl
              << "Free seats for "
              << eventName
              << " on "
              << eventDate
              << ":\n";

    for (int i = 0; i < eventHall.getNumberRows(); ++i)
    {
        std::cout << "On row "
                  << i + 1
                  << ":";

        for (int j = 0; j < eventHall.getSeatsPerRow(); ++j)
        {
            if (seatDistribution[i][j])
            {
                std::cout << " "
                          << j + 1;
            }
        }

        std::cout << std::endl;
    }
}

void Event::bookSeat(const size_t &row, const size_t &seat)
{
    Seat toBeBooked(row, seat);

    bookedSeats.push_back(toBeBooked);
}

void Event::sellSeat(const size_t &row, const size_t &seat)
{
    Seat toBeSold(row, seat);

    soldSeats.push_back(toBeSold);
}

bool Event::loadData(std::fstream &file)
{
    size_t sizeHolder;
    if (!file.read((char *)&sizeHolder, sizeof(size_t)))
    {
        file.close();
        return 0;
    }

    for (int i = 0; i < sizeHolder; ++i)
    {
        char symbol;
        if (!file.read((char *)&symbol, sizeof(char)))
        {
            file.close();
            return 0;
        }
        eventName.push_back(symbol);
    }

    eventName.shrink_to_fit();

    for (int i = 0; i < 10; ++i)
    {
        if (!file.read((char *)&eventDate[i], sizeof(char)))
        {
            file.close();
            return 0;
        }
    }
    eventDate[10] = '\0';

    if (!eventHall.loadData(file))
    {
        file.close();
        return 0;
    }

    if (!file.read((char *)&sizeHolder, sizeof(size_t)))
    {
        file.close();
        return 0;
    }

    for (int i = 0; i < sizeHolder; ++i)
    {
        Seat currSeat;
        if (!file.read((char *)&currSeat.seatRow, sizeof(size_t)))
        {
            file.close();
            return 0;
        }
        if (!file.read((char *)&currSeat.seatNumber, sizeof(size_t)))
        {
            file.close();
            return 0;
        }

        bookedSeats.push_back(currSeat);
    }

    bookedSeats.shrink_to_fit();

    if (!file.read((char *)&sizeHolder, sizeof(size_t)))
    {
        file.close();
        return 0;
    }

    for (int i = 0; i < sizeHolder; ++i)
    {
        Seat currSeat;

        if (!file.read((char *)&currSeat.seatRow, sizeof(size_t)))
        {
            file.close();
            return 0;
        }
        if (!file.read((char *)&currSeat.seatNumber, sizeof(size_t)))
        {
            file.close();
            return 0;
        }

        soldSeats.push_back(currSeat);
    }

    soldSeats.shrink_to_fit();

    return 1;
}

bool Event::seedData(std::fstream &file)
{
    size_t sizeHolder = eventName.length();
    if (!file.write((const char *)&sizeHolder, sizeof(size_t)))
    {
        file.close();
        return 0;
    }

    for (int i = 0; i < sizeHolder; i++)
    {
        if (!file.write((const char *)&eventName[i], sizeof(char)))
        {
            file.close();
            return 0;
        }
    }

    for (int i = 0; i < 10; i++)
    {
        if (!file.write((const char *)&eventDate[i], sizeof(char)))
        {
            file.close();
            return 0;
        }
    }

    if (!eventHall.seedData(file))
    {
        file.close();
        return 0;
    }

    sizeHolder = bookedSeats.size();
    if (!file.write((const char *)&sizeHolder, sizeof(size_t)))
    {
        file.close();
        return 0;
    }

    for (int i = 0; i < sizeHolder; ++i)
    {
        if (!file.write((const char *)&bookedSeats[i].seatRow, sizeof(size_t)))
        {
            file.close();
            return 0;
        }

        if (!file.write((const char *)&bookedSeats[i].seatNumber, sizeof(size_t)))
        {
            file.close();
            return 0;
        }
    }

    sizeHolder = soldSeats.size();
    if (!file.write((const char *)&sizeHolder, sizeof(size_t)))
    {
        file.close();
        return 0;
    }

    for (int i = 0; i < sizeHolder; ++i)
    {
        if (!file.write((const char *)&soldSeats[i].seatRow, sizeof(size_t)))
        {
            file.close();
            return 0;
        }

        if (!file.write((const char *)&soldSeats[i].seatNumber, sizeof(size_t)))
        {
            file.close();
            return 0;
        }
    }

    return 1;
}