/**
*	@file	AdventOfCode2019/Day8Puzzle1/Solution.cpp
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using String = std::string;

void GetLayers(const String filename, const int layerLength, std::vector<String> &layers)
{
	std::ifstream input(filename);
	String layer;
	layer.reserve(layerLength);
	int counter(1);
	char digit;
	while (input.get(digit))
	{
		layer.push_back(digit);

		if (0 == (counter % layerLength))
		{
			layers.push_back(layer);
			layer.clear();
		}

		++counter;
	}
	input.close();
}

void GetLeastZerosLayer(const std::vector<String> &layers, const int layerLength, String &fewestLayer)
{
	int fewestZeros(layerLength + 1);
	for (String layer : layers)
	{
		int numberOfZeros(std::count(layer.begin(), layer.end(), '0'));
		if (numberOfZeros < fewestZeros)
		{
			fewestZeros = numberOfZeros;
			fewestLayer = layer;
		}
	}
}

int OnesMultiplyTwos(const String layer)
{
	const int ones(std::count(layer.begin(), layer.end(), '1'));
	const int twos(std::count(layer.begin(), layer.end(), '2'));
	return ones * twos;
}

int main(int argc, char** argv)
{
	if (1 == argc)
		std::cout << "No filename was provided, using file \"input\"\n";

	const String filename = (1 == argc ? "input" : argv[1]);

	std::vector<String> layers;
	GetLayers(filename, 25 * 6, layers);

	String leastZerosLayer;
	GetLeastZerosLayer(layers, 25 * 6, leastZerosLayer);
	
	int result = OnesMultiplyTwos(leastZerosLayer);
	std::cout << "For the layer with the fewest 0 digits, the number of 1 digits multiplied by the number of 2 digits is: " << result << '\n';
}
