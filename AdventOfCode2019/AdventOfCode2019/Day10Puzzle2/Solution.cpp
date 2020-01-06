/**
*	@file	AdventOfCode2019/Day10Puzzle2/Solution.cpp
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <map>
#include <utility>
#include <algorithm>

using String = std::string;
using Map = std::vector<std::vector<char>>;

int GCD(const int a, const int b)
{
	if (0 == b)
		return std::abs(a);
	else
		return std::abs(GCD(b, a % b));
}

class KeyData {
public:
	bool ySign;
	bool xSign;
	float gradient;

	bool operator==(const KeyData &rhs) const
	{
		return ((this->gradient == rhs.gradient) && (this->ySign == rhs.ySign) && (this->xSign == rhs.xSign));
	}

	bool operator<(const KeyData &rhs) const
	{
		// Irreflexivity.
		if (*this == rhs)
			return false;

		// rhs is before based on sector.
		if ((this->xSign == false) && (this->ySign == false) && (rhs.xSign == false) && (rhs.ySign == true)  ||
			(this->xSign == false) && (this->ySign == false) && (rhs.xSign == true)  && (rhs.ySign == false) ||
			(this->xSign == false) && (this->ySign == false) && (rhs.xSign == true)  && (rhs.ySign == true)  ||
			(this->xSign == false) && (this->ySign == true)  && (rhs.xSign == true)  && (rhs.ySign == false) ||
			(this->xSign == false) && (this->ySign == true)  && (rhs.xSign == true)  && (rhs.ySign == true)  ||
			(this->xSign == true)  && (this->ySign == true)  && (rhs.xSign == true)  && (rhs.ySign == false))
			return false;

		// lhs is before based on sector.
		if ((this->xSign == false) && (this->ySign == true)  && (rhs.xSign == false) && (rhs.ySign == false) ||
			(this->xSign == true)  && (this->ySign == false) && (rhs.xSign == false) && (rhs.ySign == true)  ||
			(this->xSign == true)  && (this->ySign == false) && (rhs.xSign == false) && (rhs.ySign == false) ||
			(this->xSign == true)  && (this->ySign == false) && (rhs.xSign == true)  && (rhs.ySign == true)  ||
			(this->xSign == true)  && (this->ySign == true)  && (rhs.xSign == false) && (rhs.ySign == false) ||
			(this->xSign == true)  && (this->ySign == true)  && (rhs.xSign == false) && (rhs.ySign == true))
			return true;

		// all negative or all positive. Whichever is closest to 0.
		if ((this->xSign == false) && (this->ySign == false) && (rhs.xSign == false) && (rhs.ySign == false) ||
			(this->xSign == true)  && (this->ySign == true)  && (rhs.xSign == true)  && (rhs.ySign == true))
		{
			if (std::abs(this->gradient) < std::abs(rhs.gradient))
				return true;
			else
				return false;
		}

		// same with x and y signs differing. Which is most negative.
		if ((this->xSign == false) && (this->ySign == true)  && (rhs.xSign == false) && (rhs.ySign == true)  ||
			(this->xSign == true)  && (this->ySign == false) && (rhs.xSign == true)  && (rhs.ySign == false))
		{
			if (this->gradient < rhs.gradient)
				return true;
			else
				return false;
		}
	}
};

class KeyDataHash {
public:
	size_t operator()(const KeyData &tryingData) const
	{
		return (HashCombine(std::hash<bool>()(tryingData.ySign), HashCombine(std::hash<bool>()(tryingData.xSign), std::hash<float>()(tryingData.gradient))));
	}

private:
	size_t HashCombine(size_t lhs, size_t rhs) const
	{
		lhs ^= rhs + 0x9e3779b9 + (lhs << 6) + (lhs >> 2);
		return lhs;
	}
};

void PrintMap(const Map &map)
{
	const size_t width = map.size();
	const size_t height = map[0].size();
	for (size_t x = 0; x < width; ++x)
	{
		for (size_t y = 0; y < height; ++y)
		{
			std::cout << map[x][y];
		}
		std::cout << '\n';
	}
}

float GetGradient(const int xDifference, const int yDifference)
{
	float gradient;
	if ((0 == xDifference) && (0 == yDifference))
		gradient = 0;
	else if ((0 == xDifference) && (0 > yDifference))
		gradient = -std::numeric_limits<float>::infinity();
	else if ((0 == xDifference) && (0 <= yDifference))
		gradient = std::numeric_limits<float>::infinity();
	else
		gradient = yDifference / static_cast<float>(xDifference);

	return gradient;
}

int GetDetectionAmounts(const int y, const int x, const Map &map)
{
	const size_t width = map[0].size();
	const size_t height = map.size();
	std::unordered_set<KeyData, KeyDataHash> haveTried;
	int numberFound(0);

	for (int i = 0; i < width; ++i)
	{
		for (int j = 0; j < height; ++j)
		{
			// Get data of attempt.
			const int xDifference = i - x;
			const int yDifference = j - y;
			if ((0 == xDifference) && (0 == yDifference))
				continue;
			const float gradient = GetGradient(xDifference, yDifference);
			const KeyData trying{ !std::signbit((float)yDifference), !std::signbit((float)xDifference), gradient };

			// Check if already done
			auto search = haveTried.find(trying);
			if (haveTried.end() != search)
			{
				continue;
			}
			else
			{
				haveTried.insert(trying);
				const int gcd = GCD(yDifference, xDifference);
				const int xStep = xDifference / gcd;
				const int yStep = yDifference / gcd;

				// Check for asteroid.
				for (int xCheck = x + xStep, yCheck = y + yStep;
					(xCheck >= 0) && (xCheck < width) && (yCheck >= 0) && (yCheck < height);
					xCheck += xStep, yCheck += yStep)
				{
					if ('#' == map[yCheck][xCheck])
					{
						++numberFound;
						break;
					}
				}
			}
		}
	}

	return numberFound;
}

std::pair<int, int> GetVaporisedAsteroid(const int y, const int x, Map map, const int which)
{
	const size_t width = map[0].size();
	const size_t height = map.size();
	std::map<KeyData, std::pair<int, int>> angles;

	// Map all angles to their steps. Sorted correctly using KeyData::operator<.
	for (int i = 0; i < width; ++i)
	{
		for (int j = 0; j < height; ++j)
		{
			// Get data of angle.
			const int xDifference = i - x;
			const int yDifference = j - y;
			if ((0 == xDifference) && (0 == yDifference))
				continue;
			const float gradient = GetGradient(xDifference, yDifference);
			const KeyData angle{ !std::signbit((float)yDifference), !std::signbit((float)xDifference), gradient };

			// Check if already done
			auto search = angles.find(angle);
			if (angles.end() != search)
			{
				continue;
			}
			else
			{
				const int gcd = GCD(yDifference, xDifference);
				const int xStep = xDifference / gcd;
				const int yStep = yDifference / gcd;
				
				angles[angle] = std::pair<int, int>(xStep, yStep);
			}
		}
	}

	// Loop over angles repeatedly until nothing was vaporised for a loop.
	std::vector<std::pair<int, int>> vaporised;
	bool haveVaporised;
	do
	{
		haveVaporised = false;
		for (auto const &element : angles)
		{
			const int xStep(element.second.first);
			const int yStep(element.second.second);

			for (int xCheck = x + xStep, yCheck = y + yStep;
				(xCheck >= 0) && (xCheck < width) && (yCheck >= 0) && (yCheck < height);
				xCheck += xStep, yCheck += yStep)
			{
				if ('#' == map[yCheck][xCheck])
				{
					haveVaporised = true;
					map[yCheck][xCheck] = '.';
					vaporised.push_back(std::pair<int, int>(xCheck, yCheck));
					break;
				}
			}
		}
	} while (haveVaporised);

	return vaporised[which - 1];
}

int main(int argc, char** argv)
{
	if (1 == argc)
		std::cout << "No filename was provided, using file \"input\"\n";

	const String filename = (1 == argc ? "input" : argv[1]);

	std::ifstream input(filename);

	// Read in map.
	Map map;
	String line;
	while (std::getline(input, line))
	{
		std::vector<char> row;
		for (char location : line)
		{
			row.push_back(location);
		}
		map.push_back(row);
	}
	input.close();

	// Find best location amount.
	const size_t width = map[0].size();
	const size_t height = map.size();
	int best(0), bestX(-1), bestY(-1);
	for (int x = 0; x < width; ++x)
	{
		for (int y = 0; y < height; ++y)
		{
			if ('#' == map[y][x])
			{
				const int n = GetDetectionAmounts(y, x, map);
				if (n > best)
				{
					best = n;
					bestX = x;
					bestY = y;
				}
			}
		}
	}
	std::cout << "The most number of astroids that can been seen is: " << best << " at location: " << bestX << ',' << bestY << '\n';

	// Vaporise asteroids.
	const std::pair<int, int> twoHundredth = GetVaporisedAsteroid(bestY, bestX, map, 200);
	std::cout << "The coordinate of the 200th asteroid vaprosied was: " << twoHundredth.first << ',' << twoHundredth.second << '\n';
	std::cout << "Therefore the answer is: " << ((100 * twoHundredth.first) + twoHundredth.second) << '\n';

	return EXIT_SUCCESS;
}
