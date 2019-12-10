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
     *  @brief  Get current size of the memory.
     */
    size_t GetMemorySize() const;

    /**
     *  @brief  Write to memory.
     * 
     *  @param  address the address to write to.
     *  @param  value the value to write.
     * 
     *  @return boolean to indicate whether the write was successful.
     */
    bool Write(const int address, const int value);

    /**
     *  @brief  Read from memory.
     * 
     *  @param  address the address to read form.
     *  @param  value the value read.
     * 
     *  @return boolean to indicate whether the read was successful.
     */
    bool Read(const int address, int &value) const;

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

inline size_t IntcodeComputer::GetMemorySize() const
{
    return memory.size();
}