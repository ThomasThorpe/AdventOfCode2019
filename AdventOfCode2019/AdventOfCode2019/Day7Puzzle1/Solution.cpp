/**
*	@file	AdventOfCode2019/Day7Puzzle1/Solution.cpp
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "AdventOfCode2019/Day2Puzzle1/IntcodeComputer.h"

using String = std::string;
using IntVector = std::vector<int>;

int main(int argc, char **argv)
{
	if (1 == argc)
		std::cout << "No filename was provided, using file \"input\"\n";

	const String FILENAME = (1 == argc ? "input" : argv[1]);

	int largest(0), output;
	IntVector phaseSettings{ 0, 1, 2, 3, 4 };
	do
	{
		IntcodeComputer intcodeComputer(FILENAME);
		intcodeComputer.AppendInput(phaseSettings[0]);
		intcodeComputer.AppendInput(0);
		(void) intcodeComputer.Run();
		output = intcodeComputer.GetOutput(0);
		intcodeComputer.Reset();

		intcodeComputer.ReadIntcodeProgram(FILENAME);
		intcodeComputer.AppendInput(phaseSettings[1]);
		intcodeComputer.AppendInput(output);
		(void) intcodeComputer.Run();
		output = intcodeComputer.GetOutput(0);
		intcodeComputer.Reset();

		intcodeComputer.ReadIntcodeProgram(FILENAME);
		intcodeComputer.AppendInput(phaseSettings[2]);
		intcodeComputer.AppendInput(output);
		(void) intcodeComputer.Run();
		output = intcodeComputer.GetOutput(0);
		intcodeComputer.Reset();

		intcodeComputer.ReadIntcodeProgram(FILENAME);
		intcodeComputer.AppendInput(phaseSettings[3]);
		intcodeComputer.AppendInput(output);
		(void) intcodeComputer.Run();
		output = intcodeComputer.GetOutput(0);
		intcodeComputer.Reset();

		intcodeComputer.ReadIntcodeProgram(FILENAME);
		intcodeComputer.AppendInput(phaseSettings[4]);
		intcodeComputer.AppendInput(output);
		(void) intcodeComputer.Run();
		output = intcodeComputer.GetOutput(0);
		intcodeComputer.Reset();

		if (output > largest)
			largest = output;
	}
	while (std::next_permutation(phaseSettings.begin(), phaseSettings.end()));

	std::cout << "The largest output signal found was: " << largest << '\n';

	return EXIT_SUCCESS;
}
