/**
 *	@file	AdventOfCode2019/Day14Puzzle1/Solution.cpp
 */

#include <iostream>
#include <string>
#include <unordered_map>

using String = std::string;

int main(int argc, char **argv)
{
	if (1 == argc)
		std::cout << "No filename was provided, using file \"input\"\n";

	const String filename = (1 == argc ? "input" : argv[1]);

	// Read in input into map. rhs is key to vector of lhs chemicals.

	// Initalise what is needed to nothing.
	// Find FUEL. Add to what is needed.
	// Keep replacing everything inside needed with the input chemicals to make them.
	// Do this until all needed is made with ORE.
	// Once all needed is a primary chemical made from ore finally convert into ore amounts.

	return EXIT_SUCCESS;
}
