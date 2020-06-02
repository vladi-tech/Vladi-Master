#include "Ticket.h"
#include <cstdlib>
#include <ctime>

void Ticket::generateUniqueNumber()
{
    std::srand(std::time(nullptr));
    int randomNumber = double(std::rand() * 1.0 / (RAND_MAX)) * 999;

    this->uniqueCode[0] = '0' + this->ticketSeat.seatNumber / 10;
    this->uniqueCode[1] = '0' + this->ticketSeat.seatNumber % 10;
    this->uniqueCode[2] = '0' + this->ticketSeat.seatRow / 10;
    this->uniqueCode[3] = '0' + this->ticketSeat.seatRow % 10;
    this->uniqueCode[4] = '0' + this->eventDate[2];
    this->uniqueCode[5] = '0' + this->eventDate[3];
    this->uniqueCode[6] = '0' + this->eventDate[5];
    this->uniqueCode[7] = '0' + this->eventDate[6];
    this->uniqueCode[8] = '0' + this->eventDate[8];
    this->uniqueCode[9] = '0' + this->eventDate[9];
    this->uniqueCode[10] = '0' + this->eventName[0];
    this->uniqueCode[11] = '0' + this->eventName[eventName.length() - 1];
    this->uniqueCode[12] = '0' + randomNumber / 100;
    this->uniqueCode[13] = '0' + (randomNumber % 100) / 10;
    this->uniqueCode[14] = '0' + randomNumber % 10;
}

Ticket::Ticket() : ticketSeat{0, 0}
{
    strcpy(this->eventDate, "2000-01-01");
    strcpy(this->uniqueCode, "00000000000000");
}

Ticket::Ticket(const Ticket &other) : eventName{other.eventName}, ticketSeat{other.ticketSeat}, note{other.note}
{
    eventName.shrink_to_fit();
    strcpy(this->eventDate, other.eventDate);

    strcpy(this->uniqueCode, other.uniqueCode);
}
Ticket::Ticket(const std::string &_name, const char *_date, const size_t &_row, const size_t &_number, const char *_note = nullptr) : eventName{_name}, ticketSeat{_row, _number}
{
    this->eventName = _name;
    eventName.shrink_to_fit();

    strcpy(this->eventDate, _date);

    if (_note != nullptr)
    {
        this->note = _note;
        note.shrink_to_fit();
    }

    generateUniqueNumber();
}
Ticket::~Ticket()
{
    strcpy(this->eventDate, "2000-01-01");
    strcpy(this->uniqueCode, "00000000000000");
}

//Operators:
Ticket &Ticket::operator=(const Ticket &other)
{
    if (this != &other)
    {
        this->eventName = other.eventName;

        strcpy(this->eventDate, other.eventDate);

        this->ticketSeat.seatRow = other.ticketSeat.seatRow;
        this->ticketSeat.seatNumber = other.ticketSeat.seatNumber;

        this->note = other.note;

        strcpy(this->uniqueCode, other.uniqueCode);
    }

    return *this;
}

bool Ticket::operator==(const Ticket &other) const
{
    return (strcmp(this->uniqueCode, other.uniqueCode) == 0);
}
bool Ticket::operator==(const char *_code) const
{
    return (strcmp(this->uniqueCode, _code) == 0);
}

//Setters and getters:
char *Ticket::getDate() const
{
    char *result = new char[11];
    strcpy(result, this->eventDate);
    return result;
}

size_t Ticket::getRow() const
{
    return ticketSeat.seatRow;
}

size_t Ticket::getSeatNumber() const
{
    return ticketSeat.seatNumber;
}

//Additional functions:
void Ticket::print() const
{
    std::cout << std::endl
              << "Event: "
              << eventName << " Date: "
              << eventDate
              << " Row: "
              << ticketSeat.seatRow
              << " Number: "
              << ticketSeat.seatNumber;

    if (note.size())
    {
        std::cout << std::endl
                  << "Note: "
                  << note;
    }

    ///We will not be printing the ticket's code, as it is unique and is the only way to validate if the ticket is real or not.
}

bool Ticket::checkIfFor(const char *_eventName = nullptr, const char *_eventDate = nullptr) const
{
    if (_eventDate == nullptr)
    {
        return (!eventName.compare(_eventName));
    }
    else if (_eventName == nullptr)
    {
        return (!strcmp(this->eventDate, _eventDate));
    }

    return (!eventName.compare(_eventName) && !strcmp(this->eventDate, _eventDate));
}
bool Ticket::compareByData(const char *_eventName, const char *_eventDate, const size_t &_row, const size_t &_seat) const
{
    return (!eventName.compare(_eventName) && !strcmp(this->eventDate, _eventDate) && (ticketSeat.seatRow == _row) && (ticketSeat.seatNumber == _seat));
}
bool Ticket::checkInPeriod(const char *from, const char *to) const
{
    return ((strcmp(from, this->eventDate) <= 0) && (strcmp(this->eventDate, to) >= 0));
}

bool Ticket::loadData(std::fstream &file)
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

    for (int i = 0; i < 10; ++i)
    {
        if (!file.read((char *)&eventDate[i], sizeof(char)))
        {
            file.close();
            return 0;
        }
    }
    eventDate[10] = '\0';

    if (!file.read((char *)&ticketSeat.seatRow, sizeof(size_t)))
    {
        file.close();
        return 0;
    }
    if (!file.read((char *)&ticketSeat.seatNumber, sizeof(size_t)))
    {
        file.close();
        return 0;
    }

    if (!file.read((char *)&sizeHolder, sizeof(size_t)))
    {
        file.close();
        return 0;
    }

    if (sizeHolder)
    {
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
            note.push_back(symbol);
        }
    }

    for (int i = 0; i < 15; ++i)
    {
        if (!file.read((char *)&uniqueCode[i], sizeof(char)))
        {
            file.close();
            return 0;
        }
    }
    uniqueCode[15] = '\0';

    return 1;
}

bool Ticket::seedData(std::fstream &file)
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

    if (!file.write((const char *)&ticketSeat.seatRow, sizeof(size_t)))
    {
        file.close();
        return 0;
    }

    if (!file.write((const char *)&ticketSeat.seatNumber, sizeof(size_t)))
    {
        file.close();
        return 0;
    }

    sizeHolder = note.length();
    if (!file.write((const char *)&sizeHolder, sizeof(size_t)))
    {
        file.close();
        return 0;
    }

    if (sizeHolder)
    {
        for (int i = 0; i < sizeHolder; i++)
        {
            if (!file.write((const char *)&note[i], sizeof(char)))
            {
                file.close();
                return 0;
            }
        }
    }

    for (int i = 0; i < 15; ++i)
    {
        if (!file.write((const char *)&uniqueCode[i], sizeof(char)))
        {
            file.close();
            return 0;
        }
    }

    return 1;
}
