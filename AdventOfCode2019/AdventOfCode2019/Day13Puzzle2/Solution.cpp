/**
 *	@file	AdventOfCode2019/Day13Puzzle2/Solution.cpp
 */

#include <iostream>
#include <string>

#include "AdventOfCode2019/Day13Puzzle1/ArcadeCabient.h"

using String = std::string;

int main(int argc, char **argv)
{
	if (1 == argc)
		std::cout << "No filename was provided, using file \"input\"\n";

	const String filename = (1 == argc ? "input" : argv[1]);

	ArcadeCabient arcadeCabient(filename);
	arcadeCabient.InsertCoins();
	(void) arcadeCabient.Run();

	return EXIT_SUCCESS;
}
