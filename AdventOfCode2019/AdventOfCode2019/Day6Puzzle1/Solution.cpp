/**
*	@file	AdventOfCode2019/Day6Puzzle1/Solution.cpp
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <utility>

using String = std::string;
using OrbitMap = std::unordered_map<String, String>;

int GetOrbits(String key, OrbitMap &orbitMap)
{
	const String value = orbitMap[key];
	if (value.empty())
		return 0;
	else
		return 1 + GetOrbits(value, orbitMap);
}

int main(int argc, char **argv)
{
	if (1 == argc)
		std::cout << "No filename was provided, using file \"input\"\n";

	const String filename = (1 == argc ? "input" : argv[1]);
	std::ifstream input(filename);

	OrbitMap orbitMap;
	std::vector<String> objects;
	String line, object;
	while (std::getline(input, line))
	{
		std::stringstream ss(line);
		while (std::getline(ss, object, ')'))
		{
			objects.push_back(object);
		}

		orbitMap[objects[1]] = objects[0];
		objects.clear();
	}
	input.close();

	int numberOfOrbits(0);
	for (const auto &element : orbitMap)
	{
		numberOfOrbits += GetOrbits(element.first, orbitMap);
	}
	std::cout << numberOfOrbits << '\n';

	return EXIT_SUCCESS;
}
