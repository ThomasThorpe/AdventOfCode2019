/**
 *	@file	AdventOfCode2019/Day4Puzzle2/Solution.cpp
 */

#include <iostream>
#include <string>

using String = std::string;

bool IsNeverDecreasing(const int number)
{
	const String stringNumber(std::to_string(number));

	for (int i = 0; i < stringNumber.size(); ++i)
	{
		const char digit(stringNumber[i]);
		const char nextDigit(stringNumber.size() - 1 == i ? 'T' : stringNumber[i + 1]);

		if ('T' == nextDigit)
			continue;

		if (nextDigit < digit)
			return false;
	}

	return true;
}

bool HasDoubleDigits(const int number)
{
	const String stringNumber(std::to_string(number));

	for (int i = 0; i < stringNumber.size(); ++i)
	{
		const char previousDigit(0 == i ? 'T' : stringNumber[i - 1]);
		const char digit(stringNumber[i]);
		const char nextDigit(stringNumber.size() - 1 == i ? 'T' : stringNumber[i + 1]);
		const char twoAheadDigit('T' == nextDigit || stringNumber.size() - 2 == i ? 'T' : stringNumber[i + 2]);

		if ((previousDigit != digit) && (digit == nextDigit) && (twoAheadDigit != digit))
			return true;
	}

	return false;
}

bool HasMatchingAdjacentNumbers(const int number)
{
	const String stringNumber(std::to_string(number));

	for (int i = 0; i < stringNumber.size(); ++i)
	{
		const char digit(stringNumber[i]);
		const char nextDigit(stringNumber.size() - 1 == i ? 'T' : stringNumber[i + 1]);

		if (digit == nextDigit)
			return true;
	}

	return false;
}

int CalulcatePossiblePasswords(const int start, const int end)
{
	int count(0);
	for (int i = start; i <= end; ++i)
	{
		// Check if a six digit number.
		if (100000 > i || 999999 < i)
			continue;

		// Check if two adjacent digits are the same.
		if (!HasDoubleDigits(i))
			continue;

		// Check if digits never decrease from left to right.
		if (!IsNeverDecreasing(i))
			continue;

		++count;
	}

	return count;
}

int main()
{
	std::cout << "The number of possible passwords between 240920 and 789857 is: " << CalulcatePossiblePasswords(240920, 789857) << '\n';

	return EXIT_SUCCESS;
}
