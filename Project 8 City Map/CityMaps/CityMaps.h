#ifndef __City_Map_H
#define __City_Map_H

#include "../Graph/Graph.h"

template <class VertexType, class WeightType>
class CityMaps
{
public:
    CityMaps() = default;
    bool setCurrent(const VertexType &);

    void location() const;
    void change(const VertexType &);
    void neighbours();
    void move(const VertexType &);
    void close(const VertexType &);
    void open(const VertexType &);
    void closed() const;
    void tour();

    void checkPath(const VertexType &, const VertexType &);
    void findShortest(const VertexType &, const VertexType &);
    void canReachAll(const VertexType &);
    void isCyclic(const VertexType &);
    void findDeadEnd();
    void deserialize(const std::string &);

private:
    CityGraph<VertexType, WeightType> cityMap;
    std::set<VertexType> closedIntersections;
    VertexType currentIntersection;

    bool checkIfAvailable(const VertexType &) const;
    bool exists(const VertexType &) const;
    bool isClosed(const VertexType &) const;
};

template <class VertexType, class WeightType>
bool CityMaps<VertexType, WeightType>::setCurrent(const VertexType &newIntersection)
{
    if (!cityMap.hasVertex(newIntersection))
    {
        std::cout << std::endl
                  << "Invalid intersection!"
                  << std::endl;
        return false;
    }

    currentIntersection = newIntersection;
    return true;
}

template <class VertexType, class WeightType>
bool CityMaps<VertexType, WeightType>::exists(const VertexType &newIntersection) const
{
    if (!cityMap.hasVertex(newIntersection))
    {
        std::cout << std::endl
                  << "There is no intersection called {"
                  << newIntersection
                  << "} your position is still {"
                  << currentIntersection
                  << '}'
                  << std::endl;

        return false;
    }

    return true;
}

template <class VertexType, class WeightType>
bool CityMaps<VertexType, WeightType>::isClosed(const VertexType &newIntersection) const
{
    return closedIntersections.count(newIntersection) == 1;
}

template <class VertexType, class WeightType>
bool CityMaps<VertexType, WeightType>::checkIfAvailable(const VertexType &newIntersection) const
{
    if (!exists(newIntersection))
    {
        std::cout << std::endl
                  << "No such intersection { " << newIntersection << " } exists!";
        return false;
    }
    else if (isClosed(newIntersection))
    {
        std::cout << std::endl
                  << "The desired intersection {"
                  << newIntersection
                  << "} is closed, your position is still {"
                  << currentIntersection
                  << '}'
                  << std::endl;

        return false;
    }

    return true;
}

template <class VertexType, class WeightType>
void CityMaps<VertexType, WeightType>::location() const
{
    std::cout << std::endl
              << "You are currently at intersection {"
              << currentIntersection
              << '}' << std::endl;
}

template <class VertexType, class WeightType>
void CityMaps<VertexType, WeightType>::change(const VertexType &newIntersection)
{
    if (!checkIfAvailable(newIntersection))
    {
        return;
    }

    currentIntersection = newIntersection;
}

template <class VertexType, class WeightType>
void CityMaps<VertexType, WeightType>::neighbours()
{
    std::cout << std::endl
              << "All the neighbours of intersection {"
              << currentIntersection
              << "} are { ";

    for (auto i : cityMap.findNeighbours(currentIntersection))
    {
        std::cout << i << ' ';
    }

    std::cout << " }"
              << std::endl;
    ;
}

template <class VertexType, class WeightType>
void CityMaps<VertexType, WeightType>::move(const VertexType &newIntersection)
{
    if (!checkIfAvailable(newIntersection))
    {
        return;
    }
    std::vector<std::vector<VertexType>> pathToNew;

    try
    {
        pathToNew = cityMap.findAllPaths(currentIntersection, newIntersection, closedIntersections);
    }
    catch (std::invalid_argument e)
    {
        std::cout << std::endl
                  << "!!! " << e.what()
                  << " No such intersectoion { "
                  << newIntersection
                  << " } was found!"
                  << std::endl;

        return;
    }
    catch (...)
    {
        std::cout << "Unkown error"
                  << std::endl;
        return;
    }

    if (pathToNew.empty())
    {
        std::cout << std::endl
                  << "There is no available path between these 2 intersections!"
                  << std::endl;

        return;
    }

    std::cout << "The position was changed from{ "
              << currentIntersection << " } to { "
              << newIntersection
              << "} The path between the two is { ";

    ///We return the shortest path
    for (auto i : pathToNew[0])
    {
        std::cout << i << ' ';
    }

    std::cout << " }"
              << std::endl;

    currentIntersection = newIntersection;
}

template <class VertexType, class WeightType>
void CityMaps<VertexType, WeightType>::close(const VertexType &toClose)
{
    if (!exists(toClose))
    {
        return;
    }
    else if (isClosed(toClose))
    {
        std::cout << std::endl
                  << "The intersection{ "
                  << toClose
                  << "} is already closed"
                  << std::endl;
    }

    closedIntersections.insert(toClose);
}

template <class VertexType, class WeightType>
void CityMaps<VertexType, WeightType>::open(const VertexType &toOpen)
{
    if (!exists(toOpen))
    {
        return;
    }
    else if (isClosed(toOpen))
    {
        std::cout << std::endl
                  << "The intersection{ "
                  << toOpen
                  << "} is now open!"
                  << std::endl;

        closedIntersections.erase(toOpen);

        return;
    }
    else
    {
        std::cout << std::endl
                  << "The intersection { "
                  << toOpen
                  << " } is not closed. It will remain open!"
                  << std::endl;
    }
}

template <class VertexType, class WeightType>
void CityMaps<VertexType, WeightType>::closed() const
{
    if (closedIntersections.empty())
    {
        std::cout << std::endl
                  << "All intersections are open!"
                  << std::endl;
    }

    std::cout << "All closed intersections are{ ";

    for (auto i : closedIntersections)
    {
        std::cout << i << ' ';
    }

    std::cout << " }"
              << std::endl;
}

template <class VertexType, class WeightType>
void CityMaps<VertexType, WeightType>::tour()
{
    std::vector<VertexType> tourPath = cityMap.chinesePostman();

    if (tourPath.empty())
    {
        std::cout << std::endl
                  << "You cannot fully traverse the city!"
                  << std::endl;

        return;
    }

    std::cout << std::endl
              << "The tour path is { ";

    for (auto i : tourPath)
    {
        std::cout << i << ' ';
    }

    std::cout << '}'
              << std::endl;
}

template <class VertexType, class WeightType>
void CityMaps<VertexType, WeightType>::checkPath(const VertexType &start, const VertexType &end)
{
    bool hasPath;

    try
    {
        hasPath = cityMap.hasPath(start, end, {});
    }
    catch (std::invalid_argument e)
    {
        std::cout << std::endl
                  << "!!!" << e.what()
                  << std::endl;
        return;
    }
    catch (...)
    {
        std::cout << std::endl
                  << "Unknow error!"
                  << std::endl;
        return;
    }

    if (hasPath)
    {
        std::cout << std::endl
                  << "A path between { " << start << " and " << end << " } exists"
                  << std::endl;
    }
    else
    {
        std::cout << std::endl
                  << "A path between { " << start << " and " << end << " } does not exist"
                  << std::endl;
    }
}

template <class VertexType, class WeightType>
void CityMaps<VertexType, WeightType>::isCyclic(const VertexType &start)
{
    bool isCyclic;

    try
    {
        isCyclic = cityMap.isCyclic(start);
    }
    catch (std::invalid_argument e)
    {
        std::cout << std::endl
                  << "!!! " << e.what()
                  << "No such intersectoion { "
                  << start
                  << " } was found!"
                  << std::endl;
    }
    catch (...)
    {
        std::cout << std::endl
                  << "Unknow error!"
                  << std::endl;
    }

    if (isCyclic)
    {
        std::cout << std::endl
                  << "You can cycle starting from { " << start << " }"
                  << std::endl;
    }
    else
    {
        std::cout << std::endl
                  << "You cannot cycle starting from { " << start << " }"
                  << std::endl;
    }
}

template <class VertexType, class WeightType>
void CityMaps<VertexType, WeightType>::findShortest(const VertexType &start, const VertexType &end)
{
    if (closedIntersections.count(start) == 1 || closedIntersections.count(end) == 1)
    {
        std::cout << std::endl
                  << "There is no path between a closed intersection and another itersection"
                  << std::endl;
    }

    std::vector<std::vector<VertexType>> allPaths;

    try
    {
        allPaths = cityMap.findAllPaths(start, end, closedIntersections);
    }
    catch (std::invalid_argument e)
    {
        std::cout << std::endl
                  << "!!!" << e.what()
                  << std::endl;

        return;
    }
    catch (...)
    {
        std::cout << std::endl
                  << "Unknow error!"
                  << std::endl;

        return;
    }

    if (allPaths.empty())
    {
        std::cout << std::endl
                  << "There is no path between { " << start << " and " << end << " }"
                  << std::endl;
    }
    else
    {
        std::cout << std::endl
                  << "The paths are:"
                  << std::endl;

        for (std::vector<VertexType> currPath : allPaths)
        {
            std::cout << "{ ";

            for (VertexType vert : currPath)
            {
                std::cout << vert << " ";
            }

            std::cout << '}'
                      << std::endl;
        }
    }
}

template <class VertexType, class WeightType>
void CityMaps<VertexType, WeightType>::canReachAll(const VertexType &start)
{
    bool canReach;

    try
    {
        bool canReach = cityMap.canReachEverywhere(start);
    }
    catch (std::invalid_argument e)
    {
        std::cout << std::endl
                  << "!!!"
                  << e.what()
                  << std::endl;
    }
    catch (...)
    {
        std::cout
            << std::endl
            << "Unknown error!"
            << std::endl;
    }

    if (!canReach)
    {
        std::cout << std::endl
                  << "You cannot reach all intersections from {"
                  << start
                  << " }"
                  << std::endl;
    }

    std::cout << std::endl
              << "You can reach all intersections from {"
              << start
              << " }"
              << std::endl;
}

template <class VertexType, class WeightType>
void CityMaps<VertexType, WeightType>::findDeadEnd()
{
    std::set<std::pair<VertexType, VertexType>> deadEndStreets = cityMap.findDeadEnd();

    if (deadEndStreets.empty())
    {
        std::cout << std::endl
                  << "There are no dead-end streets!"
                  << std::endl;
        return;
    }

    std::cout << std::endl
              << "All dead-end streets are:"
              << std::endl;

    for (auto street : deadEndStreets)
    {
        std::cout << std::endl
                  << "\t{ "
                  << street.first
                  << " -> "
                  << street.second
                  << " }";
    }
}

template <class VertexType, class WeightType>
void CityMaps<VertexType, WeightType>::deserialize(const std::string &fileName)
{
    std::ifstream fileToLoad;
    fileToLoad.open(fileName, std::ios::in);

    if (fileToLoad.is_open())
    {
        cityMap.deserialize(fileToLoad);
    }
    else
    {
        std::cout << std::endl
                  << "Unable to open file or file does not exist!"
                  << std::endl;
    }
}

#endif
