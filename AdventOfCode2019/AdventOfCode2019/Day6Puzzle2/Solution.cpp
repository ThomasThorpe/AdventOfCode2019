/**
*	@file	AdventOfCode2019/Day6Puzzle2/Solution.cpp
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
using StringVector = std::vector<String>;

int GetOrbits(const String key, OrbitMap &orbitMap)
{
	const String value = orbitMap[key];
	if (value.empty())
		return 0;
	else
		return 1 + GetOrbits(value, orbitMap);
}

void GetPathInformation(const String key, OrbitMap &orbitMap, StringVector &path)
{
	path.push_back(key);

	const String value = orbitMap[key];
	if (!value.empty())
		GetPathInformation(value, orbitMap, path);
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
	std::cout << "The total number of orbits in the map is: " << numberOfOrbits << '\n';

	// Part 2.
	StringVector myPath, santaPath;
	GetPathInformation(orbitMap["YOU"], orbitMap, myPath);
	GetPathInformation(orbitMap["SAN"], orbitMap, santaPath);

	size_t i(myPath.size() - 1), j(santaPath.size() - 1);
	while (myPath[i] == santaPath[j])
	{
		--i, --j;
	}
	++i, ++j;
	std::cout << "The number of orbital tranfers to santa is: " << i + j << '\n';

	return EXIT_SUCCESS;
}
