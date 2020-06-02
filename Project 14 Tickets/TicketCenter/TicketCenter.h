#ifndef _TicketCenter_hh
#define _TicketCenter_hh

#include "..\Ticket\Ticket.cpp"
#include <functional>

class TicketCenter
{
private:
    std::vector<Hall> availableHalls;

    std::vector<Event> availableEvents;

    std::vector<Ticket> bookedTickets;

    std::vector<Ticket> soldTickets;

    void removeBookedTicket(const char *, const char *, const size_t &, const size_t &);
    void sortEventsAlphabetically();

    //Find the required data
    size_t findEventByNameDate(const char *, const char *) const;

    //Functions from input
    void findNote(std::string &, std::string &);

    //Additional help finctions
    void lowAttendancePrint(const std::vector<Event> &) const;
    void removeLowAttendance();
    void reportWithoutHall(const char *, const char *) const;
    void reportWithHall(const char *, const char *, const char *) const;
    bool validateDate(const std::string &) const;

    //DataLoading

    bool loadHalls(std::fstream &);
    bool loadEvents(std::fstream &);
    bool loadBookedTickets(std::fstream &);
    bool loadSoldTickets(std::fstream &);

    //DataSeeding
    bool seedEvents(std::fstream &);
    bool seedBookedTickets(std::fstream &);
    bool seedSoldTickets(std::fstream &);

public:
    //Constructors and Destructor
    TicketCenter();
    TicketCenter(const TicketCenter &);
    ~TicketCenter();

    //Operators
    TicketCenter &operator=(const TicketCenter &);

    //Functions according to the desired command that require additional input
    void commandAddEvent();
    void commandFreeSeats() const;
    void commandBookTicket();
    void commandUnbookTicket();
    void commandBuyTicket();
    void commandBookings() const;
    void commandCheck() const;
    void commandReport() const;
    void commandLowAttendance();

    void printHalls() const;

    //Functions from the task guidelines

    void help() const;
    void addEvent(const char *, const char[], const char *);

    void freeSeats(const char *, const char *) const;
    void book(const char *, const char *, const size_t &, const size_t &, const char *);
    void unbook(const char *, const char *, const size_t &, const size_t &);
    void buy(const char *, const char *, const size_t &, const size_t &);

    void bookings(const char *, const char *) const;

    void check(const char *) const;
    void report(const char *, const char *, const char *) const;
    void mostSeen() const;
    void lowAttendanceFromTo(const char *, const char *);

    //File manipulation functions
    bool loadData(std::fstream &);
    bool seedData(std::fstream &);
    void open(const char *);
    void save(const char *);
    void saveAs(const char *);
    void close();

    //Main function the user will interact with
    void startCenter();
};

#endif