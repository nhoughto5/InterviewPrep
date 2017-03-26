#include "MessageBus.h"

#include "Elevators.h"

Elevators::Elevators()
{
}

void Elevators::Start()
{
	REGISTER_ELEVATOR(MessageElevatorCall, Elevators::OnMessageElevatorCall);
	REGISTER_ELEVATOR(MessageElevatorStep, Elevators::OnMessageElevatorStep);
	REGISTER_ELEVATOR(MessageElevatorRequest, Elevators::OnMessageElevatorRequest);

	myElevators.push_back(Elevator{ 1, 10, 6, Direction::Down });

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
	// TODO Implement me!
	callQueue.push_back(aMessage);
}

//Human in elevator presses desired flood button
void Elevators::OnMessageElevatorRequest(const MessageElevatorRequest& aMessage)
{
	// TODO Implement me!
	auto it = std::find_if(myElevators.begin(), myElevators.end(), [&aMessage](const Elevator& obj) {return obj.Id == aMessage.myElevatorId; });

	// TODO Multiple people?
	if (it != myElevators.end()) {
		// The SelectFloor method performs the necessary error handling
		it->SelectFloor(aMessage.myFloor);
	}
	else {
		std::cerr << "ERROR: Can not find elevator number: " << aMessage.myElevatorId << "\n";
	}
}

void Elevators::OnMessageElevatorStep(const MessageElevatorStep& aMessage)
{
	Log("[Elevators] Step");

	// Look at each OnMessageElevatorCall in the queue and assign 
	//	the nearest available elevator to service it.
	updateTargetFloors();

	for (auto& elevator : myElevators)
	{
		elevator.Step();
	}

	MessageElevatorStep message;
	SEND_TO_ELEVATORS(message);
}

bool Elevators::canService(const MessageElevatorCall& aMessage) {
	unsigned int floorPersonIsOn = aMessage.myFloor;
	Direction directionPersonWantsToGo = aMessage.myDirection;

	Elevator *tempElevator = nullptr;
	int distance = std::numeric_limits<int>::max();
	int tempDistance;
	bool elevAbove, personWantsToGoUp, elevatorGoingUp, onExtremity;
	//Choose Elevator to service call
	for (Elevator& elevator : myElevators) {

		//Only look at idle elevators
		if (elevator.HasWork()) {
			// Negative / Positive detemines direction
			tempDistance = (int)elevator.CurrentFloor() - (int)floorPersonIsOn;
			elevAbove = tempDistance > 0 ? true : false;
			personWantsToGoUp = directionPersonWantsToGo == Direction::Up ? true : false;
			elevatorGoingUp = elevator.CurrentDirection() == Direction::Up ? true : false;
			onExtremity = ((floorPersonIsOn == 1) || (floorPersonIsOn == elevator.getMyFloorCount())) ? true : false;

			/*
			( Person wants to go up'. Elevator Going Up'. Elevator Above ) +
			( Elevator Going Up'. Elevator Above . On Extremity ) +
			( Elevator Going Up . Elevator Above'. On Extremity ) +
			( Person wants to go up . Elevator Going Up . Elevator Above')
			*/
			if (floorPersonIsOn <= elevator.getMyFloorCount()) {
				if ((!personWantsToGoUp && !elevatorGoingUp && elevAbove) ||
					(!elevatorGoingUp && elevAbove && onExtremity) ||
					(elevatorGoingUp && !elevAbove && onExtremity) ||
					(personWantsToGoUp && elevatorGoingUp && !elevAbove)) {

					//Find the closest
					if (abs(tempDistance) < distance) {
						tempElevator = &elevator;
						distance = abs(tempDistance);
					}
				}
			}
		}
	}
	if (tempElevator == nullptr) {
		return false;
	}
	else {
		return true;
		tempElevator->setTargetFloor(floorPersonIsOn);
	}
	
}

void Elevators::updateTargetFloors() {
	for (std::vector<MessageElevatorCall>::const_iterator it = callQueue.begin(); it != callQueue.end(); ++it) {
		if (canService(*it)) {
			callQueue.erase(it);
		}
	}
}