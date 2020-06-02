#include "TicketCenter.h"
#include <string>

//Manipulating the stored data

void TicketCenter::removeBookedTicket(const char *_eventName, const char *_eventDate, const size_t &_row, const size_t &_seat)
{
    for (int i = 0; i < bookedTickets.size() - 1; ++i)
    {
        if (bookedTickets[i].compareByData(_eventName, _eventDate, _row, _seat))
        {
            bookedTickets[i] = bookedTickets[bookedTickets.size() - 1]; //If we find a match, we will transfer the data of the last ticket to the current one, then remove the extra copy
            bookedTickets.pop_back();
        }
    }
}

//Functions from input
void TicketCenter::findNote(std::string &eventName, std::string &note)
{
    for (int i = 0; i < eventName.size(); ++i)
    {
        if (eventName[i] == '#' && eventName[i + 1] == '!') ///We will use the combination #! as a sign of the start of the note
        {
            i = i + 2;
            for (; i < eventName.size(); ++i)
            {
                note.push_back(eventName[i]);
            }

            for (int j = note.size(); j > 0; --j)
            {
                eventName.pop_back();
            }

            if (eventName[eventName.size() - 1] == '!')
            {
                eventName.pop_back();
            }
            if (eventName[eventName.size() - 1] == '#')
            {
                eventName.pop_back();
            }
            if (eventName[eventName.size() - 1] == ' ')
            {
                eventName.pop_back();
            }
        }
    }
}

//Additional help finctions

//lowAttendanceFromTo
void TicketCenter::lowAttendancePrint(const std::vector<Event> &eventsUnderTenPercent) const
{
    if (!eventsUnderTenPercent.size())
    {
        std::cout << std::endl
                  << "There are no events with attendance lower than 10%!\n";
        return;
    }

    std::cout << std::endl
              << "There are "
              << eventsUnderTenPercent.size()
              << " events with attendance lower thatn 10%:!\n";

    for (int i = 0; i < eventsUnderTenPercent.size(); ++i)
    {
        eventsUnderTenPercent[i].print();
        std::cout << "Attendance percentage: "
                  << eventsUnderTenPercent[i].getAttendacePercentage()
                  << std::endl;
    }
}

void TicketCenter::removeLowAttendance()
{
    std::cout << std::endl
              << "Would you like to cancel the low attendance events? (Y/N)?\n";

    char input;
    std::cin >> input;

    while (input != 'Y' && input != 'y' && input != 'N' && input != 'n')
    {
        std::cout << std::endl
                  << "Invalid input, please choose Y/N\n";
        std::cin >> input;
    }

    if (input == 'Y' || input == 'y')
    {
        std::vector<Event> overTenPercent;

        for (int i = 0; i < availableEvents.size(); ++i)
        {
            if (availableEvents[i].getAttendacePercentage() >= 0.1)
            {
                overTenPercent.push_back(availableEvents[i]);
            }
        }

        availableEvents = overTenPercent;
        std::cout << std::endl
                  << "Events successfully removed!\n";
    }
}
void TicketCenter::reportWithoutHall(const char *from, const char *to) const
{
    std::cout << " :"
              << std::endl;

    for (int i = 0; i < availableEvents.size(); ++i)
    {
        char *temp = availableEvents[i].getDate();
        if (strcmp(from, temp) < 0 && strcmp(temp, to) < 0)
        {
            std::cout << std::endl;
            availableEvents[i].print();

            std::cout << std::endl
                      << "Number of tickets for event: "
                      << availableEvents[i].getNumberSoldSeats()
                      << std::endl;
        }
        delete[] temp;
    }
}
void TicketCenter::reportWithHall(const char *from, const char *to, const char *hall) const
{
    std::cout << " in hall "
              << hall
              << " :"
              << std::endl;

    for (int i = 0; i < availableEvents.size(); ++i)
    {
        char *temp = availableEvents[i].getHallNumber();

        if (strcmp(temp, hall) == 0)
        {
            delete[] temp;
            temp = availableEvents[i].getDate();
            if (strcmp(from, temp) < 0 && strcmp(temp, to) < 0)
            {
                std::cout << std::endl;
                availableEvents[i].print();

                std::cout << std::endl
                          << "Number of tickets for event: "
                          << availableEvents[i].getNumberSoldSeats()
                          << std::endl;
            }
        }

        delete[] temp;
    }
}
bool TicketCenter::validateDate(const std::string &eventDate) const
{
    if (eventDate.length() != 10 || (eventDate[4] != '-') || (eventDate[7] != '-'))
    {
        std::cout << "Invalid length of the date or the date does not math the ISO8601 format!\n";
        return 0;
    }

    char year[5] = {eventDate[0], eventDate[1], eventDate[2], eventDate[3]};
    char month[3] = {eventDate[5], eventDate[6]};
    char date[3] = {eventDate[8], eventDate[9]};

    if (strcmp(year, "2020") < 0 || strcmp(year, "2030") > 0)
    {
        std::cout << "Error, the year is not in the valid range (2020-2030)!\n";
        return 0;
    }

    if (strcmp(month, "01") < 0 || strcmp(month, "12") > 0)
    {
        std::cout << "Error, the month is not in the valid range (01-12)!\n";
        return 0;
    }

    if (strcmp(date, "01") < 0 || strcmp(date, "31") > 0)
    {
        std::cout << "Error, the date is not in the valid range (01-31)!\n";
        return 0;
    }

    return 1;
}
//Find the required data
size_t TicketCenter::findEventByNameDate(const char *_eventName = nullptr, const char *_eventDate = nullptr) const
{
    for (int i = 0; i < availableEvents.size(); ++i)
    {
        char *temp = availableEvents[i].getName();

        if (strcmp(temp, _eventName) == 0)
        {
            delete[] temp;
            temp = availableEvents[i].getDate();
            if (strcmp(temp, _eventDate) == 0)
            {
                delete[] temp;
                return i;
            }
        }

        delete[] temp;
    }

    std::cout << "There is no such event!";
    return availableEvents.size() + 1;
}

//DataLoading
bool TicketCenter::loadHalls(std::fstream &file)
{
    size_t sizeHolder;

    if (!file.read((char *)&sizeHolder, sizeof(size_t)))
    {
        file.close();
        return 0;
    }

    for (int i = 0; i < sizeHolder; ++i)
    {
        Hall temp;

        if (!temp.loadData(file))
        {
            file.close();
            return 0;
        }

        availableHalls.push_back(temp);
    }

    std::cout << "Halls Loaded!";

    return 1;
}
bool TicketCenter::loadEvents(std::fstream &file)
{
    size_t sizeHolder;

    if (!file.read((char *)&sizeHolder, sizeof(size_t)))
    {
        file.close();
        return 0;
    }

    for (int i = 0; i < sizeHolder; ++i)
    {
        Event temp;

        if (!temp.loadData(file))
        {
            file.close();
            return 0;
        }

        availableEvents.push_back(temp);
    }

    std::cout << "Events Loaded!";
    return 1;
}
bool TicketCenter::loadBookedTickets(std::fstream &file)
{
    size_t sizeHolder;

    if (!file.read((char *)&sizeHolder, sizeof(size_t)))
    {
        file.close();
        return 0;
    }

    for (int i = 0; i < sizeHolder; ++i)
    {
        Ticket temp;
        if (!temp.loadData(file))
        {
            file.close();
            return 0;
        }

        bookedTickets.push_back(temp);
    }

    std::cout << "booked Loaded!";
    return 1;
}
bool TicketCenter::loadSoldTickets(std::fstream &file)
{
    size_t sizeHolder;

    if (!file.read((char *)&sizeHolder, sizeof(size_t)))
    {
        file.close();
        return 0;
    }

    for (int i = 0; i < sizeHolder; ++i)
    {
        Ticket temp;

        if (!temp.loadData(file))
        {
            file.close();
            return 0;
        }

        soldTickets.push_back(temp);
    }

    std::cout << "sold Loaded!";
    return 1;
}

//DataSeeding
bool TicketCenter::seedEvents(std::fstream &file)
{
    size_t sizeHolder = availableEvents.size();
    if (!file.write((char *)&sizeHolder, sizeof(size_t)))
    {
        file.close();
        return 0;
    }

    for (int i = 0; i < sizeHolder; ++i)
    {
        if (!availableEvents[i].seedData(file))
        {
            file.close();
            return 0;
        }
    }

    return 1;
}
bool TicketCenter::seedBookedTickets(std::fstream &file)
{
    size_t sizeHolder = bookedTickets.size();
    if (!file.write((char *)&sizeHolder, sizeof(size_t)))
    {
        file.close();
        return 0;
    }

    for (int i = 0; i < sizeHolder; ++i)
    {
        if (!bookedTickets[i].seedData(file))
        {
            file.close();
            return 0;
        }
    }

    return 1;
}
bool TicketCenter::seedSoldTickets(std::fstream &file)
{
    size_t sizeHolder = soldTickets.size();
    if (!file.write((char *)&sizeHolder, sizeof(size_t)))
    {
        file.close();
        return 0;
    }

    for (int i = 0; i < sizeHolder; ++i)
    {
        if (!soldTickets[i].seedData(file))
        {
            file.close();
            return 0;
        }
    }

    return 1;
}
//Constructors and Destructor
TicketCenter::TicketCenter()
{
}
TicketCenter::TicketCenter(const TicketCenter &other) : availableHalls{other.availableHalls}, availableEvents{other.availableEvents}, bookedTickets{other.bookedTickets}, soldTickets{other.soldTickets}
{
}
TicketCenter::~TicketCenter()
{
}

//Operators
TicketCenter &TicketCenter::operator=(const TicketCenter &other)
{
    if (this != &other)
    {
        this->availableHalls = other.availableHalls;
        this->availableEvents = other.availableEvents;
        this->bookedTickets = other.bookedTickets;
        this->soldTickets = other.soldTickets;
    }

    return *this;
}

//Functions according to the desired command that require additonal input
void TicketCenter::commandAddEvent()
{
    std::string eventDate;
    std::cin >> eventDate;

    std::string eventHall;
    std::cin >> eventHall;

    std::string eventName;
    getline(std::cin, eventName);

    if (!validateDate(eventDate) || eventHall.empty() || eventName.empty())
    {
        std::cout << std::endl
                  << "Invalid output, please make sure your date is correctly input(YYYY-MM-DD), as well as that you have input the hall number and event name\n";
    }
    else
    {
        addEvent(eventName.c_str() + 1, eventDate.c_str(), eventHall.c_str());
    }
}
void TicketCenter::commandFreeSeats() const
{
    std::string eventDate;
    std::cin >> eventDate;

    std::string eventName;
    getline(std::cin, eventName);

    if (!validateDate(eventDate) || eventName.length() == 0)
    {
        std::cout << std::endl
                  << "Invalid output, please make sure your date is correctly input(YYYY-MM-DD), as well as that you have input the hall number and event name\n";
    }
    else
    {
        freeSeats(eventName.c_str() + 1, eventDate.c_str());
    }
}
void TicketCenter::commandBookTicket()
{
    size_t row;
    size_t seat;
    std::string eventDate;
    std::string eventName;
    std::string note;

    std::cin >> row >> seat >> eventDate;
    getline(std::cin, eventName);

    if (!validateDate(eventDate) || eventName.empty())
    {
        std::cout << std::endl
                  << "Invalid output, please make sure your date is correctly input(YYYY-MM-DD), as well as that you have input the hall number and event name\n";
    }
    else
    {
        findNote(eventName, note);

        book(eventName.c_str() + 1, eventDate.c_str(), row, seat, note.c_str());
    }
}
void TicketCenter::commandUnbookTicket()
{
    size_t row;
    size_t seat;
    std::string eventDate;
    std::string eventName;

    std::cin >> row >> seat >> eventDate;
    getline(std::cin, eventName);

    if (!validateDate(eventDate) || eventName.empty())
    {
        std::cout << std::endl
                  << "Invalid output, please make sure your date is correctly input(YYYY-MM-DD), as well as that you have input the hall number and event name\n";
    }
    else
    {
        unbook(eventName.c_str() + 1, eventDate.c_str(), row, seat);
    }
}
void TicketCenter::commandBuyTicket()
{
    size_t row;
    size_t seat;
    std::string eventDate;
    std::string eventName;

    std::cin >> row >> seat >> eventDate;
    getline(std::cin, eventName);

    if (!validateDate(eventDate) || eventName.empty())
    {
        std::cout << std::endl
                  << "Invalid output, please make sure your date is correctly input(YYYY-MM-DD), as well as that you have input the hall number and event name\n";
    }
    else
    {

        buy(eventName.c_str() + 1, eventDate.c_str(), row, seat);
    }
}
void TicketCenter::commandBookings() const
{
    std::string input;
    std::getline(std::cin, input);

    std::string date;
    std::string event;
    int i = 1;

    for (; i < input.length() && input[i] != ' '; ++i)
    {
        date.push_back(input[i]);
    }

    if (validateDate(date) && input[5] == '-' && input[8] == '-')
    {
        i++;
        if (i < input.length())
        {
            for (; i < input.length(); ++i)
            {
                event.push_back(input[i]);
            }

            bookings(event.c_str(), date.c_str());
        }
        else
        {
            bookings(nullptr, date.c_str());
        }
    }
    else
    {
        if (input.length() == 11 && input[1] == '2' && input[2] == '0' && input[5] == '-')
        {
            std::cout << "Incorrect date!";
        }
        else
        {
            bookings(input.c_str() + 1, nullptr);
        }
    }
};
void TicketCenter::commandCheck() const
{
    std::string code;
    std::cin >> code;

    check(code.c_str());
}
void TicketCenter::commandReport() const
{
    std::string input;

    std::getline(std::cin, input);

    std::string from;
    std::string to;
    std::string hall;

    int i = 1;
    for (; input[i] != ' ' && i < input.length(); ++i)
    {
        from.push_back(input[i]);
    }
    ++i;
    for (; input[i] != ' ' && i < input.length(); ++i)
    {
        to.push_back(input[i]);
    }
    ++i;
    for (; i < input.length(); ++i)
    {
        hall.push_back(input[i]);
    }

    if (!validateDate(from) || !validateDate(to))
    {
        std::cout << std::endl
                  << "Invalid output, please make sure your dates were input correctly(YYYY-MM-DD)\n";
    }
    else
    {
        if (!hall.size())
        {
            report(from.c_str(), to.c_str(), nullptr);
        }
        else
        {
            report(from.c_str(), to.c_str(), hall.c_str());
        }
    }
}
void TicketCenter::commandLowAttendance()
{
    std::string from;
    std::string to;

    std::cin >> from >> to;

    if (!validateDate(from) || !validateDate(to))
    {
        std::cout << std::endl
                  << "Invalid output, please make sure your dates were input correctly(YYYY-MM-DD)\n";
    }
    else
    {

        lowAttendanceFromTo(from.c_str(), to.c_str());
    }
}

void TicketCenter::printHalls() const
{
    std::cout << "\nHalls:\n";

    for (int i = 0; i < availableHalls.size(); ++i)
    {
        availableHalls[i].print();
    }
}

//Functions from the task guidelines
void TicketCenter::help() const
{
    std::cout << "\n---------List Of Commands------\n";

    std::cout << "\nCommand one:\n";
    std::cout << "Syntax: open <filename/path to file>\n";
    std::cout << "Does: Opens the designated file and loads its content. If no such file exists, the command will create a new one.\n";

    std::cout << "\nCommand two:\n";
    std::cout << "Syntax: close\n";
    std::cout << "Does: Closes the currently opened file, without saving any changes made.\n";

    std::cout << "\nCommand three:\n";
    std::cout << "Syntax: save\n";
    std::cout << "Does: Save any changes made in the opened file.\n";

    std::cout << "\nCommand four:\n";
    std::cout << "Syntax: saveas <filename/path to file>\n";
    std::cout << "Does: Creates a new file and saves the data in the designated new file.\n";

    std::cout << "\nCommand five:\n";
    std::cout << "Syntax: help\n";
    std::cout << "Does: Prints a list of all commands.\n";

    std::cout << "\nCommand six:\n";
    std::cout << "Syntax: exit\n";
    std::cout << "Does: Exits the programm.\n";

    std::cout << "\nCommand seven:\n";
    std::cout << "Syntax: addevent <date> <hall> <name>\n";
    std::cout << "Does: Adds an event with <name> in <hall> on <date>.\n";

    std::cout << "\nCommand eight:\n";
    std::cout << "Syntax: freeseats <date> <name>\n";
    std::cout << "Does: Prints all free seats for event <name> on <date>\n";

    std::cout << "\nCommand nine:\n";
    std::cout << "Syntax: book <row> <seat> <date> <name> <note>\n";
    std::cout << "Does: Books a tickets for event <name> on <date> in <hall> for <row> and <seat>, leaving a <note>.\nWhen inputting the note, it is necessary for it to start with '#!'\n";

    std::cout << "\nCommand nine:\n";
    std::cout << "Syntax: unbook <row> <seat> <date> <name>\n";
    std::cout << "Does: Rmoves the booking for the ticket for event <name> on <date> in <hall> for <row> and <seat>\n";

    std::cout << "\nCommand ten:\n";
    std::cout << "Syntax: buy <row> <seat> <date> <name>\n";
    std::cout << "Does: Buys a ticket for event <name> on <date> in <hall> for <row> and <seat>\n";

    std::cout << "\nCommand eleven:\n";
    std::cout << "Syntax: bookings [<date>][<name>]\n";
    std::cout << "Does: Prints all !booked! tickets for[<name>] on [<date>]. If <name> is not input, prints all tickets for events on <date>.\nIf <date> is not input, prints all tickets for [<name>].\n";

    std::cout << "\nCommand twelve:\n";
    std::cout << "Syntax: check <code>\n";
    std::cout << "Does: Checks if a ticket code is genuine. Returns information about the seat.\n";

    std::cout << "\nCommand thirteen:\n";
    std::cout << "Syntax: report <from> <to> [<hall>]\n";
    std::cout << "Does: Prints all bought tickets in [<hall>] between <from> and <to>.\nIf [<hall>] is not input, prints all bought tickets between <from> and <to>.";

    std::cout << "\nCommand fourteen:\n";
    std::cout << "Syntax: lowattendace <from> <to>\n";
    std::cout << "Does: Prints all events with under 10% attendance rate between <from> and <to.> Allows the user to cancel those events.\n";

    std::cout << "\nCommand fifteen:\n";
    std::cout << "Syntax: mostseen\n";
    std::cout << "Does: Prints the 5 events with highest attendance rate.\n";

    std::cout << "\nCommand sixteen:\n";
    std::cout << "Syntax: printhalls\n";
    std::cout << "Does: Prints all available halls.\n";

    std::cout << "\n---------End Of List------\n";
}

void TicketCenter::addEvent(const char *newEventName, const char *newEventDate, const char *newEventHall)
{
    for (int i = 0; i < availableEvents.size(); ++i)
    {
        char *temp = availableEvents[i].getDate();

        if (strcmp(temp, newEventDate) == 0)
        {
            delete[] temp;
            temp = availableEvents[i].getHallNumber();

            if (strcmp(temp, newEventHall) == 0)
            {
                std::cout << std::endl
                          << "There is already another event in this hall on this date! Event will not be added!"
                          << std::endl;
                delete[] temp;
                return;
            }
        }

        delete[] temp;
    }

    for (int i = 0; i < availableHalls.size(); ++i)
    {
        if (availableHalls[i] == newEventHall)
        {
            Event toBeAdded(newEventName, newEventDate, availableHalls[i]);
            availableEvents.push_back(toBeAdded);

            std::cout << std::endl
                      << "Event successfully added!\n"
                      << std::endl;

            return;
        }
    }

    std::cout << "\nEvent cannot be added, no such hall exists!\n";
}

void TicketCenter::freeSeats(const char *_eventName, const char *_eventDate) const
{
    size_t eventIndex = findEventByNameDate(_eventName, _eventDate);

    if (eventIndex > availableEvents.size())
    {
        std::cout << std::endl
                  << _eventDate << " is not an available date for "
                  << _eventName
                  << "."
                  << std::endl;
        return;
    }
    else
    {
        availableEvents[eventIndex].printFreeSeats();
    }
}

void TicketCenter::book(const char *_eventName, const char *_eventDate, const size_t &_row, const size_t &_seat, const char *_note = nullptr)
{
    size_t eventIndex = findEventByNameDate(_eventName, _eventDate);

    if (eventIndex > availableEvents.size())
    {
        std::cout << std::endl
                  << "There are no such events on this date!"
                  << std::endl;
        return;
    }
    else if (availableEvents[eventIndex].checkIfBooked(_row, _seat) || availableEvents[eventIndex].checkIfSold(_row, _seat))
    {
        std::cout << std::endl
                  << "Seat cannot be booked!"
                  << std::endl;
        return;
    }
    else
    {
        Ticket newTicket(_eventName, _eventDate, _row, _seat, _note);
        bookedTickets.push_back(newTicket);
        availableEvents[eventIndex].bookSeat(_row, _seat);
        std::cout << std::endl
                  << "Ticket successfully booked!"
                  << std::endl;

        return;
    }
}

void TicketCenter::unbook(const char *_eventName, const char *_eventDate, const size_t &_row, const size_t &_seat)
{
    size_t eventIndex = findEventByNameDate(_eventName, _eventDate);

    if (eventIndex > availableEvents.size())
    {
        std::cout << std::endl
                  << "There are no such events on this date!"
                  << std::endl;
        return;
    }

    if (availableEvents[eventIndex].unbookSeat(_row, _seat))
    {
        removeBookedTicket(_eventName, _eventDate, _row, _seat);
    }
}

void TicketCenter::buy(const char *_eventName, const char *_eventDate, const size_t &_row, const size_t &_seat)
{
    size_t eventIndex = findEventByNameDate(_eventName, _eventDate);

    if (eventIndex > availableEvents.size())
    {
        std::cout << std::endl
                  << "There are no such events on this date!"
                  << std::endl;
        return;
    }

    if (availableEvents[eventIndex].checkIfBooked(_row, _seat) || availableEvents[eventIndex].checkIfSold(_row, _seat))
    {
        std::cout << std::endl
                  << "Seat cannot be bought!"
                  << std::endl;
        return;
    }
    else
    {
        Ticket newTicket(_eventName, _eventDate, _row, _seat);
        soldTickets.push_back(newTicket);
        availableEvents[eventIndex].sellSeat(_row, _seat);
        std::cout << std::endl
                  << "Ticket bought successfully!"
                  << std::endl;

        return;
    }
}

void TicketCenter::check(const char *codeToCheck) const
{
    for (int i = 0; i < bookedTickets.size(); ++i)
    {
        if (bookedTickets[i] == codeToCheck)
        {
            std::cout << std::endl
                      << "Genuine ticket, booked for row: "
                      << bookedTickets[i].getRow()
                      << " seat: "
                      << bookedTickets[i].getSeatNumber()
                      << '.'
                      << std::endl;

            return;
        }
    }

    for (int i = 0; i < soldTickets.size(); ++i)
    {
        if (soldTickets[i] == codeToCheck)
        {
            std::cout << std::endl
                      << "Genuine ticket, sold for row: "
                      << soldTickets[i].getRow()
                      << " seat: "
                      << soldTickets[i].getSeatNumber()
                      << '.'
                      << std::endl;

            return;
        }
    }

    std::cout << std::endl
              << "The code is fake, no such ticket exists!"
              << std::endl;
}

void TicketCenter::bookings(const char *_eventName = nullptr, const char *_eventDate = nullptr) const
{
    std::cout << std::endl
              << "All bookings";

    if (_eventName != nullptr)
    {
        std::cout << " for "
                  << _eventName;
    }

    if (_eventDate != nullptr)
    {
        std::cout << " on "
                  << _eventDate;
    }

    std::cout << ": "
              << std::endl;

    if (_eventName == nullptr && _eventDate == nullptr)
    {
        for (int i = 0; i < bookedTickets.size(); ++i)
        {
            bookedTickets[i].print();
            std::cout << std::endl;
        }

        return;
    }
    else
    {
        for (int i = 0; i < bookedTickets.size(); ++i)
        {
            if (bookedTickets[i].checkIfFor(_eventName, _eventDate))
            {
                bookedTickets[i].print();
                std::cout << std::endl;
            }
        }
    }

    return;
}

void TicketCenter::report(const char *from, const char *to, const char *hall = nullptr) const
{
    std::cout << std::endl
              << "All sold tickets between "
              << from
              << " and "
              << to;

    if (hall == nullptr)
    {
        reportWithoutHall(from, to);
    }
    else
    {
        reportWithHall(from, to, hall);
    }
}

void TicketCenter::mostSeen() const
{
    double percentagePerEvent[availableEvents.size()];

    for (int i = 0; i < availableEvents.size(); ++i)
    {
        percentagePerEvent[i] = availableEvents[i].getAttendacePercentage();
    }

    size_t mostSeen[5] = {0, 0, 0, 0, 0};

    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < availableEvents.size(); ++j)
        {
            if (availableEvents[mostSeen[i]].getAttendacePercentage() < percentagePerEvent[j])
            {
                mostSeen[i] = j;
            }
        }

        percentagePerEvent[mostSeen[i]] = 0;
    }

    std::cout << std::endl
              << "The 5 most seen events:\n"
              << std::endl;

    for (int i = 0; i < 5; ++i)
    {
        availableEvents[mostSeen[i]].print();
        std::cout << "Attendance percentage: "
                  << availableEvents[mostSeen[i]].getAttendacePercentage()
                  << std::endl;
    }
}

void TicketCenter::lowAttendanceFromTo(const char *from, const char *to)
{

    std::vector<Event> eventsUnderTenPercent;

    for (int i = 0; i < availableEvents.size(); ++i)
    {
        char *date = availableEvents[i].getDate();
        char *hall = availableEvents[i].getHallNumber();

        if (strcmp(from, date) <= 0 && strcmp(date, to) <= 0 && availableEvents[i].getAttendacePercentage() < 0.1)
        {
            eventsUnderTenPercent.push_back(availableEvents[i]);
        }

        delete[] date;
        delete[] hall;
    }

    lowAttendancePrint(eventsUnderTenPercent);
    if (eventsUnderTenPercent.size())
    {
        removeLowAttendance();
    }

    return;
}

//File manioulation functions:
bool TicketCenter::loadData(std::fstream &file)
{

    if (!loadEvents(file))
    {
        return 0;
    }

    if (!loadBookedTickets(file))
    {
        return 0;
    }

    if (!loadSoldTickets(file))
    {
        return 0;
    }

    return 1;
}

bool TicketCenter::seedData(std::fstream &file)
{
    if (!seedEvents(file))
    {
        return 0;
    }
    if (!seedBookedTickets(file))
    {
        return 0;
    }
    if (!seedSoldTickets(file))
    {
        return 0;
    }

    return 1;
}

void TicketCenter::open(const char *fileName)
{
    std::fstream input;
    input.open("Data/PresetHallData.bin", std::ios::in | std::ios::binary);
    if (input.is_open())
    {
        if (!loadHalls(input))
        {
            std::cout << "\n No preset hall data found!";
        }
    }

    input.close();

    input.open(fileName, std::ios::in | std::ios::binary);

    if (input.is_open())
    {
        if (loadData(input))
        {
            std::cout << std::endl
                      << "The data was successfully loaded!\n";
        }
        else
        {
            std::cout << "The data could not be loaded due to an error!";
        }
    }
    else
    {
        std::cout << std::endl
                  << "New file created!"
                  << std::endl;
    }

    input.close();
};

void TicketCenter::save(const char *fileName)
{
    std::fstream output;
    output.open(fileName, std::ios::out | std::ios::binary);

    if (output.is_open())
    {
        if (seedData(output))
        {
            std::cout << std::endl
                      << "The file was updated successfully!\n";
        }
        else
        {
            std::cout << "The file could not be updated due to an error!";
        }
    }

    output.close();
};

void TicketCenter::saveAs(const char *fileName)
{
    std::fstream output;
    output.open(fileName, std::ios::out | std::ios::binary);

    if (output.is_open())
    {
        if (seedData(output))
        {
            std::cout << std::endl
                      << "The data was successfully saved in the new file!\n";
        }
        else
        {
            std::cout << "The new file could not be created due to an error!";
        }
    }

    output.close();
};

void TicketCenter::close()
{
    std::cout << std::endl
              << "Closing file!\n";

    for (int i = 0; i < availableHalls.size(); ++i)
    {
        availableHalls.pop_back();
    }

    for (int i = 0; i < availableEvents.size(); ++i)
    {
        availableEvents.pop_back();
    }

    for (int i = 0; i < bookedTickets.size(); ++i)
    {
        bookedTickets.pop_back();
    }

    for (int i = 0; i < soldTickets.size(); ++i)
    {
        soldTickets.pop_back();
    }
}
//Main function the user will interact with

void TicketCenter::startCenter()
{
    //The longst function name is 16 characters - lowestattendance
    std::string openedFileName; //If a file has been opned via the open function, we will keep it's name here. No other actions will be allowed while there is no opened file

    std::cout << "Welcome to the FMI ticket center! Please state your commands:\n";

    std::string command;

    do
    {
        std::cin >> command;

        if (strcmp(command.c_str(), "open") == 0)
        {
            if (!openedFileName.empty())
            {
                close();
            }

            getline(std::cin, openedFileName);
            open(openedFileName.c_str());
            continue;
        }
        else if (strcmp(command.c_str(), "help") == 0)
        {
            help();
            continue;
        }
        else if (strcmp(command.c_str(), "exit") == 0)
        {
            std::cout << std::endl
                      << "Exiting the program!\n";
            return;
        }
        else if (openedFileName.empty())
        {
            std::cout << "\nYou have not opened a file yet, please use 'open' in order to be able to use additional commands!\n";
            continue;
        }
        else if (strcmp(command.c_str(), "close") == 0 && !openedFileName.empty())
        {
            close();
            while (!openedFileName.empty())
            {
                openedFileName.pop_back();
            }
            continue;
        }
        else if (strcmp(command.c_str(), "save") == 0 && !openedFileName.empty())
        {
            save(openedFileName.c_str());
            continue;
        }
        else if (strcmp(command.c_str(), "saveas") == 0 && !openedFileName.empty())
        {
            getline(std::cin, openedFileName);
            saveAs(openedFileName.c_str());
            continue;
        }
        else if (strcmp(command.c_str(), "addevent") == 0 && !openedFileName.empty())
        {

            commandAddEvent();
            continue;
        }
        else if (strcmp(command.c_str(), "freeseats") == 0 && !openedFileName.empty())
        {
            commandFreeSeats();
            continue;
        }
        else if (strcmp(command.c_str(), "book") == 0 && !openedFileName.empty())
        {
            commandBookTicket();
            continue;
        }
        else if (strcmp(command.c_str(), "unbook") == 0 && !openedFileName.empty())
        {
            commandUnbookTicket();
            continue;
        }
        else if (strcmp(command.c_str(), "buy") == 0 && !openedFileName.empty())
        {
            commandBuyTicket();
            continue;
        }
        else if (strcmp(command.c_str(), "bookings") == 0 && !openedFileName.empty())
        {
            commandBookings();
            continue;
        }
        else if (strcmp(command.c_str(), "check") == 0 && !openedFileName.empty())
        {
            commandCheck();
            continue;
        }
        else if (strcmp(command.c_str(), "report") == 0 && !openedFileName.empty())
        {
            commandReport();
            continue;
        }
        else if (strcmp(command.c_str(), "mostseen") == 0 && !openedFileName.empty())
        {
            mostSeen();
            continue;
        }
        else if (strcmp(command.c_str(), "lowattendance") == 0 && !openedFileName.empty())
        {
            commandLowAttendance();
            continue;
        }
        else if (strcmp(command.c_str(), "printhalls") == 0 && !openedFileName.empty())
        {
            printHalls();
            continue;
        }
        else
        {
            std::cout << "\nInvalid command, if you are unsure as to what comman you desire, please use 'help' to receive a detailed list of all commands!\n";
            continue;
        }

    } while (true);
}
