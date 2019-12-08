/**
 *  @file   AdventOfCode2019/Day2/Puzzle1/IntcodeComputer.cpp
 * 
 *  @brief  Implementation of the IntcodeComputer class.
 */

#include "IntcodeComputer.h"

// ---------------------------------------------------------------------------------------------------------------------------------

IntcodeComputer::IntcodeComputer(const String &FILENAME)
{
    ReadIntcodeProgram(FILENAME);
}

// ---------------------------------------------------------------------------------------------------------------------------------

IntcodeComputer::~IntcodeComputer()
{
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

void IntcodeComputer::SaveIntcodeOutput(const String &FILENAME) const
{
    std::ofstream OUTPUT(FILENAME);

    for (int number : memory)
    {
        OUTPUT << number << ',';
    }
}

// ---------------------------------------------------------------------------------------------------------------------------------

void IntcodeComputer::Run()
{
    const size_t end = memory.size();
    int instructionPointer(0);

    while (end > instructionPointer)
    {
        const int opcode = memory[instructionPointer];

        switch (opcode)
        {
            case 1:
                Add(instructionPointer);
                break;
            case 2:
                Multiply(instructionPointer);
                break;
            case 99:
                instructionPointer = end;
                std::cout << "Found opcode 99 to terminate. Stopping program.\n";
                SaveIntcodeOutput("output");
                break;
            default:
                instructionPointer = end;
                std::cout << "Invalid opcode found at position: " << opcode << '\n';
                SaveIntcodeOutput("errorOutput");
        }
    }
}