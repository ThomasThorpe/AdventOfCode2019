/**
 *  @file   AdventOfCode2019/Day2/Puzzle1/main.cpp
 */

#include "IntcodeComputer.h"

int main(int argc, char **argv)
{
    if (1 == argc)
        std::cout << "No filename was provided, using file \"input\"\n";
    
    const String FILENAME = (1 == argc ? "input" : argv[1]);

    IntcodeComputer intcodeComputer(FILENAME);
    intcodeComputer.Write(1,12);
    intcodeComputer.Write(2,2);
    intcodeComputer.Run();

    return EXIT_SUCCESS;
}