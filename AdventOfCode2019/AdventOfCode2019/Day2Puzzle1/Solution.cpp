/**
 *	@file	AdventOfCode2019/Day2Puzzle1/Solution.cpp
 */

#include <iostream>
#include <string>

#include "IntcodeComputer.h"

using String = std::string;

int main(int argc, char **argv)
{
	if (1 == argc)
		std::cout << "No filename was provided, using file \"input\"\n";
	
	const String FILENAME = (1 == argc ? "input" : argv[1]);

	IntcodeComputer intcodeComputer(FILENAME);
	intcodeComputer.Write(1,12);
	intcodeComputer.Write(2,2);
	intcodeComputer.Run();
	std::cout << "The value left at position after the program halts is: " << intcodeComputer.Read(0) << '\n';

	return EXIT_SUCCESS;
}
