/**
 *	@file	AdventOfCode2019/Day11Puzzle2/Solution.cpp
 */

#include <iostream>
#include <string>

#include "HullPaintingRobot.h"

using String = std::string;
using Coorindate = std::pair<int, int>;

int main(int argc, char **argv)
{
	if (1 == argc)
		std::cout << "No filename was provided, using file \"input\"\n";

	const String filename = (1 == argc ? "input" : argv[1]);

	HullPaintingRobot hullPaintingRobot(filename);
	(void) hullPaintingRobot.Run();

	return EXIT_SUCCESS;
}
