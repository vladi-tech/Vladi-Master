#include "Hall.h"
#include <fstream>

Hall::Hall() : numberRows{0}, seatsPerRow{0}
{
}

Hall::Hall(const Hall &other) : hallNumber{other.hallNumber}, numberRows{other.numberRows}, seatsPerRow{other.seatsPerRow}
{
    hallNumber.shrink_to_fit();
}

Hall::Hall(const std::string &_hallNumber, const size_t &_numberRows, const size_t &_seatsPerRow) : hallNumber{_hallNumber}, numberRows{_numberRows}, seatsPerRow{_seatsPerRow}
{
    hallNumber.shrink_to_fit();
}

Hall::~Hall()
{
}

Hall &Hall::operator=(const Hall &other)
{
    if (this != &other)
    {
        this->hallNumber = other.hallNumber;

        this->numberRows = other.numberRows;
        this->seatsPerRow = other.seatsPerRow;
    }

    return *this;
}

bool Hall::operator==(const Hall &other) const
{
    return (!this->hallNumber.compare(other.hallNumber));
}
bool Hall::operator==(const char *other) const
{
    return (!this->hallNumber.compare(other));
}

//Additional functions:

char *Hall::getNumber() const
{
    char *result = new char[this->hallNumber.length() + 1];
    strcpy(result, hallNumber.c_str());
    return result;
}
size_t Hall::getNumberRows() const
{
    return numberRows;
}
size_t Hall::getSeatsPerRow() const
{
    return seatsPerRow;
}

void Hall::print() const
{
    std::cout << std::endl
              << "Hall number: "
              << hallNumber
              << std::endl
              << "Rows in the hall: "
              << numberRows
              << std::endl
              << "Seats per row: "
              << seatsPerRow
              << std::endl;
}

bool Hall::loadData(std::fstream &file)
{
    size_t nameSize;
    if (!file.read((char *)&nameSize, sizeof(size_t)))
    {
        file.close();
        return 0;
    }

    for (int i = 0; i < nameSize; ++i)
    {
        char symbol;
        if (!file.read((char *)&symbol, sizeof(char)))
        {
            file.close();
            return 0;
        }
        hallNumber.push_back(symbol);
    }

    if (!file.read((char *)&numberRows, sizeof(size_t)))
    {
        file.close();
        return 0;
    }

    if (!file.read((char *)&seatsPerRow, sizeof(size_t)))
    {
        file.close();
        return 0;
    }

    return 1;
}
bool Hall::seedData(std::fstream &file)
{

    size_t nameSize = hallNumber.length();
    if (!file.write((const char *)&nameSize, sizeof(size_t)))
    {
        file.close();
        return 0;
    }

    for (int i = 0; i < nameSize; i++)
    {
        if (!file.write((const char *)&hallNumber[i], sizeof(char)))
        {
            file.close();
            return 0;
        }
    }

    if (!file.write((const char *)&numberRows, sizeof(size_t)))
    {
        file.close();
        return 0;
    }

    if (!file.write((const char *)&seatsPerRow, sizeof(size_t)))
    {
        file.close();
        return 0;
    }

    return 1;
}