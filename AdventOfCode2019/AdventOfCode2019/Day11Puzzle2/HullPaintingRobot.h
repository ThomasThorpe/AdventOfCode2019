/**
 *	@file	AdventOfCode2019/Day11Puzzle2/IntcodeComputer.h
 *
 *	@brief	Header file for the HullPaintingRobot class.
 */

#if (!defined HULL_PAINTING_ROBOT_H)
#define HULL_PAINTING_ROBOT_H

#include <iostream>
#include <exception>
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>

#include "AdventOfCode2019/Day2Puzzle1/IntcodeComputer.h"

using String = std::string;
using Coordinate = std::pair<int, int>;

class HullPaintingRobot
{
public:
	enum class ProcessState
	{
		NOT_INITALISED = 0,
		INITALISED = 1,
		SUSPENDED = 2,
		RUNNING = 3,
		TERMINATED = 4
	};
	/**
	*	@brief	Default constructor.
	*/
	HullPaintingRobot();

	/**
	 *	@brief	Constructor.
	 *
	 *	@param	filename the filename of the intcode program.
	 *	@param	name the name of the hull painting robot.
	 */
	HullPaintingRobot(const String &filename, const String &name = "DefaultHullPaintingRobot");

	/**
	 *	@brief	Destructor.
	 */
	~HullPaintingRobot();

	/**
	 *	@brief	Get the process state.
	 */
	ProcessState GetProcessState() const;

	/**
	 *	@brief	Reset.
	 */
	void Reset();

	/**
 *	@brief	Save robot's memory.
 *
 *	@param	filename the filename to save the memory to.
 */
	void SaveMemory(const String &filename) const;

	/**
	 *	@brief	Initialise robot's memory to the programs values.
	 *
	 *	@param	filename the filename of the intcode program.
	 */
	void ReadIntcodeProgram(const String &filename);

	/**
	 *	@brief	Save robot's outputs.
	 *
	 *	@param	filename the filename to save the outputs to.
	 */
	void SaveOuputs(const String &filename) const;

	/**
	 *	@brief	Run the robot.
	 *
	 *	@throw	std::runtime_error if the robot is not initalised.
	 */
	ProcessState Run();

private:
	enum class Direction : int
	{
		NORTH = 0,
		EAST = 1,
		SOUTH = 2,
		WEST = 3
	};

	enum class PaneColour
	{
		BLACK = 0,
		WHITE = 1
	};

	class CoordinateHash {
	public:
		size_t operator()(const Coordinate &coordinate) const;

	private:
		size_t HashCombine(size_t lhs, size_t rhs) const;
	};

	/**
	 *	@brief	Print out the registration identifier.
	 *
	 *	@param	painted	a map of the coordinates and their colour.
	 */
	void Print(const std::unordered_map<Coordinate, PaneColour, CoordinateHash>& painted) const;

	/**
	 *	@brief	Turns the robot.
	 *
	 *	@throw	std::invalid_argument if turn is not 0 or 1.
	 */
	void Turn(const int turn);

	/**
	 *	@brief	Moves the robot forward.
	 */
	void MoveFoward();

	IntcodeComputer m_brain;				///< the brain of the robot.
	ProcessState m_processState;			///< the state of the robot.
	String m_name;							///< the name of the robot.

	Coordinate m_position;					///< the position of the robot.
	Direction m_facing;						///< the facing direction of the robot.
};

// ---------------------------------------------------------------------------------------------------------------------------------

inline HullPaintingRobot::ProcessState HullPaintingRobot::GetProcessState() const
{
	return m_processState;
}

// ---------------------------------------------------------------------------------------------------------------------------------

inline void HullPaintingRobot::SaveMemory(const String &filename) const
{
	m_brain.SaveMemory(filename);
}

// ---------------------------------------------------------------------------------------------------------------------------------

inline void HullPaintingRobot::ReadIntcodeProgram(const String &filename)
{
	m_brain.ReadIntcodeProgram(filename);
	m_processState = ProcessState::INITALISED;
}

// ---------------------------------------------------------------------------------------------------------------------------------

inline void HullPaintingRobot::SaveOuputs(const String &filename) const
{
	m_brain.SaveOuputs(filename);
}

// ---------------------------------------------------------------------------------------------------------------------------------

inline size_t HullPaintingRobot::CoordinateHash::operator()(const Coordinate &coordinate) const
{
	return (HashCombine(std::hash<int>()(coordinate.first), std::hash<int>()(coordinate.second)));
}

// ---------------------------------------------------------------------------------------------------------------------------------

inline size_t HullPaintingRobot::CoordinateHash::HashCombine(size_t lhs, size_t rhs) const
{
	lhs ^= rhs + 0x9e3779b9 + (lhs << 6) + (lhs >> 2);
	return lhs;
}

#endif // (!defined HULL_PAINTING_ROBOT_H)
