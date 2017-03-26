#pragma once

#include <string>
#include "Elevator.h"

enum Direction {
	Up = 0,
	Down
};

class MessageElevatorReady
{
};

class MessageElevatorStep
{
};

//Human sitting in the lobby presses button to call elevator
class MessageElevatorCall
{
public:
	unsigned int			myFloor;
	Direction				myDirection;
};

//Human in elevator presses desired floor button
class MessageElevatorRequest
{
public:
	unsigned int			myElevatorId;
	unsigned int			myFloor;
};

class MessageElevatorArrived
{
public:
	unsigned int			myElevatorId;
	unsigned int			myFloor;
};

class MessageHumanStep
{
};

static std::string ToString(const Direction aDirection) {
	switch (aDirection) {
	case Direction::Up:
		return "Up";
	case Direction::Down:
		return "Down";
	default:
		return "Unknown";
		break;
	}
}