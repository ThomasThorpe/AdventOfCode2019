/**
 *	@file	AdventOfCode2019/Day5Puzzle1/Solution.cpp
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
	intcodeComputer.AppendInput(1);
	intcodeComputer.Run();

	std::cout << "The diagnostic code was: " << intcodeComputer.GetOutput(intcodeComputer.GetOutputSize() - 1) << '\n';

	return EXIT_SUCCESS;
}
