#ifndef __Graph_H
#define __Graph_H

#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <stack>
#include <string>
#include <fstream>

template <class VertexType, class WeightType>
class CityGraph
{
    ///As in the tasks example, we will use the pair of <Intersection, Distance> to define a one-way street.
    using StreetType = std::pair<VertexType, WeightType>;

    ///To represent the neighbouring intersections we will use a set of Streets, as defined above
    using NeighboursType = std::set<StreetType>;

public:
    CityGraph() = default;

    ///Checks if a vertex is part of the graph
    bool hasVertex(const VertexType &) const;

    ///Checks if the it two vertices(intersections) are adjacent
    bool hasEdge(const VertexType &, const VertexType &);

    ///Returns the distance between two adjacent vertices(intercetions)
    WeightType getEdgeWeight(const VertexType &, const VertexType &);

    ///Checks if there is a path between two vertices(intersections)
    bool hasPath(const VertexType &, const VertexType &, const std::set<VertexType> &);

    ///Finds all paths between two vertices(intersections)
    std::vector<std::vector<VertexType>> findAllPaths(const VertexType &, const VertexType &, const std::set<VertexType> &);

    ///Recursive function for findAllPaths
    void findAllPathsHelper(const VertexType &, const VertexType &, std::set<VertexType> &, std::vector<VertexType> &, std::vector<std::vector<VertexType>> &, const std::set<VertexType> &);

    ///Checks if there is a cycle in the graph
    bool isCyclic(const VertexType &);

    ///Checks if we can do a fully traverse all edges(streets) of the graph(city) without taking the same edge(street) twice
    std::vector<VertexType> chinesePostman();

    ///Checks if we can reach all other vertices(interesections) from the current one
    bool canReachEverywhere(const VertexType &);

    ///Returns all neighbours of the given edge(intersection)
    std::set<VertexType> findNeighbours(const VertexType &);

    ///Finds all dead-end streets
    std::set<std::pair<VertexType, VertexType>> findDeadEnd();

    ///Deserializes the graph from a txt file
    void deserialize(std::ifstream &);

    ///Checks if the start and end of the path are a part of the graph
    bool checkPathValidity(const VertexType &, const VertexType &);

private:
    ///We will keep a seperate set of all intersections in the graph, as it will enable easier-to-undertand code later on in the task
    std::set<VertexType> intersections;

    std::map<VertexType, NeighboursType> neighbours;

    void deserializeHelperAlphabetic(char &, VertexType &, std::ifstream &);
    void deserializeHelperNumeric(char &, WeightType &, std::ifstream &);
};

///Checks if a vertex is part of the graph
template <class VertexType, class WeightType>
bool CityGraph<VertexType, WeightType>::hasVertex(const VertexType &toCheck) const
{
    return intersections.count(toCheck) == 1;
}

///Checks if the two vertices(intersections) are adjacent
template <class VertexType, class WeightType>
bool CityGraph<VertexType, WeightType>::hasEdge(const VertexType &first, const VertexType &second)
{
    ///If one of the vertices is not part of the graph, then we early return false
    if (!checkPathValidity(first, second))
    {
        return false;
    }

    ///neighbours[first] = set { pair { adjacent_intersection, distance } }
    ///We iterate through all neighbour pairs to check if the adjacent intercection value is the same as "second"
    ///If it is, then we have found the desired edge
    for (auto i : neighbours[first])
    {
        if (i.first.compare(second) == 0)
        {
            return true;
        }
    }

    return false;
}

///Returns the distance between two adjacent vertices(intercetions)
template <class VertexType, class WeightType>
WeightType CityGraph<VertexType, WeightType>::getEdgeWeight(const VertexType &first, const VertexType &second)
{
    if (!checkPathValidity(first, second))
    {
        throw std::invalid_argument("Invalid intersecion: ");
    }

    for (auto i : neighbours[first])
    {
        if (i.first.compare(second) == 0)
        {
            return i.second;
        }
    }

    ///If we have not found the edge, then we return -1
    return -1;
}

///Checks if there is a path between two vertices(intersections)
template <class VertexType, class WeightType>
bool CityGraph<VertexType, WeightType>::hasPath(const VertexType &start, const VertexType &end, const std::set<VertexType> &closedIntersections)
{
    if (!checkPathValidity(start, end))
    {
        throw std::invalid_argument("Invalid argument: ");
    }
    else if (closedIntersections.count(start) == 1 || closedIntersections.count(end) == 1)
    {
        return false;
    }

    std::stack<VertexType> toTraverse;
    std::set<VertexType> visitedVertices;

    VertexType current = start;

    toTraverse.push(current);
    visitedVertices.insert(current);

    while (!toTraverse.empty())
    {
        current = toTraverse.top();
        toTraverse.pop();

        for (auto vert : neighbours[current])
        {
            if (visitedVertices.count(vert.first) == 0 && closedIntersections.count(vert.first) == 0)
            {
                toTraverse.push(vert.first);
                visitedVertices.insert(vert.first);
            }
        }

        if (visitedVertices.count(end) == 1)
        {
            return true;
        }
    }

    return false;
}

///Finds all paths between two vertices(intersections)
template <class VertexType, class WeightType>
std::vector<std::vector<VertexType>> CityGraph<VertexType, WeightType>::findAllPaths(const VertexType &start, const VertexType &end, const std::set<VertexType> &closedIntersections)
{
    std::vector<std::vector<VertexType>> allPaths;

    if (!checkPathValidity(start, end))
    {
        throw std::invalid_argument("Invalid argument: ");
    }
    else if (!hasPath(start, end, closedIntersections) || closedIntersections.count(start) || closedIntersections.count(end))
    {
        return allPaths;
    }

    std::set<VertexType> visitedVertices;
    std::vector<VertexType> currPath;

    visitedVertices.insert(start);
    currPath.push_back(start);

    findAllPathsHelper(start, end, visitedVertices, currPath, allPaths, closedIntersections);

    return allPaths;
}

///Recursive function for findAllPaths
template <class VertexType, class WeightType>
void CityGraph<VertexType, WeightType>::findAllPathsHelper(const VertexType &start, const VertexType &end, std::set<VertexType> &visitedVertices, std::vector<VertexType> &currPath, std::vector<std::vector<VertexType>> &allPaths, const std::set<VertexType> &closedIntersections)
{
    if (start.compare(end) == 0)
    {
        allPaths.push_back(currPath);
    }
    else
    {
        for (auto vert : neighbours[start])
        {
            if (visitedVertices.count(vert.first) == 0 && closedIntersections.count(vert.first) == 0)
            {
                currPath.push_back(vert.first);
                visitedVertices.insert(vert.first);

                findAllPathsHelper(vert.first, end, visitedVertices, currPath, allPaths, closedIntersections);
            }
        }
    }

    visitedVertices.erase(start);
    currPath.pop_back();
}

///Checks if there is a cycle in the graph
template <class VertexType, class WeightType>
bool CityGraph<VertexType, WeightType>::isCyclic(const VertexType &start)
{
    if (!hasVertex(start))
    {
        throw std::invalid_argument("invalid argument: ");
    }

    ///If there is a path from a neighbouring intersection to the start, then it means we have a path A->B and then path B->C->.....->A, which is essentially a cycle
    for (VertexType vert : findNeighbours(start))
    {
        if (hasPath(vert, start, {}))
        {
            return true;
        }
    }

    return false;
}

///Checks if we can fully traverse all edges(streets) of the graph(city) without taking the same edge(street) twice
template <class VertexType, class WeightType>
std::vector<VertexType> CityGraph<VertexType, WeightType>::chinesePostman()
{
    std::vector<VertexType> tourRoute;
    return tourRoute;
}

///Checks if we can reach all other vertices(interesections) from the current one
template <class VertexType, class WeightType>
bool CityGraph<VertexType, WeightType>::canReachEverywhere(const VertexType &current)
{
    ///Firstly, we check if the desired vertex(intersection) is part of the graph(city)
    if (!hasVertex(current))
    {
        throw std::invalid_argument("Invalid agrumet: ");
    }

    ///We create a set of all intersections we can reach
    std::set<VertexType> reachable;

    ///We obviously can reach the one we are in
    reachable.insert(current);

    ///We iterate through all the available intersections
    for (VertexType vert : intersections)
    {
        ///If we are yet to reach the current vertex(intersection), then we check if there is a path to there
        if (reachable.count(vert) == 0 && hasPath(current, vert, {}))
        {
            reachable.insert(vert);
        }
    }

    return reachable == intersections;
}

///Returns all neighbours of the given edge(intersection)
template <class VertexType, class WeightType>
std::set<VertexType> CityGraph<VertexType, WeightType>::findNeighbours(const VertexType &current)
{
    std::set<VertexType> neighbourIntersections;

    for (auto i : neighbours[current])
    {
        neighbourIntersections.insert(i.first);
    }

    return neighbourIntersections;
}

///Finds all dead-end streets
template <class VertexType, class WeightType>
std::set<std::pair<VertexType, VertexType>> CityGraph<VertexType, WeightType>::findDeadEnd()
{
    std::set<std::pair<VertexType, VertexType>> deadEndSet;

    ///We traverse all intersections
    for (VertexType inter : intersections)
    {
        ///For the current intersection we go through its neighbours
        for (std::pair<VertexType, WeightType> neigh : neighbours[inter])
        {
            ///If its neighbour has no streets that go out of it, then this is a dead end street
            if ((neighbours.find(neigh.first) == neighbours.end()) || neighbours[neigh.first].empty())
            {
                deadEndSet.insert(std::make_pair(inter, neigh.first));
            }
        }
    }

    return deadEndSet;
}

template <class VertexType, class WeightType>
void CityGraph<VertexType, WeightType>::deserializeHelperAlphabetic(char &iter, VertexType &curr, std::ifstream &input)
{
    do
    {
        input >> iter;
        curr += iter;
    } while (iter != ' ' && iter != '\n' && !input.eof());
}

template <class VertexType, class WeightType>
void CityGraph<VertexType, WeightType>::deserializeHelperNumeric(char &iter, WeightType &curr, std::ifstream &input)
{
    do
    {
        input >> iter;
        curr = curr * 10 + (iter - '0');
    } while (iter != ' ' && iter != '\n' && !input.eof());
}

template <class VertexType, class WeightType>
void CityGraph<VertexType, WeightType>::deserialize(std::ifstream &input)
{
    VertexType currVertex;
    VertexType currNeighbour;
    WeightType currWeight;
    std::set<std::pair<VertexType, WeightType>> currData;

    char iter;

    while (input)
    {
        currVertex.clear();
        currNeighbour.clear();

        deserializeHelperAlphabetic(iter, currVertex, input);

        while (iter != '\n')
        {
            deserializeHelperAlphabetic(iter, currNeighbour, input);

            currWeight = 0;
            deserializeHelperNumeric(iter, currWeight, input);

            if (!hasEdge(currVertex, currNeighbour))
            {
                std::pair<VertexType, WeightType> curr = std::make_pair(currNeighbour, currWeight);
                currData.insert(curr);
            }
            else
            {
                std::cout << "There is already a street between { " << currVertex << " } and { " << currNeighbour
                          << " }, so no more such additions are allowed!"
                          << std::endl;
            }
        }

        neighbours[currVertex] = currData;
    }
}

template <class VertexType, class WeightType>
bool CityGraph<VertexType, WeightType>::checkPathValidity(const VertexType &start, const VertexType &end)
{
    if (!hasVertex(start) || !hasVertex(end))
    {
        return false;
    }

    return true;
}

#endif
