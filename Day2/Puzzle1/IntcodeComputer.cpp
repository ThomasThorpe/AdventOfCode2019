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

bool IntcodeComputer::Write(const int address, const int value)
{
    if ((address <= memory.size()) && (address >= 0))
    {
        memory[address] = value;
        return true;
    }
    else
    {
        return false;
    }
    
}

// ---------------------------------------------------------------------------------------------------------------------------------

bool IntcodeComputer::Read(const int address, int &value) const
{
    if ((address <= memory.size()) && (address >= 0))
    {
        value = memory[address];
        return true;
    }
    else
    {
        return false;
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

// ---------------------------------------------------------------------------------------------------------------------------------

void IntcodeComputer::Add(int &instructionPointer)
{
    const int input1 = memory[instructionPointer+1];
    const int input2 = memory[instructionPointer+2];
    const int output = memory[instructionPointer+3];

    memory[output] = memory[input1] + memory[input2];

    instructionPointer += 4;
}

// ---------------------------------------------------------------------------------------------------------------------------------

void IntcodeComputer::Multiply(int &instructionPointer)
{
    const int input1 = memory[instructionPointer+1];
    const int input2 = memory[instructionPointer+2];
    const int output = memory[instructionPointer+3];

    memory[output] = memory[input1] * memory[input2];

    instructionPointer += 4;
}