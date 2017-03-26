#pragma once

#include <mutex>
#include <vector>
#include <limits>
#include <queue>
#include "Elevator.h"
#include "Messages.h"

class Elevators
{
public:
	Elevators();

	void Start();
	void OnMessageElevatorCall(const MessageElevatorCall& aMessage);
	void OnMessageElevatorRequest(const MessageElevatorRequest& aMessage);
	void OnMessageElevatorStep(const MessageElevatorStep& aMessage);

private:
	void updateTargetFloors();
	bool canService(const MessageElevatorCall& message);

	std::vector<Elevator>	myElevators;
	std::vector<MessageElevatorCall> callQueue;
};
