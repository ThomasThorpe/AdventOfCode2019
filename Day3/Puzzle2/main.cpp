/**
 *  @file   AdventOfCode2019/Day3/Puzzle2/main.cpp
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>
#include <algorithm>
#include <vector>
#include <utility>
#include <limits>
#include <string>

using String = std::string;
using StringVector = std::vector<String>;
using Coordinate = std::pair<int, int>;
using CoordinateVector = std::vector<Coordinate>;

int GetManhattanDistance(const Coordinate &coordinate)
{
    return std::abs(coordinate.first) + abs(coordinate.second);
}

int FindFastest(const CoordinateVector &wire1Coordinates, const CoordinateVector &wire2Coordinates, const CoordinateVector &intersections)
{
    int fastest(std::numeric_limits<int>::max());
    for (const Coordinate coordinate : intersections)
    {
        CoordinateVector::const_iterator itr1(std::find(wire1Coordinates.begin(), wire1Coordinates.end(), coordinate));
        CoordinateVector::const_iterator itr2(std::find(wire2Coordinates.begin(), wire2Coordinates.end(), coordinate));
        if (itr1 != wire1Coordinates.end() && itr2 != wire2Coordinates.end())
        {
            const int length((std::distance(wire1Coordinates.begin(), itr1)) + (std::distance(wire2Coordinates.begin(), itr2)));
            if ((length < fastest) && (0 != length))
                fastest = length;
        }
        else
        {
            throw std::logic_error("There is an intersection point that does not exist in both wire coordinates!\n");
        }
    }

    return fastest;
}

int FindClosest(const CoordinateVector &coordinates)
{
    if (0 == coordinates.size())
        throw std::length_error("There are no coordinates to check!\n");

    int closest(std::numeric_limits<int>::max());
    for (const Coordinate coordinate : coordinates)
    {
        const int result(GetManhattanDistance(coordinate));
        if ((result < closest) && (result != 0))
            closest = result;
    }

    return closest;
}

void FindIntersectionPoints(const CoordinateVector &wire1Coordinates, const CoordinateVector &wire2Coordinates, CoordinateVector &intersections)
{
    for (const Coordinate coordinate1 : wire1Coordinates)
    {
        for (const Coordinate coordinate2 : wire2Coordinates)
        {
            if (coordinate1 == coordinate2)
                intersections.push_back(coordinate1);
        }
    }
}

void GetWireInput(std::ifstream &INPUT, StringVector &wireInput)
{
    String line;
    std::getline(INPUT, line);
    std::istringstream lineStream(line);
    String direction;
    while (std::getline(lineStream, direction, ','))
    {
        wireInput.push_back(direction);
    }
}

void GetWireCoordinates(const StringVector &wireInput, CoordinateVector &coordinateVector)
{
    int x(0), y(0), newX(0), newY(0);
    coordinateVector.push_back(Coordinate(x, y));
    for (const String direction : wireInput)
    {
        const int length = std::stoi(direction.substr(1));

        switch (direction.at(0))
        {
        case 'U':
            for (int i = 0; i < length; ++i)
            {
                newY = y + 1;
                coordinateVector.push_back(Coordinate(newX, newY));
                y = newY;
            }
            break;
        case 'R':
            for (int i = 0; i < length; ++i)
            {
                newX = x + 1;
                coordinateVector.push_back(Coordinate(newX, newY));
                x = newX;
            }
            break;
        case 'D':
            for (int i = 0; i < length; ++i)
            {
                newY = y - 1;
                coordinateVector.push_back(Coordinate(newX, newY));
                y = newY;
            }
            break;
        case 'L':
            for (int i = 0; i < length; ++i)
            {
                newX = x - 1;
                coordinateVector.push_back(Coordinate(newX, newY));
                x = newX;
            }
            break;
        default:
            throw std::invalid_argument("Invalid direction character!\n");
        }
    }
}

int main(int argc, char **argv)
{
    if (1 == argc)
        std::cout << "No filename as provided, using \"input\"\n";

    const String FILENAME = (1 == argc ? "input" : argv[1]);
    std::ifstream INPUT(FILENAME);

    StringVector wire1Input;
    GetWireInput(INPUT, wire1Input);
    StringVector wire2Input;
    GetWireInput(INPUT, wire2Input);
    INPUT.close();

    CoordinateVector wire1Coordinates;
    CoordinateVector wire2Coordinates;
    try
    {
        GetWireCoordinates(wire1Input, wire1Coordinates);
        GetWireCoordinates(wire2Input, wire2Coordinates);
    }
    catch (std::invalid_argument e)
    {
        std::cout << e.what();
        return EXIT_FAILURE;
    }

    CoordinateVector intersections;
    FindIntersectionPoints(wire1Coordinates, wire2Coordinates, intersections);

    try
    {
        std::cout << "The distance of the clostest intersection point is: " << FindClosest(intersections) << '\n';
        std::cout << "The length of the fastest intersection point is: " << FindFastest(wire1Coordinates, wire2Coordinates, intersections) << '\n';
    }
    catch (std::length_error e)
    {
        std::cout << e.what();
        return EXIT_FAILURE;
    }
    catch (std::logic_error e)
    {
        std::cout << e.what();
        return EXIT_FAILURE;
    }

    std::cout << "Press any key to exit";
    std::cin.get();

    return EXIT_SUCCESS;
}