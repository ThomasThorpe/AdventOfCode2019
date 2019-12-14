/**
 *  @file   AdventOfCode2019/Day2/Puzzle2/main.cpp
 */

#include "AdventOfCode2019/Day2/Puzzle1/IntcodeComputer.h"

int main(int argc, char **argv)
{
    bool b(false);

    if (1 == argc)
        std::cout << "No filename was provided, using file \"input\"\n";

    const String FILENAME = (1 == argc ? "input" : argv[1]);

    IntcodeComputer intcodeComputer(FILENAME);
    for (int noun = 0; noun < 100; ++noun)
    {
        for (int verb = 0; verb < 100; ++verb)
        {
            intcodeComputer.ReadIntcodeProgram(FILENAME);
            intcodeComputer.Write(1,noun);
            intcodeComputer.Write(2,verb);
            intcodeComputer.Run();

            const int output = intcodeComputer.Read(0);
            if (19690720 == output)
            {
                std::cout << "Found the solution!\n"
                          << "Noun was: " << noun << '\n'
                          << "Verb was: " << verb << '\n'
                          << "100 * noun + verb is: " << ((100 * noun) + verb) << '\n';
                break;
            }
        }
    }
}