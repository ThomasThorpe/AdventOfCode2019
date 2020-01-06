/**
 *	@file	AdventOfCode2019/Day12Puzzle1/Solution.cpp
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <array>
#include <vector>
#include <unordered_set>
#include <utility>
#include <numeric>

using String = std::string;
using Position = std::array<int, 3>;
using Velocity = std::array<int, 3>;
using Moon = std::pair<Position, Velocity>;

class MoonsHash
{
public:
	size_t operator()(const std::vector<Moon> &moons) const
	{
		size_t hash(0);
		for (const Moon &moon : moons)
		{
			HashCombine(std::hash<int>()(hash), (MoonHash(moon)));
		}
		return hash;
	}

	size_t MoonHash (const Moon &moon) const
	{
		return (HashCombine(std::hash<int>()(moon.first[0]),
				HashCombine(std::hash<int>()(moon.first[1]),
				HashCombine(std::hash<int>()(moon.first[2]),
				HashCombine(std::hash<int>()(moon.second[0]),
				HashCombine(std::hash<int>()(moon.second[1]),
				std::hash<int>()(moon.second[2])))))));
	}

private:
	size_t HashCombine(size_t lhs, size_t rhs) const
	{
		lhs ^= rhs + 0x9e3779b9 + (lhs << 6) + (lhs >> 2);
		return lhs;
	}
};

void PrintSystemState(const std::vector<Moon> &moons, const bool showEnergy = false)
{
	for (const Moon &moon : moons)
	{
		std::cout << "pos=<x=" << moon.first[0]  << ", y=" << moon.first[1]  << ", z=" << moon.first[2]  << ">, "
				  << "vel=<x=" << moon.second[0] << ", y=" << moon.second[1] << ", z=" << moon.second[2] << ">\n";
	}

	// TODO: Display energy as shown in puzzle.txt
}

void ReadInput(const String &filename, std::vector<Moon> &moons)
{
	std::ifstream input(filename);

	String line;
	while (std::getline(input, line))
	{
		Moon moon;
		
		std::stringstream ss(line);
		String value;
		String segment;
		int position(0);
		while (std::getline(ss, segment, ','))
		{
			bool start(false);
			for (const char &c : segment)
			{
				if ('=' == c)
				{
					start = true;
					continue;
				}

				if (start)
				{
					if ('>' == c)
						continue;

					value += c;
				}
			}

			moon.first[position] = std::stoi(value);
			value.clear();
			++position;
		}

		moons.push_back(moon);
	}
	input.close();
}

void UpdatePositions(std::vector<Moon> &moons)
{
	for (Moon &moon : moons)
	{
		moon.first[0] += moon.second[0];
		moon.first[1] += moon.second[1];
		moon.first[2] += moon.second[2];
	}
}

void UpdateVelocity(std::vector<Moon> &moons)
{
	for (int i = 0; i < moons.size(); ++i)
	{
		for (int j = i + 1; j < moons.size(); ++j)
		{
			Moon &moon1 = moons[i], &moon2 = moons[j];

			// X axis.
			if (moon1.first[0] > moon2.first[0])
			{
				--moon1.second[0];
				++moon2.second[0];
			}
			else if (moon1.first[0] < moon2.first[0])
			{
				++moon1.second[0];
				--moon2.second[0];
			}

			// Y axis.
			if (moon1.first[1] > moon2.first[1])
			{
				--moon1.second[1];
				++moon2.second[1];
			}
			else if (moon1.first[1] < moon2.first[1])
			{
				++moon1.second[1];
				--moon2.second[1];
			}

			// Z axis.
			if (moon1.first[2] > moon2.first[2])
			{
				--moon1.second[2];
				++moon2.second[2];
			}
			else if (moon1.first[2] < moon2.first[2])
			{
				++moon1.second[2];
				--moon2.second[2];
			}
		}
	}
}

void SimulateMotion(const int timesteps, std::vector<Moon> &moons)
{
	for (int step = 0; step < timesteps; ++step)
	{
		UpdateVelocity(moons);
		UpdatePositions(moons);
	}
}

int CalculateTotalEnergy(const std::vector<Moon> &moons)
{
	static const auto abssum = [](auto x, auto y){ return x + std::abs(y); };

	int totalEnergy(0);
	for (const Moon &moon : moons)
	{
		totalEnergy += std::accumulate(moon.first.begin(), moon.first.end(), 0, abssum) * std::accumulate(moon.second.begin(), moon.second.end(), 0, abssum);
	}

	return totalEnergy;
}

int FindRepeated(std::vector<Moon> &moons)
{
	std::unordered_set<std::vector<Moon>, MoonsHash> hasBeen;

	int timestep(0);
	bool foundRepeat(false);
	while (!foundRepeat)
	{
		auto search = hasBeen.find(moons);
		if (hasBeen.end() == search)
		{
			// Not seen before.
			hasBeen.insert(moons);
			UpdateVelocity(moons);
			UpdatePositions(moons);
			++timestep;
		}
		else
		{
			// Seen before
			return timestep;
		}
	}
}

int main(int argc, char **argv)
{
	if (1 == argc)
		std::cout << "No filename was provided, using file \"input\"\n";

	const String filename = (1 == argc ? "input" : argv[1]);

	std::vector<Moon> moons;
	moons.reserve(4);
	ReadInput(filename, moons);
	const int timesteps = FindRepeated(moons);

	std::cout << "The number of timesteps to get to a previous state was: " << timesteps << '\n';

	return EXIT_SUCCESS;
}
