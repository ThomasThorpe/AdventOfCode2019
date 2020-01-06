/**
*	@file	AdventOfCode2019/Day7Puzzle2/Solution.cpp
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
	IntVector phaseSettings{ 5, 6, 7, 8, 9 };
	do
	{
		// Setup.
		IntcodeComputer AmpA(FILENAME, "Amplifier A");
		AmpA.AppendInput(phaseSettings[0]);
		AmpA.AppendInput(0);
		IntcodeComputer AmpB(FILENAME, "Amplifier B");
		AmpB.AppendInput(phaseSettings[1]);
		IntcodeComputer AmpC(FILENAME, "Amplifier C");
		AmpC.AppendInput(phaseSettings[2]);
		IntcodeComputer AmpD(FILENAME, "Amplifier D");
		AmpD.AppendInput(phaseSettings[3]);
		IntcodeComputer AmpE(FILENAME, "Amplifier E");
		AmpE.AppendInput(phaseSettings[4]);

		while (IntcodeComputer::ProcessState::TERMINATED != AmpE.GetProcessState())
		{
			(void) AmpA.Run();
			output = AmpA.GetLastOutput();

			AmpB.AppendInput(output);
			(void) AmpB.Run();
			output = AmpB.GetLastOutput();

			AmpC.AppendInput(output);
			(void) AmpC.Run();
			output = AmpC.GetLastOutput();
			
			AmpD.AppendInput(output);
			(void) AmpD.Run();
			output = AmpD.GetLastOutput();

			AmpE.AppendInput(output);
			(void) AmpE.Run();
			output = AmpE.GetLastOutput();

			if (IntcodeComputer::ProcessState::TERMINATED != AmpE.GetProcessState())
			{
				AmpA.AppendInput(output);
			}
		}

		if (output > largest)
			largest = output;
	}
	while (std::next_permutation(phaseSettings.begin(), phaseSettings.end()));

	std::cout << "The largest output signal found was: " << largest << '\n';

	return EXIT_SUCCESS;
}
