#include "MessageBus.h"

#include "Elevators.h"

Elevators::Elevators()
{
}

void Elevators::Start()
{
	REGISTER_ELEVATOR(MessageElevatorCall,			Elevators::OnMessageElevatorCall);
	REGISTER_ELEVATOR(MessageElevatorStep,			Elevators::OnMessageElevatorStep);
	REGISTER_ELEVATOR(MessageElevatorRequest,		Elevators::OnMessageElevatorRequest);

	myElevators.push_back(Elevator{1, 10, 6, Direction::Down});

	{
		MessageElevatorStep message;
		SEND_TO_ELEVATORS(message);
	}

	{
		MessageElevatorReady message;
		SEND_TO_HUMANS(message);
	}
}

//Human sitting in the lobby presses button to call elevator
void Elevators::OnMessageElevatorCall(const MessageElevatorCall& aMessage)
{
	// Implement me!
	unsigned int floorPersonIsOn = aMessage.myFloor;
	Direction directionPersonWantsToGo = aMessage.myDirection;

	Elevator *tempElevator;
	int distance = std::numeric_limits<int>::max();

	//Choose Elevator to service call
	for (Elevator& elevator : myElevators) {
		// TODO Fix unsigned int subtraction
		if (abs((int)elevator.CurrentFloor() - (int)floorPersonIsOn) < distance) {
			if (directionPersonWantsToGo == elevator.CurrentDirection()) {
				tempElevator = &elevator;
			}
		}
	}
	tempElevator->setTargetFloor(floorPersonIsOn);
}

//Human in elevator presses desired flood button
void Elevators::OnMessageElevatorRequest(const MessageElevatorRequest& aMessage)
{
	// Implement me!
	int x = 4;
	++x;
}

void Elevators::OnMessageElevatorStep(const MessageElevatorStep& aMessage)
{
	Log("[Elevators] Step");

	for (auto& elevator : myElevators)
	{
		elevator.Step();
	}

	MessageElevatorStep message;
	SEND_TO_ELEVATORS(message);
}