/**
 *  @file   AdventOfCode2019/Day2/Puzzle1/IntcodeComputer.h
 * 
 *  @brief  Header file for the IntcodeComputer class.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

typedef std::string String;
typedef std::vector<int> IntVector;

class IntcodeComputer
{
public:
    /**
     *  @brief  Constructor.
     * 
     *  @param  FILENAME the filename of the intcode program.
     */
    IntcodeComputer(const String &FILENAME);

    /**
     *  @brief  Destructor.
     */
    ~IntcodeComputer();

    /**
     *  @brief  Initialise computer's memory to the program's values.
     * 
     *  @param  FILENAME the filename of the intcode program.
     */
    void ReadIntcodeProgram(const String &FILENAME);

    /**
     *  @brief  Save intcode output.
     * 
     *  @param  FILENAME the filename to save the output to.
     */
    void SaveIntcodeOutput(const String &FILENAME) const;

    /**
     *  @brief  Run on the computer's memory.
     */
    void Run();

private:
    /**
     *  @brief  Add operation.
     * 
     *  @param  instructionPointer address of this opcode.
     */
    void Add(int &instructionPointer);

    /**
     *  @brief  Multiply operation.
     * 
     *  @param  instructionPointer address of this opcode.
     */
    void Multiply(int &instructionPointer);

    IntVector memory;    //<<< the memory of the computer.
};

// ---------------------------------------------------------------------------------------------------------------------------------

inline void IntcodeComputer::Add(int &instructionPointer)
{
    const int input1 = memory[instructionPointer+1];
    const int input2 = memory[instructionPointer+2];
    const int output = memory[instructionPointer+3];

    memory[output] = memory[input1] + memory[input2];

    instructionPointer += 4;
}

// ---------------------------------------------------------------------------------------------------------------------------------

inline void IntcodeComputer::Multiply(int &instructionPointer)
{
    const int input1 = memory[instructionPointer+1];
    const int input2 = memory[instructionPointer+2];
    const int output = memory[instructionPointer+3];

    memory[output] = memory[input1] * memory[input2];

    instructionPointer += 4;
}