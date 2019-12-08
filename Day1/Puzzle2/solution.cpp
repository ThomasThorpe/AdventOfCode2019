/**
 *  @file   AdventOfCode2019/Day1/Puzzle2/solution.cpp
 */

#include "solution.h"

int AdditionalFuel(int fuelAsMass)
{
    int additionalFuel = (fuelAsMass / 3) - 2;
    if (additionalFuel <= 0)
        return 0;
    else
        return additionalFuel + AdditionalFuel(additionalFuel);
}

int main(int argc, char **argv)
{
    typedef std::string String;

    if (1 == argc)
        std::cout << "No filename was provided, using file \"input\"\n";

    const String FILENAME = (1 == argc ? "input" : argv[1]);
    std::ifstream INPUT(FILENAME);

    int totalFuel(0);
    String mass;
    while (std::getline(INPUT,mass))
    {
        int moduleFuel = (std::stoi(mass) / 3) - 2;
        moduleFuel += AdditionalFuel(moduleFuel);
        totalFuel += moduleFuel;
    }
    std::cout << "The total fuel required is: " << totalFuel << '\n';

    return EXIT_SUCCESS;
}