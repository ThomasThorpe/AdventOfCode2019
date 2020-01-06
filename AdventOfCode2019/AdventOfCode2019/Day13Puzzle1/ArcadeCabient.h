/**
 *	@file	AdventOfCode2019/Day13Puzzle1/AracdeCabient.h
 *
 *	@brief	Header file for the ArcadeCabient class.
 */

#if (!defined ARCADE_CABIENT_H)
#define ARCADE_CABIENT_H

#include <string>

#include "AdventOfCode2019/Day2Puzzle1/IntcodeComputer.h"

class ArcadeCabient
{
public:
	using String = std::string;

	enum class ProcessState
	{
		NOT_INITALISED = 0,
		INITALISED = 1,
		SUSPENDED = 2,
		RUNNING = 3,
		TERMINATED = 4
	};

	/**
	 *	@biref	Default constructor.
	 */
	ArcadeCabient();

	/**
	 *	@brief	Constructor.
	 *
	 *	@param	filename the filename of the intcode program.
	 *	@param	name the name of the arcade cabient.
	 */
	ArcadeCabient(const String &filename, const String &name = "DefaultArcadeCabient");

	/**
	 *	@brief	Destructor.
	 */
	~ArcadeCabient();

	/**
	 *	@brief	Insert coins to play.
	 */
	void InsertCoins();

	/**
	 *	@brief	Get the process state.
	 */
	ProcessState GetProcessState() const;

	/**
	 *	@brief	Load game.
	 */
	void LoadGame(const String &filename);

	/**
	 *	@brief	Reset.
	 */
	void Reset();

	/**
	 *	@brief	Get the number of blocks remaining.
	 */
	int GetRemaining() const;

	/**
	 *	@brief	Run the arcade cabient.
	*
	*	@throw	std::runtime_error if the robot is not initalised.
	*/
	ProcessState Run();

private:
	/**
	 *	@brief	Get input from the player.
	 */
	void GetPlayerInput();

	/**
	 *	@brief	Get input from computer.
	 */
	void GetComputerInput();

	/**
	 *	@brief	Get x position of the paddle.
	 */
	int GetPaddleX() const;

	/**
	 *	@brief	Get x position of the ball.
	 */
	int GetBallX() const;

	/**
	 *	@brief	Print out the display and score.
	 */
	void PrintDisplay() const;

	IntcodeComputer m_processor;			///< the processor of the arcade cabient.
	ProcessState m_processState;			///< the state of the arcade cabient.
	String m_name;							///< the name of the arcade cabient.
};

// ---------------------------------------------------------------------------------------------------------------------------------

inline void ArcadeCabient::InsertCoins()
{
	m_processor.Write(0, 2);
}

// ---------------------------------------------------------------------------------------------------------------------------------

inline ArcadeCabient::ProcessState ArcadeCabient::GetProcessState() const
{
	return m_processState;
}

#endif // (!defined ARCADE_CABIENT_H)
