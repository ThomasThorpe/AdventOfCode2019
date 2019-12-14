/**
 *  @file   AdventOfCode2019/Day2/Puzzle1/IntcodeComputer.cpp
 * 
 *  @brief  Implementation of the IntcodeComputer class.
 */

#include "IntcodeComputer.h"

// ---------------------------------------------------------------------------------------------------------------------------------

IntcodeComputer::IntcodeComputer(const String &FILENAME) :
    isLogging(false)
{
    ReadIntcodeProgram(FILENAME);
}

// ---------------------------------------------------------------------------------------------------------------------------------

IntcodeComputer::~IntcodeComputer()
{
}

// ---------------------------------------------------------------------------------------------------------------------------------

void IntcodeComputer::SaveIntcodeOutput(const String &FILENAME) const
{
    std::ofstream OUTPUT(FILENAME);

    for (int number : memory)
    {
        OUTPUT << number << ',';
    }
}

// ---------------------------------------------------------------------------------------------------------------------------------

void IntcodeComputer::ReadIntcodeProgram(const String &FILENAME)
{
    std::ifstream INPUT(FILENAME);
    memory.clear();

    String number;
    while (std::getline(INPUT,number,','))
    {
        memory.push_back(std::stoi(number));
    }
}

// ---------------------------------------------------------------------------------------------------------------------------------

void IntcodeComputer::Run()
{
    const size_t end = memory.size();
    int instructionPointer(0);

    while (end > instructionPointer)
    {
        const int opcode = GetOpcode(instructionPointer);

        switch (opcode)
        {
            case ADD:
                Add(instructionPointer);
                break;
            case MULTIPLY:
                Multiply(instructionPointer);
                break;
            case INPUT:
            {
                const int input(0); // TODO: Work out best way to get input.
                Input(instructionPointer, input);
                break;
            }
            case OUTPUT:
                Output(instructionPointer);
                break;
            case TERMINATE:
                instructionPointer = end;
                if (isLogging)
                    std::cout << "Found opcode 99 to terminate. Stopping program and saving output.\n";
                SaveIntcodeOutput("output");
        }
    }
}

// ---------------------------------------------------------------------------------------------------------------------------------

int IntcodeComputer::GetOpcode(const int instructionPointer) const
{
	IsAddressValid(instructionPointer);
	
	const int value(memory[instructionPointer]);
	const String stringValue(std::to_string(value));
	const std::size_t digits(stringValue.size());
	const int opcode = (digits >= 2 ? std::stoi(stringValue.substr(digits - 2)) : value);

	switch (opcode)
	{
		case ADD:
		case MULTIPLY:
		case INPUT:
		case OUTPUT:
		case TERMINATE:
			break;
		default:
			throw std::invalid_argument(String(std::to_string(opcode)) + " is not a valid opcode!\n");
	}

	return opcode;
}

// ---------------------------------------------------------------------------------------------------------------------------------

void IntcodeComputer::Add(int &instructionPointer)
{
	IsAddressValid(instructionPointer);
	IsAddressValid(instructionPointer + 1);
	IsAddressValid(instructionPointer + 2);
	IsAddressValid(instructionPointer + 3);

	const int input1 = memory[instructionPointer + 1];
	const int input2 = memory[instructionPointer + 2];
	const int output = memory[instructionPointer + 3];

	memory[output] = memory[input1] + memory[input2];

	instructionPointer += 4;
}

// ---------------------------------------------------------------------------------------------------------------------------------

void IntcodeComputer::Multiply(int &instructionPointer)
{
	IsAddressValid(instructionPointer);
	IsAddressValid(instructionPointer + 1);
	IsAddressValid(instructionPointer + 2);
	IsAddressValid(instructionPointer + 3);

	const int input1 = memory[instructionPointer + 1];
	const int input2 = memory[instructionPointer + 2];
	const int output = memory[instructionPointer + 3];

	memory[output] = memory[input1] * memory[input2];

	instructionPointer += 4;
}

// ---------------------------------------------------------------------------------------------------------------------------------

void IntcodeComputer::Input(int &instructionPointer, const int input)
{
	IsAddressValid(instructionPointer);
	IsAddressValid(instructionPointer + 1);

	const int output = memory[instructionPointer + 1];

	memory[output] = input;

	instructionPointer += 2;
}

// ---------------------------------------------------------------------------------------------------------------------------------

int IntcodeComputer::Output(int &instructionPointer) const
{
	IsAddressValid(instructionPointer);
	IsAddressValid(instructionPointer + 1);

	const int output = memory[instructionPointer + 1];

	return memory[output];

	instructionPointer += 2;
}