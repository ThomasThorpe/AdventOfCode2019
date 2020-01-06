/**
 *	@file	AdventOfCode2019/Day2Puzzle1/IntcodeComputer.h
 *
 *	@brief	Header file for the IntcodeComputer class.
 */

#if (!defined INTCODE_COMPUTER_H)
#define INTCODE_COMPUTER_H

#include <exception>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

class IntcodeComputer
{
public:
	using String = std::string;
	using IntVector = std::vector<long long int>;

	enum class ProcessState
	{
		NOT_INITALISED = 0,
		INITALISED = 1,
		SUSPENDED = 2,
		RUNNING = 3,
		TERMINATED = 4
	};

	/**
	 *	@brief	Defeault constructor.
	 */
	IntcodeComputer();

	/**
	 *	@brief	Constructor.
	 * 
	 *	@param	filename the filename of the intcode program.
	 *	@param	name the name of the computer.
	 */
	IntcodeComputer(const String &filename, const String &name = "DefaultIntcodeComputer");

	/**
	 *	@brief	Destructor.
	 */
	~IntcodeComputer();

	/**
	 *	@brief	Toggle logging.
	 */
	void ToggleLogging();

	/**
	 *	@brief	Set logging.
	 */
	void SetLogging(const bool shouldLog);

	/**
	 *	@brief	Get process state.
	 */
	ProcessState GetProcessState() const;

	/**
	 *	@brief	Reset.
	 */
	void Reset();

	/**
	 *	@brief	Append input.
	 *
	 *	@param	input the input to append.
	 */
	void AppendInput(const long long int input);

	/**
	 *	@brief	Get output.
	 *
	 *	@param	index the index of the output to get.
	 */
	long long int GetOutput(const int index) const;

	/**
	 *	@brief	Get reference to output vector.
	 */
	const IntVector &GetOutputs() const;

	/**
	 *	@brief	Get last output.
	 */
	long long int GetLastOutput() const;

	/**
	*	@brief	Get output vector size.
	*/
	size_t GetOutputSize() const;

	/**
	 *	@brief	Write to memory.
	 *
	 *	@param	address the address to write to.
	 *	@param	value the value to write.
	 *
	 *	@throw	std::out_of_range if the address is out of range.
	 */
	void Write(const int address, const long long int value);

	/**
	 *	@brief	Read from memory.
	 *
	 *	@param	address the address to read form.
	 *
	 *	@return	the value being read.
	 *
	 *	@throw	std::out_of_range if the address is out of range.
	 */
	long long int Read(const int address) const;

	/**
	 *	@brief	Save computer's memory.
	 *
	 *	@param	filename the filename to save the memory to.
	 */
	void SaveMemory(const String &filename) const;

	/**
	 *	@brief	Initialise computer's memory to the programs values.
	 *
	 *	@param	filename the filename of the intcode program.
	 */
	void ReadIntcodeProgram(const String &filename);

	/**
	 *	@brief	Save computer's outputs.
	 *
	 *	@param	filename the filename to save the outputs to.
	 */
	void SaveOuputs(const String &filename) const;

	/**
	 *	@brief	Run on the computer's memory.
	 *
	 *	@throw	std::runtime_error if the computer is not initalised.
	 */
	ProcessState Run();

private:
	enum class Opcode
	{
		ADD = 1,
		MULTIPLY = 2,
		INPUT = 3,
		OUTPUT = 4,
		JUMP_IF_TRUE = 5,
		JUMP_IF_FALSE = 6,
		LESS_THAN = 7,
		EQUALS = 8,
		RELATIVE_BASE_OFFSET = 9,
		TERMINATE = 99
	};

	enum class ParameterMode
	{
		POSITION_MODE = 0,
		IMMEDIATE_MODE = 1,
		RELATIVE_MODE = 2
	};

	/**
	 *	@brief	Checks if the address is valid.
	 *
	 *	@param	address the address.
	 *
	 *	@throw	std::out_of_range if the address is out of range.
	 */
	void IsAddressValid(const int address) const;

	/**
	*	@brief	Checks if range of addresses are valid.
	*
	*	@param	address the first address.
	*	@param	count the number of addresses.
	*
	*	@throw	std::out_of_range if any address is out of range.
	*/
	void AreAddressesValid(const int address, const int count) const;

	/**
	 *	@brief	Gets the opcode from the value of the first parameter.
	 *
	 *	@param	address the address of the first parameter.
	 *
	 *	@return the opcode.
	 *
	 *	@throw	std::invalid_argument if the opcode does not exist.
	 */
	Opcode GetOpcode(const int address) const;

	/**
	 *	@brief	Gets the parameter modes from the value of the first parameter.
	 *
	 *	@param	address the address of the first parameter.
	 *	@param	count the number of parameters excluding the first.
	 *	@param	parameterModes the parameter modes.
	 *
	 *	@throw	std::invalid_argument if the parameter mode does not exist.
	 */
	void GetParameterModes(const int address, const size_t count, std::vector<ParameterMode> &parameterModes) const;

	/**
	*	@brief	Gets the value given a parameter and it's mode.
	*
	*	@param	address the address of the parameter.
	*	@param	mode the mode of the parameter.
	*
	*	@retval	value the value.
	*
	*	@throw	std::invalid_argument if the paramter mode does not exist.
	*/
	long long int GetValue(const int address, const ParameterMode mode, const bool isOutput = false) const;

	/**
	*	@brief	Gets the values given address of the first parameter and parameter modes.
	*
	*	@param	address the address of the first parameter.
	*	@param	modes vector of parameter modes.
	*	@param	values the values.
	*/
	void GetValues(const int address, const IntVector &modes, IntVector &values) const;

	/**
	*	@brief	Gets the values given address of the first parameter and number of parameters.
	*
	*	@param	address the address of the opcode.
	*	@param	count the number of parameters.
	*	@param	values the values.
	*/
	void GetValues(const int address, const int count, IntVector &values) const;

	/**
	 *	@brief	Add operation. Takes three parameters, adds the first two and stores the result in the third.
	 *
	 *	@param	value1 the first parameter.
	 *	@param	value2 the second parameter.
	 *	@param	output the third parameter.
	 */
	void Add(const long long int value1, const long long int value2, const long long int output);

	/**
	 *	@brief	Multiply operation. Takes three paramteres, multiples the first two and stores the result in the third.
	 *
	 *	@param	value1 the first parameter.
	 *	@param	value2 the second parameter.
	 *	@param	output the third parameter.
	 */
	void Multiply(const long long int value1, const long long int value2, const long long int output);

	/**
	 *	@brief	Input operation. Takes one input and one parameter, stores input in the parameter.
	 *
	 *	@param	output the first parameter.
	 *
	 *	@throw	std::out_of_range if there is no more input to consume.
	 *
	 *	@return	boolean to indicate if should suspend.
	 */
	bool Input(const long long int output);

	/**
	 *	@brief	Output operation. Takes one parameter, outputs the value in the parameter.
	 *
	 *	@param	value the value.
	 */
	void Output(const long long int value);

	/**
	*	@brief	Jump-if-true operation. Takes two parameters, if the first parameter is non-zero, set the instruction pointer with value from the second parameter.
	*
	*	@param	instructionPointer the instructionPointer.
	*	@param	value1 the first parameter.
	*	@param	value2 the second parameter.
	*/
	void JumpIfTrue(int &instructionPointer, const long long int value1, const long long int value2);

	/**
	*	@brief	Jump-if-false operation. Takes two parameters, if the first parameter is zero, set the instruction pointer with the value from the second parameter.
	*
	*	@param	instructionPointer address of this opcode.
	*	@param	value1 the first parameter.
	*	@param	value2 the second parameter.
	*/
	void JumpIfFalse(int &instructionPointer, const long long int value1, const long long int value2);

	/**
	*	@brief	Less Than operation. Takes three parameters, if the first parameter is less than the second parameter, it stores 1 in the position given by the third parameter, else 0.
	*
	*	@param	value1 the first parameter.
	*	@param	value2 the second parameter.
	*	@param	output the third parameter.
	*/
	void LessThan(const long long int value1, const long long int value2, const long long int output);

	/**
	*	@brief	Equals operation. Takes three parameters, if the first parameter is equal to the second parameter, it stores 1 in the position given by the third parameter, else 0.
	*
	*	@param	value1 the first parameter.
	*	@param	value2 the second parameter.
	*	@param	output the third parameter.
	*/
	void Equals(const long long int value1, const long long int value2, const long long int output);

	/**
	*	@brief	Relative Base Offset operation. Takes one parameter, The value of the parameter is added to the relative base.
	*
	*	@param	valu1 the first parameter.
	*/
	void RelativeBaseOffset(const long long int value);

	ProcessState m_processState;			///< the state of the computer.
	IntVector m_memory;						///< the memory of the computer.
	IntVector m_inputs;						///< the inputs for input operations.
	IntVector m_outputs;					///< the ouputs from output operations.
	int m_inputPointer;						///< the pointer to the next input to be used. 
	int m_instructionPointer;				///< the instruction pointer.
	int m_relativeBase;						///< the relative base.

	bool m_isLogging;						///< flag to determine if logging should happen.
	String m_name;							///< the name of the computer.
};

// ---------------------------------------------------------------------------------------------------------------------------------

inline void IntcodeComputer::ToggleLogging()
{
	m_isLogging = !m_isLogging;
}

// ---------------------------------------------------------------------------------------------------------------------------------

inline void IntcodeComputer::SetLogging(const bool shouldLog)
{
	m_isLogging = shouldLog;
}

// ---------------------------------------------------------------------------------------------------------------------------------

inline IntcodeComputer::ProcessState IntcodeComputer::GetProcessState() const
{
	return m_processState;
}

// ---------------------------------------------------------------------------------------------------------------------------------

inline void IntcodeComputer::AppendInput(const long long int input)
{
	m_inputs.push_back(input);
}

// ---------------------------------------------------------------------------------------------------------------------------------

inline long long int IntcodeComputer::GetOutput(const int index) const
{
	if ((0 > index) || (m_outputs.size() <= index))
		throw std::out_of_range("The index was out of range!\n");

	return m_outputs[index];
}

// ---------------------------------------------------------------------------------------------------------------------------------

inline const IntcodeComputer::IntVector &IntcodeComputer::GetOutputs() const
{
	return m_outputs;
}

// ---------------------------------------------------------------------------------------------------------------------------------

inline long long int IntcodeComputer::GetLastOutput() const
{
	return m_outputs[m_outputs.size() - 1];
}

// ---------------------------------------------------------------------------------------------------------------------------------

inline size_t IntcodeComputer::GetOutputSize() const
{
	return m_outputs.size();
}

// ---------------------------------------------------------------------------------------------------------------------------------

inline void IntcodeComputer::Write(const int address, const long long int value)
{
	IsAddressValid(address);

	m_memory[address] = value;
}

// ---------------------------------------------------------------------------------------------------------------------------------

inline long long int IntcodeComputer::Read(const int address) const
{
	IsAddressValid(address);

	return m_memory[address];
}

// ---------------------------------------------------------------------------------------------------------------------------------

inline void IntcodeComputer::IsAddressValid(const int address) const
{
	if ((0 > address) || (m_memory.size() <= address))
		throw std::out_of_range("The address was out of range!\n");
}

// ---------------------------------------------------------------------------------------------------------------------------------

inline void IntcodeComputer::AreAddressesValid(const int address, const int count) const
{
	for (int i = 0; i < count; ++i)
	{
		IsAddressValid(address + i);
	}
}

// ---------------------------------------------------------------------------------------------------------------------------------

inline void IntcodeComputer::Add(const long long int value1, const long long int value2, const long long int output)
{
	m_memory[output] = value1 + value2;
}

// ---------------------------------------------------------------------------------------------------------------------------------

inline void IntcodeComputer::Multiply(const long long int value1, const long long int value2, const long long int output)
{
	m_memory[output] = value1 * value2;
}

// ---------------------------------------------------------------------------------------------------------------------------------

inline void IntcodeComputer::Output(const long long int value)
{
	m_outputs.push_back(value);
}

// ---------------------------------------------------------------------------------------------------------------------------------

inline void IntcodeComputer::RelativeBaseOffset(const long long int value)
{
	m_relativeBase += value;
}

#endif // (!defined INTCODE_COMPUTER_H)
