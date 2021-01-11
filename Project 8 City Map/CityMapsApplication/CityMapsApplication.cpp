#ifndef __Application_CPP
#define __Application_CPP

#include "CityMapsApplication.h"

void CityMapsApplication::deserialize(const std::string &fileName)
{
    currLoadedCity.deserialize(fileName);
}
void CityMapsApplication::location()
{
    currLoadedCity.location();
}
void CityMapsApplication::neighbours()
{
    currLoadedCity.neighbours();
}
void CityMapsApplication::move(const std::string &intersection)
{
    currLoadedCity.move(intersection);
}
void CityMapsApplication::close(const std::string &intersection)
{
    currLoadedCity.close(intersection);
}
void CityMapsApplication::open(const std::string &intersection)
{
    currLoadedCity.open(intersection);
}
void CityMapsApplication::closed()
{
    currLoadedCity.closed();
}
void CityMapsApplication::tour()
{
    currLoadedCity.tour();
}
void CityMapsApplication::start()
{
    std::cout << std::endl
              << "-------Welcome to the City Maps Application-------"
              << std::endl
              << std::endl
              << "To start the interactive mode please type \"i <InputFileName> <CurrentIntersection>\""
              << std::endl;

    std::string userInput;

    do
    {
        std::cin >> userInput;

        if (!initiated && userInput[0] == 'i')
        {
            std::string startingIntersection;
            std::cin >> startingIntersection;

            std::string fileToOpen;
            std::cin >> fileToOpen;

            currLoadedCity.deserialize(fileToOpen);

            if (currLoadedCity.setCurrent(startingIntersection))
            {
                initiated = true;
            }
        }
        else if (initiated && userInput.compare("location") == 0)
        {
            currLoadedCity.location();
        }
        else if (initiated && userInput.compare("change") == 0)
        {
            std::string toChange;
            std::cin >> toChange;
            currLoadedCity.change(toChange);
        }
        else if (initiated && userInput.compare("neighbours") == 0)
        {
            currLoadedCity.neighbours();
        }
        else if (initiated && userInput.compare("move") == 0)
        {
            std::string toChange;
            std::cin >> toChange;
            currLoadedCity.move(toChange);
        }
        else if (initiated && userInput.compare("close") == 0)
        {
            std::string toChange;
            std::cin >> toChange;
            currLoadedCity.close(toChange);
        }
        else if (initiated && userInput.compare("open") == 0)
        {
            std::string toChange;
            std::cin >> toChange;
            currLoadedCity.open(toChange);
        }
        else if (initiated && userInput.compare("closed") == 0)
        {
            currLoadedCity.closed();
        }
        else if (initiated && userInput.compare("tour") == 0)
        {
            currLoadedCity.tour();
        }
        else
        {
            std::cout << std::endl
                      << "Invalid command! Make sure the file was properly initiated!"
                      << std::endl;
        }
    } while (true);
}

#endif
