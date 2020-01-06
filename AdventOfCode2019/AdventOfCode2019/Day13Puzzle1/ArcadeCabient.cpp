/**
 *	@file	AdventOfCode2019/Day13Puzzle1/ArcadeCabient.cpp
 *
 *	@brief	Implementation of the ArcadeCabient class.
 */

#include "ArcadeCabient.h"

// ---------------------------------------------------------------------------------------------------------------------------------

ArcadeCabient::ArcadeCabient() :
	m_processor(),
	m_processState(ProcessState::NOT_INITALISED),
	m_name("DefaultArcadeCabient")
{
}

// ---------------------------------------------------------------------------------------------------------------------------------

ArcadeCabient::ArcadeCabient(const String &filename, const String &name) :
	m_processor(filename, name + "Processor"),
	m_processState(ProcessState::INITALISED),
	m_name(name)
{
}

// ---------------------------------------------------------------------------------------------------------------------------------

ArcadeCabient::~ArcadeCabient()
{
}

// ---------------------------------------------------------------------------------------------------------------------------------

void ArcadeCabient::LoadGame(const String &filename)
{
	m_processor.Reset();
	m_processor.ReadIntcodeProgram(filename);
	m_processState = ProcessState::INITALISED;
}

// ---------------------------------------------------------------------------------------------------------------------------------

void ArcadeCabient::Reset()
{
	m_processor.Reset();
	m_processState = ProcessState::NOT_INITALISED;
}

// ---------------------------------------------------------------------------------------------------------------------------------

int ArcadeCabient::GetRemaining() const
{
	const std::vector<long long int> outputs = m_processor.GetOutputs();

	std::vector<std::vector<char>> currentDisplay(25, std::vector<char>(42));

	for (size_t i = 0; i < outputs.size(); i += 3)
	{
		if ((-1 == outputs[i]) && (0 == outputs[i + 1]))
		{
			continue;
		}
		else
		{
			if (0 == outputs[i + 2])
				currentDisplay[outputs[i + 1]][outputs[i]] = ' ';
			else if (1 == outputs[i + 2])
				currentDisplay[outputs[i + 1]][outputs[i]] = '@';
			else if (2 == outputs[i + 2])
				currentDisplay[outputs[i + 1]][outputs[i]] = '#';
			else if (3 == outputs[i + 2])
				currentDisplay[outputs[i + 1]][outputs[i]] = '=';
			else if (4 == outputs[i + 2])
				currentDisplay[outputs[i + 1]][outputs[i]] = 'O';
		}
	}

	int blocks(0);
	for (int x = 0; x < 25; ++x)
	{
		for (int y = 0; y < 42; ++y)
		{
			if ('#' == currentDisplay[x][y])
				++blocks;
		}
	}
	
	return blocks;
}

// ---------------------------------------------------------------------------------------------------------------------------------

ArcadeCabient::ProcessState ArcadeCabient::Run()
{
	if ((ProcessState::INITALISED != m_processState) && (ProcessState::SUSPENDED != m_processState))
		throw std::runtime_error("Cannot run when arcade cabient is not initalised!\n");

	m_processState = ProcessState::RUNNING;

	int counter(0);
	do
	{
		(void)m_processor.Run();
		
		if (0 == counter % 100)
			PrintDisplay();

		GetComputerInput();

		if (IntcodeComputer::ProcessState::TERMINATED == m_processor.GetProcessState())
			m_processState = ProcessState::TERMINATED;
		
		++counter;
	}
	while (ProcessState::TERMINATED != m_processState);

	std::cout << "The number of blocks remaining was: " << GetRemaining() << '\n';
	PrintDisplay();

	return m_processState;
}

// ---------------------------------------------------------------------------------------------------------------------------------

void ArcadeCabient::GetPlayerInput()
{
	String input;
	do
	{
		std::cout << "Please enter -1, 0, or 1 to move the paddle: ";
		std::getline(std::cin, input);
	} while (("-1" != input) && ("0" != input) && ("1" != input));

	m_processor.AppendInput(std::stoll(input));
}

// ---------------------------------------------------------------------------------------------------------------------------------

void ArcadeCabient::GetComputerInput()
{
	const int paddleX = GetPaddleX();
	const int ballX = GetBallX();

	if (ballX > paddleX)
		m_processor.AppendInput(1);
	else if (ballX < paddleX)
		m_processor.AppendInput(-1);
	else
		m_processor.AppendInput(0);
}

// ---------------------------------------------------------------------------------------------------------------------------------

int ArcadeCabient::GetPaddleX() const
{
	const std::vector<long long int> outputs = m_processor.GetOutputs();

	int paddleX;
	for (size_t i = 0; i < outputs.size(); i += 3)
	{
		if (3 == outputs[i + 2])
			paddleX = outputs[i];
	}

	return paddleX;
}

// ---------------------------------------------------------------------------------------------------------------------------------

int ArcadeCabient::GetBallX() const
{
	const std::vector<long long int> outputs = m_processor.GetOutputs();

	int ballX;
	for (size_t i = 0; i < outputs.size(); i += 3)
	{
		if (4 == outputs[i + 2])
			ballX = outputs[i];
	}

	return ballX;
}

// ---------------------------------------------------------------------------------------------------------------------------------

void ArcadeCabient::PrintDisplay() const
{
	const std::vector<long long int> outputs = m_processor.GetOutputs();

	std::vector<std::vector<char>> toPrint(25, std::vector<char>(42));
	int score(0);

	for (size_t i = 0; i < outputs.size(); i += 3)
	{
		if ((-1 == outputs[i]) && (0 == outputs[i + 1]))
		{
			score = outputs[i + 2];
		}
		else
		{
			if (0 == outputs[i + 2])
				toPrint[outputs[i + 1]][outputs[i]] = ' ';
			else if (1 == outputs[i + 2])
				toPrint[outputs[i + 1]][outputs[i]] = '@';
			else if (2 == outputs[i + 2])
				toPrint[outputs[i + 1]][outputs[i]] = '#';
			else if (3 == outputs[i + 2])
				toPrint[outputs[i + 1]][outputs[i]] = '=';
			else if (4 == outputs[i + 2])
				toPrint[outputs[i + 1]][outputs[i]] = 'O';
		}
	}

	std::cout << "Score: " << score << '\n';
	for (int x = 0; x < 25; ++x)
	{
		for (int y = 0; y < 42; ++y)
		{
			std::cout << toPrint[x][y];
		}
		std::cout << '\n';
	}
}
