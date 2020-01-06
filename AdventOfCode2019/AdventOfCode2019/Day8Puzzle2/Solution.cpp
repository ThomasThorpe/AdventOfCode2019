/**
*	@file	AdventOfCode2019/Day8Puzzle2/Solution.cpp
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

void DecodeImage(const std::vector<String> &layers, const int layerLength, String &message)
{
	// for each pixel in range 0-149. go from top layer to bottom. if transparent pixel, go to next layer, repeat until either white or black.
	for (int pixel = 0; pixel < layerLength; ++pixel)
	{
		int layer(0);
		char colour('2');
		while ('2' == colour)
		{
			if ('2' != layers[layer][pixel])
				colour = layers[layer][pixel];
			else
				++layer;
		}
		message.push_back(colour);
	}
}

void PrintImage(const String &message, const int width)
{
	for (int i = 1; i - 1 < message.size(); ++i)
	{
		if ('1' == message[i-1])
			std::cout << '#';
		else if ('0' == message[i-1])
			std::cout << ' ';
		
		if ((0 == i % width) && (0 != i))
			std::cout << '\n';
	}
}

int main(int argc, char** argv)
{
	if (1 == argc)
		std::cout << "No filename was provided, using file \"input\"\n";

	const String filename = (1 == argc ? "input" : argv[1]);

	std::vector<String> layers;
	const int layerLenth = 25 * 6;
	GetLayers(filename, layerLenth, layers);

	String message;
	DecodeImage(layers, layerLenth, message);

	PrintImage(message, 25);
}
