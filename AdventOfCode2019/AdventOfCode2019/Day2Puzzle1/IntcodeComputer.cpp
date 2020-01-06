/**
 *	@file	AdventOfCode2019/Day2Puzzle1/IntcodeComputer.cpp
 *
 *	@brief	Implementation of the IntcodeComputer class.
 */

#include "IntcodeComputer.h"

// ---------------------------------------------------------------------------------------------------------------------------------

IntcodeComputer::IntcodeComputer() :
	m_processState(ProcessState::NOT_INITALISED),
	m_inputPointer(0),
	m_instructionPointer(0),
	m_relativeBase(0),
	m_isLogging(false),
	m_name("DefaultIntcodeComputer")
{
	m_memory.resize(65536);
	m_inputs.reserve(65536);
	m_outputs.reserve(65536);
}

// ---------------------------------------------------------------------------------------------------------------------------------

IntcodeComputer::IntcodeComputer(const String &filename, const String &name) :
	m_processState(ProcessState::NOT_INITALISED),
	m_inputPointer(0),
	m_instructionPointer(0),
	m_relativeBase(0),
	m_isLogging(false),
	m_name(name)
{
	m_memory.resize(65536);
	m_inputs.reserve(65536);
	m_outputs.reserve(65536);
	ReadIntcodeProgram(filename);
}

// ---------------------------------------------------------------------------------------------------------------------------------

IntcodeComputer::~IntcodeComputer()
{
}

// ---------------------------------------------------------------------------------------------------------------------------------

void IntcodeComputer::Reset()
{
	std::fill(m_memory.begin(), m_memory.end(), 0);
	m_inputs.clear();
	m_outputs.clear();

	m_inputPointer = 0;
	m_instructionPointer = 0;
	m_processState = ProcessState::NOT_INITALISED;
}

// ---------------------------------------------------------------------------------------------------------------------------------

void IntcodeComputer::SaveMemory(const String &filename) const
{
	std::ofstream OUTPUT(filename);

	for (long long int number : m_memory)
	{
		OUTPUT << number << ',';
	}
}

// ---------------------------------------------------------------------------------------------------------------------------------

void IntcodeComputer::ReadIntcodeProgram(const String &filename)
{
	std::ifstream INPUT(filename);
	std::fill(m_memory.begin(), m_memory.end(), 0);

	int i(0);
	String number;
	while (std::getline(INPUT,number,','))
	{
		m_memory[i] = std::stoll(number);
		++i;
	}

	m_processState = ProcessState::INITALISED;
}

// ---------------------------------------------------------------------------------------------------------------------------------

void IntcodeComputer::SaveOuputs(const String &filename) const
{
	if (0 != m_outputs.size())
	{
		std::ofstream OUTPUT(filename);

		for (long long int output : m_outputs)
		{
			OUTPUT << output << ',';
		}
	}
}

// ---------------------------------------------------------------------------------------------------------------------------------

IntcodeComputer::ProcessState IntcodeComputer::Run()
{
	if ((ProcessState::INITALISED != m_processState) && (ProcessState::SUSPENDED != m_processState))
		throw std::runtime_error("Cannot run when computer is not initalised!\n");

	m_processState = ProcessState::RUNNING;
	const size_t end = m_memory.size();

	while (end > m_instructionPointer)
	{
		const Opcode opcode = GetOpcode(m_instructionPointer);
		std::vector<ParameterMode> parameterModes;

		switch (opcode)
		{
			case Opcode::ADD:
			case Opcode::MULTIPLY:
			case Opcode::LESS_THAN:
			case Opcode::EQUALS:
			{
				AreAddressesValid(m_instructionPointer + 1, 3);
				GetParameterModes(m_instructionPointer, 3, parameterModes);
				const long long int value1 = GetValue(m_instructionPointer + 1, parameterModes[0]);
				const long long int value2 = GetValue(m_instructionPointer + 2, parameterModes[1]);
				const long long int output = GetValue(m_instructionPointer + 3, parameterModes[2], true);
				if (Opcode::ADD == opcode)
					Add(value1, value2, output);
				else if (Opcode::MULTIPLY == opcode)
					Multiply(value1, value2, output);
				else if (Opcode::LESS_THAN == opcode)
					LessThan(value1, value2, output);
				else if (Opcode::EQUALS == opcode)
					Equals(value1, value2, output);
				m_instructionPointer += 4;
				break;
			}
			case Opcode::INPUT:
			case Opcode::OUTPUT:
			case Opcode::RELATIVE_BASE_OFFSET:
			{
				IsAddressValid(m_instructionPointer + 1);
				GetParameterModes(m_instructionPointer, 1, parameterModes);
				if (Opcode::INPUT == opcode)
				{
					const int long long output = GetValue(m_instructionPointer + 1, parameterModes[0], true);
					if (Input(output))
					{
						m_processState = ProcessState::SUSPENDED;
						return m_processState;
					}
				}
				else if (Opcode::OUTPUT == opcode)
				{
					const long long int value = GetValue(m_instructionPointer + 1, parameterModes[0]);
					Output(value);
				}
				else if (Opcode::RELATIVE_BASE_OFFSET == opcode)
				{
					const long long int value = GetValue(m_instructionPointer + 1, parameterModes[0]);
					RelativeBaseOffset(value);
				}
				m_instructionPointer += 2;
				break;
			}
			case Opcode::JUMP_IF_TRUE:
			case Opcode::JUMP_IF_FALSE:
			{
				AreAddressesValid(m_instructionPointer + 1, 2);
				GetParameterModes(m_instructionPointer, 2, parameterModes);
				const long long int value1 = GetValue(m_instructionPointer + 1, parameterModes[0]);
				const long long int value2 = GetValue(m_instructionPointer + 2, parameterModes[1]);
				if (Opcode::JUMP_IF_TRUE == opcode)
					JumpIfTrue(m_instructionPointer, value1, value2);
				else if (Opcode::JUMP_IF_FALSE == opcode)
					JumpIfFalse(m_instructionPointer, value1, value2);
				// Operation will modify instruction pointer.
				break;
			}
			case Opcode::TERMINATE:
				m_instructionPointer = end;
				m_processState = ProcessState::TERMINATED;
				if (m_isLogging)
				{
					std::cout << "Found opcode 99 to terminate. Stopping program and saving memory and outputs.\n";
					SaveMemory("memory");
					SaveOuputs("outputs");
				}
				return m_processState;
		}
	}

	return m_processState;
}

// ---------------------------------------------------------------------------------------------------------------------------------

IntcodeComputer::Opcode IntcodeComputer::GetOpcode(const int address) const
{
	IsAddressValid(address);
	
	const int value(m_memory[address]);
	const String stringValue(std::to_string(value));
	const std::size_t digits(stringValue.size());

	const Opcode opcode = static_cast<Opcode>(digits < 3 ? value : std::stoi(stringValue.substr(digits - 2)));

	switch (opcode)
	{
		case Opcode::ADD:
		case Opcode::MULTIPLY:
		case Opcode::INPUT:
		case Opcode::OUTPUT:
		case Opcode::JUMP_IF_TRUE:
		case Opcode::JUMP_IF_FALSE:
		case Opcode::LESS_THAN:
		case Opcode::EQUALS:
		case Opcode::RELATIVE_BASE_OFFSET:
		case Opcode::TERMINATE:
			break;
		default:
			throw std::invalid_argument(String(static_cast<int>(opcode) + " is not a valid opcode!\n"));
	}

	return opcode;
}

// ---------------------------------------------------------------------------------------------------------------------------------

void IntcodeComputer::GetParameterModes(const int address, const size_t count, std::vector<ParameterMode> &parameterModes) const
{
	parameterModes.clear();
	parameterModes.reserve(count);
	for (int i = 0; i < parameterModes.capacity(); ++i)
	{
		parameterModes.push_back(ParameterMode::POSITION_MODE);
	}

	const int value(m_memory[address]);
	const String stringValue(std::to_string(value));
	const size_t digits(stringValue.size());

	if (digits > 2)
	{
		const String modes(stringValue.substr(0, digits - 2));
		int i(0);

		for (String::const_reverse_iterator itr = modes.rbegin(); itr != modes.rend(); ++itr)
		{
			const ParameterMode mode = static_cast<ParameterMode>((*itr) - '0');

			switch (mode)
			{
				case ParameterMode::POSITION_MODE:
				case ParameterMode::IMMEDIATE_MODE:
				case ParameterMode::RELATIVE_MODE:
					break;
				default:
					throw std::invalid_argument(String(static_cast<int>(mode) + " is not a valid parameter mode!\n"));
			}

			parameterModes[i] = mode;
			++i;
		}
	}
}

// ---------------------------------------------------------------------------------------------------------------------------------

long long int IntcodeComputer::GetValue(const int address, const ParameterMode mode, const bool isOutput) const
{
	long long int value(0);
	switch (mode)
	{
		case ParameterMode::POSITION_MODE:
			if (!isOutput)
				value = m_memory[m_memory[address]];
			else
				value = m_memory[address];
			break;
		case ParameterMode::IMMEDIATE_MODE:
			if (!isOutput)
				value = m_memory[address];
			else
				throw std::logic_error("Parameter that an instruction writes to cannot be in immediate mode!");
			break;
		case ParameterMode::RELATIVE_MODE:
			if (!isOutput)
				value = m_memory[m_memory[address] + m_relativeBase];
			else
				value = m_memory[address] + m_relativeBase;
			break;
		default:
			throw std::invalid_argument(String(static_cast<int>(mode) + " is not a valid parameter mode!\n"));
	}

	return value;
}

// ---------------------------------------------------------------------------------------------------------------------------------

void IntcodeComputer::GetValues(const int address, const IntVector &modes, IntVector &values) const
{
	// TODO. WORK OUT HOW TO MAKE FINAL PARAM BE OUTPUT VALUE
	//size_t numberOfValues(modes.size());
	//values.reserve(numberOfValues);
	//for (int i = 0; i < numberOfValues; ++i)
	//{
	//	values.push_back(GetValue(address + i, modes[i]));
	//}
}

// ---------------------------------------------------------------------------------------------------------------------------------

void IntcodeComputer::GetValues(const int address, const int count, IntVector &values) const
{
	// TODO. WORK OUT HOW TO MAKE FINAL PARAM BE OUTPUT VALUE
	//std::vector<ParameterMode parameterModes;
	//GetParameterModes(address, count, parameterModes);
	//GetValues(address + 1, parameterModes, values);
}

// ---------------------------------------------------------------------------------------------------------------------------------

bool IntcodeComputer::Input(const long long int output)
{
	if (m_inputs.size() == m_inputPointer)
	{
		if (m_isLogging)
			std::cout << m_name << " has no more input to consume. Suspending\n";
		return true;
	}
	else
	{
		m_memory[output] = m_inputs[m_inputPointer];
		++m_inputPointer;
		return false;
	}

	return false;
}

// ---------------------------------------------------------------------------------------------------------------------------------

void IntcodeComputer::JumpIfTrue(int &instructionPointer, const long long int value1, const long long int value2)
{
	if (0 != value1)
		instructionPointer = value2;
	else
		instructionPointer += 3;
}

// ---------------------------------------------------------------------------------------------------------------------------------

void IntcodeComputer::JumpIfFalse(int &instructionPointer, const long long int value1, const long long int value2)
{
	if (0 == value1)
		instructionPointer = value2;
	else
		instructionPointer += 3;
}

// ---------------------------------------------------------------------------------------------------------------------------------

void IntcodeComputer::LessThan(const long long int value1, const long long int value2, const long long  int output)
{
	if (value1 < value2)
		m_memory[output] = 1;
	else
		m_memory[output] = 0;
}

// ---------------------------------------------------------------------------------------------------------------------------------

void IntcodeComputer::Equals(const long long int value1, const long long int value2, const long long int output)
{
	if (value1 == value2)
		m_memory[output] = 1;
	else
		m_memory[output] = 0;
}
