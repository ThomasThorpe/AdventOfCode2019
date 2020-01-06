/**
 *  @file   AdventOfCode2019/Day1Puzzle1/Solution.cpp
 */

#include <string>
#include <iostream>
#include <fstream>

using String = std::string;

int main(int argc, char **argv)
{
	if (1 == argc)
		std::cout << "No filename was provided, using file \"input\"\n";

	const String FILENAME = (1 == argc ? "input" : argv[1]);
	std::ifstream INPUT(FILENAME);

	int totalFuel(0);
	String mass;
	while (std::getline(INPUT,mass))
	{
		totalFuel += (std::stoi(mass) / 3) - 2;
	}
	std::cout << "The total fuel required is: " << totalFuel << '\n';

	return EXIT_SUCCESS;
}
