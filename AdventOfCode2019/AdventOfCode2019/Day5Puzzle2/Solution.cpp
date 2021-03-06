/**
 *	@file	AdventOfCode2019/Day5Puzzle2/Solution.cpp
 */

#include <iostream>
#include <string>

#include "AdventOfCode2019/Day2Puzzle1/IntcodeComputer.h"

using String = std::string;

int main(int argc, char **argv)
{
	if (1 == argc)
		std::cout << "No filename was provided, using file \"input\"\n";

	const String FILENAME = (1 == argc ? "input" : argv[1]);

	IntcodeComputer intcodeComputer(FILENAME);
	intcodeComputer.AppendInput(5);
	intcodeComputer.Run();

	std::cout << "The diagnostic code for system ID 5 is: " << intcodeComputer.GetOutput(0) << '\n';

	return EXIT_SUCCESS;
}
