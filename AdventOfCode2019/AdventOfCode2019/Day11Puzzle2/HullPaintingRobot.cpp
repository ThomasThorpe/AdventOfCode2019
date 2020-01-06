/**
 *	@file	AdventOfCode2019/Day11Puzzle2/HullPaintingRobot.cpp
 *
 *	@brief	Implementation of the HullPaintingRobot class.
 */

#include "HullPaintingRobot.h"

// ---------------------------------------------------------------------------------------------------------------------------------

HullPaintingRobot::HullPaintingRobot() :
	m_brain(),
	m_processState(ProcessState::NOT_INITALISED),
	m_name("DefaultHullPaintingRobot"),
	m_position(10,10),
	m_facing(Direction::NORTH)
{
}

// ---------------------------------------------------------------------------------------------------------------------------------

HullPaintingRobot::HullPaintingRobot(const String &filename, const String &name) :
	m_brain(filename, name + "Brain"),
	m_processState(ProcessState::INITALISED),
	m_name(name),
	m_position(10, 10),
	m_facing(Direction::NORTH)
{
}

// ---------------------------------------------------------------------------------------------------------------------------------

HullPaintingRobot::~HullPaintingRobot()
{
}

// ---------------------------------------------------------------------------------------------------------------------------------

void HullPaintingRobot::Reset()
{
	m_brain.Reset();
	m_position = { 0, 0 };
	m_facing = Direction::NORTH;
	m_processState = ProcessState::NOT_INITALISED;
}

// ---------------------------------------------------------------------------------------------------------------------------------

HullPaintingRobot::ProcessState HullPaintingRobot::Run()
{
	if (ProcessState::INITALISED != m_processState)
		throw std::runtime_error("Cannot run when computer is not initalised!\n");

	m_processState = ProcessState::RUNNING;

	int paintedOnce(0);
	std::unordered_map<Coordinate, PaneColour, CoordinateHash> seen;
	while (ProcessState::TERMINATED != m_processState)
	{
		auto search = seen.find(m_position);
		if (search == seen.end())
		{
			// Get instructions.
			if (0 == paintedOnce)
				m_brain.AppendInput(static_cast<long long int>(PaneColour::WHITE));
			else
				m_brain.AppendInput(static_cast<long long int>(PaneColour::BLACK));
			(void) m_brain.Run();
			const PaneColour toPaint = static_cast<PaneColour>(m_brain.GetOutput(m_brain.GetOutputSize() - 2));
			const int turn = static_cast<int>(m_brain.GetOutput(m_brain.GetOutputSize() - 1));

			// Execute instructions.
			seen[m_position] = toPaint;
			++paintedOnce;
			Turn(turn);
			MoveFoward();
		}
		else
		{
			// Get instructions.
			m_brain.AppendInput(static_cast<long long int>(search->second));
			(void) m_brain.Run();
			const PaneColour toPaint = static_cast<PaneColour>(m_brain.GetOutput(m_brain.GetOutputSize() - 2));
			const int turn = static_cast<int>(m_brain.GetOutput(m_brain.GetOutputSize() - 1));

			// Execute instructions.
			seen[m_position] = toPaint;
			Turn(turn);
			MoveFoward();
		}

		if (IntcodeComputer::ProcessState::TERMINATED == m_brain.GetProcessState())
			m_processState = ProcessState::TERMINATED;
	}

	std::cout << "The number of panes painted at least once was: " << paintedOnce << '\n';
	Print(seen);
}

// ---------------------------------------------------------------------------------------------------------------------------------

void HullPaintingRobot::Print(const std::unordered_map<Coordinate, PaneColour, CoordinateHash>& painted) const
{
	std::vector<std::vector<char>> toPrint(60, std::vector<char>(60));

	for (const auto &element : painted)
	{
		if (PaneColour::WHITE == element.second)
			toPrint[element.first.first][element.first.second] = '#';
	}

	for (int x = 59; x >= 0; --x)
	{
		for (int y = 0; y < 60; ++y)
		{
			if ('#' == toPrint[y][x])
				std::cout << '#';
			else
				std::cout << ' ';
		}
		std::cout << '\n';
	}
}

// ---------------------------------------------------------------------------------------------------------------------------------

void HullPaintingRobot::Turn(const int turn)
{
	if (0 == turn)
	{
		switch (m_facing)
		{
		case Direction::NORTH:
			m_facing = Direction::WEST;
			break;
		case Direction::EAST:
			m_facing = Direction::NORTH;
			break;
		case Direction::SOUTH:
			m_facing = Direction::EAST;
			break;
		case Direction::WEST:
			m_facing = Direction::SOUTH;
		}
	}
	else if (1 == turn)
	{
		switch (m_facing)
		{
		case Direction::NORTH:
			m_facing = Direction::EAST;
			break;
		case Direction::EAST:
			m_facing = Direction::SOUTH;
			break;
		case Direction::SOUTH:
			m_facing = Direction::WEST;
			break;
		case Direction::WEST:
			m_facing = Direction::NORTH;
		}
	}
	else
	{
		throw std::invalid_argument("The turn arguement must be 0 or 1\n");
	}
}

// ---------------------------------------------------------------------------------------------------------------------------------

void HullPaintingRobot::MoveFoward()
{
	const int x(m_position.first);
	const int y(m_position.second);

	switch (m_facing)
	{
	case Direction::NORTH:
		m_position = { x, y + 1 };
		break;
	case Direction::EAST:
		m_position = { x + 1, y };
		break;
	case Direction::SOUTH:
		m_position = { x, y - 1 };
		break;
	case Direction::WEST:
		m_position = { x - 1, y };
	}
}
