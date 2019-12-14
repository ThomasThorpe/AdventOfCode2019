/**
 *  @file   AdventOfCode2019/Day2/Puzzle1/IntcodeComputer.h
 * 
 *  @brief  Header file for the IntcodeComputer class.
 */

#if (!defined INTCODE_COMPUTER_H)
#define INTCODE_COMPUTER_H

#include <exception>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using String = std::string;
using IntVector = std::vector<int>;

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
     *  @brief  Toggle logging.
     */
    void ToggleLogging();

    /**
     *  @brief  Write to memory.
     * 
     *  @param  address the address to write to.
     *  @param  value the value to write.
     * 
     *  @throw  std::out_of_range if the address is out of range.
     */
    void Write(const int address, const int value);

    /**
     *  @brief  Read from memory.
     * 
     *  @param  address the address to read form.
     * 
     *  @return the value being read.
     * 
     *  @throw std::out_of_range if the address is out of range.
     */
    int Read(const int address) const;

    /**
     *  @brief  Save intcode output.
     * 
     *  @param  FILENAME the filename to save the output to.
     */
    void SaveIntcodeOutput(const String &FILENAME) const;

    /**
     *  @brief  Initialise computer's memory to the program's values.
     * 
     *  @param  FILENAME the filename of the intcode program.
     */
    void ReadIntcodeProgram(const String &FILENAME);

    /**
     *  @brief  Run on the computer's memory.
     */
    void Run();

private:
    enum Opcodes
    {
        ADD = 1,
        MULTIPLY = 2,
        INPUT = 3,
        OUTPUT = 4,
        TERMINATE = 99
    };

    enum ParameterModes
    {
        POSITION_MODE = 0,
        IMMEDIATE_MODE = 1
    };

    /**
     *  @brief  Checks if the address is valid.
     * 
     *  @param  address the address.
     * 
     *  @throw  std::out_of_range if the address is out of range.
     */
    void IsAddressValid(const int address) const;

    /**
     *  @brief  Gets the opcode from the value of the first parameter.
     * 
     *  @param  instructionPointer address of the opcode.
     * 
     *  @return the opcode.
     * 
     *  @throw  std::out_of_range if the opcode does not exist.
     */
    int GetOpcode(const int instructionPointer) const;

    /**
     *  @brief  Add operation. Takes three parameters, adds the first two and stores the result in the third.
     * 
     *  @param  instructionPointer address of this opcode.
     */
    void Add(int &instructionPointer);

    /**
     *  @brief  Multiply operation. Takes three paramteres, multiples the first two and stores the result in the third.
     * 
     *  @param  instructionPointer address of this opcode.
     */
    void Multiply(int &instructionPointer);

    /**
     *  @brief  Input operation. Takes one input and one parameter, stores input in the parameter.
     * 
     *  @param  instructionPointer address of this opcode.
     *  @param  input the input.
     */
    void Input(int &instructionPointer, const int input);

    /**
     *  @brief  Output operation. Takes one parameter, outputs the value in the parameter.
     * 
     *  @param  instructionPointer address of this opcode.
     * 
     *  @return the value stored at the address of the parameter.
     */
    int Output(int &instructionPointer) const ;

    IntVector memory;       ///< the memory of the computer.
    bool isLogging;  ///< flag to determine if logging should happen.
};

// ---------------------------------------------------------------------------------------------------------------------------------

inline void IntcodeComputer::Write(const int address, const int value)
{
    IsAddressValid(address);

    memory[address] = value;
}

// ---------------------------------------------------------------------------------------------------------------------------------

inline int IntcodeComputer::Read(const int address) const
{
    IsAddressValid(address);

    return memory[address];
}

// ---------------------------------------------------------------------------------------------------------------------------------

inline void IntcodeComputer::IsAddressValid(const int address) const
{
	if ((0 > address) || (memory.size() <= address))
		throw std::out_of_range("The address was out of range!\n");
}

#endif // (!defined INTCODE_COMPUTER_H)