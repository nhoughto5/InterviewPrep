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
	// TODO Implement me! - Done
	callQueue.push_back(aMessage);
}

//Human in elevator presses desired flood button
void Elevators::OnMessageElevatorRequest(const MessageElevatorRequest& aMessage)
{
	Log("[Elevator] Request Recieved");
	// TODO Implement me! - Done
	auto it = std::find_if(myElevators.begin(), myElevators.end(), [&aMessage](const Elevator& obj) -> bool {return obj.Id() == aMessage.myElevatorId; });

	// TODO Multiple people?
	if (it != myElevators.end()) {
		// The SelectFloor method performs the necessary error handling
		it->SelectFloor(aMessage.myFloor);
	}
	else {
		std::cerr << "ERROR: Can not find elevator number: " << aMessage.myElevatorId << "\n";
	}
}

//TEST_CASE("Elevator Request") {
//	Elevators elev;
//	std::vector<Elevator>	myElevators;
//	myElevators.push_back(Elevator{ 1, 10, 1, Direction::Down });
//	elev.setElevators(myElevators);
//	MessageElevatorRequest mPass, mFailFloorOutOfBounds, mFailIDNotFound, mFailBoth;
//	mPass.myElevatorId = 1;
//	mPass.myFloor = 9;
//
//	mFailFloorOutOfBounds.myElevatorId = 1;
//	mFailFloorOutOfBounds.myFloor = 11;
//
//	mFailIDNotFound.myElevatorId = 2;
//	mFailIDNotFound.myFloor = 7;
//
//	mFailBoth.myElevatorId = 2;
//	mFailBoth.myFloor = 11;
//
//	elev.OnMessageElevatorRequest(mPass);
//	REQUIRE(elev.getElevators()[0].getTargetFloor() == 9);
//
//	elev.OnMessageElevatorRequest(mFailFloorOutOfBounds);
//	REQUIRE(elev.getElevators()[0].getTargetFloor() != 7);
//
//	elev.OnMessageElevatorRequest(mFailIDNotFound);
//	REQUIRE(elev.getElevators()[0].getTargetFloor() != 11);
//
//	elev.OnMessageElevatorRequest(mFailBoth);
//	REQUIRE(elev.getElevators()[0].getTargetFloor() != 11);
//
//}
void Elevators::OnMessageElevatorStep(const MessageElevatorStep& aMessage)
{
	Log("[Elevators] Step");

	// Look at each OnMessageElevatorCall in the queue and assign 
	//	the nearest available elevator to service it.
	ServiceElevatorCalls();

	for (auto& elevator : myElevators)
	{
		elevator.Step();
	}

	MessageElevatorStep message;
	SEND_TO_ELEVATORS(message);
}

//TEST_CASE("Elevator Step") {
//	Elevators elev;
//	std::vector<Elevator>	myElevators;
//	myElevators.push_back(Elevator{ 1, 10, 6, Direction::Down });
//	elev.setElevators(myElevators);
//	MessageElevatorCall mTrue1, mFalse1, mFalse2;
//	mTrue1.myDirection = Direction::Up;
//	mTrue1.myFloor = 1;
//	mFalse1.myDirection = Direction::Down;
//	mFalse1.myFloor = 7;
//	mFalse2.myDirection = Direction::Up;
//	mFalse2.myFloor = 7;
//	MessageElevatorStep step;
//	REQUIRE(elev.canService(mTrue1) == true);
//	REQUIRE(elev.getElevators()[0].CurrentFloor() == 6);
//	elev.OnMessageElevatorStep(step); //5
//	REQUIRE(elev.getElevators()[0].CurrentFloor() == 5);
//	elev.OnMessageElevatorStep(step); //4
//	elev.OnMessageElevatorStep(step); //3
//	elev.OnMessageElevatorStep(step); //2
//	elev.OnMessageElevatorStep(step); //1
//	REQUIRE(elev.getElevators()[0].HasWork() == false);
//}


bool Elevators::canService(const MessageElevatorCall& aMessage) {
	unsigned int floorPersonIsOn = aMessage.myFloor;
	Direction directionPersonWantsToGo = aMessage.myDirection;

	Elevator *tempElevator = nullptr;
	int distance = std::numeric_limits<int>::max();
	int tempDistance;
	unsigned int tempElevID = 0;
	bool elevAbove, personWantsToGoUp, elevatorGoingUp, onExtremity;
	//Choose Elevator to service call
	for (Elevator& elevator : myElevators) {

		if (!elevator.HasWork()) {
			tempDistance = (int)elevator.CurrentFloor() - (int)floorPersonIsOn;
			//Find the closest
			if (abs(tempDistance) < distance) {
				tempElevator = &elevator;
				distance = abs(tempDistance);
				if (distance == 0) {
					tempElevID = elevator.Id();
				}
			}

			////Only look at idle elevators
			//if (elevator.HasWork()) {
			//	// Negative / Positive detemines direction
			//	tempDistance = (int)elevator.CurrentFloor() - (int)floorPersonIsOn;
			//	elevAbove = tempDistance > 0 ? true : false;
			//	personWantsToGoUp = directionPersonWantsToGo == Direction::Up ? true : false;
			//	elevatorGoingUp = ((int)elevator.getTargetFloor() - (int)elevator.CurrentFloor() > 0) ? true : false;
			//	onExtremity = ((floorPersonIsOn == BOTTOM_FLOOR) || (floorPersonIsOn == elevator.getMyFloorCount())) ? true : false;

			//	/*
			//	( Person wants to go up'. Elevator Going Up'. Elevator Above ) +
			//	( Elevator Going Up'. Elevator Above . On Extremity ) +
			//	( Elevator Going Up . Elevator Above'. On Extremity ) +
			//	( Person wants to go up . Elevator Going Up . Elevator Above')
			//	*/
			//	if (floorPersonIsOn <= elevator.getMyFloorCount()) {
			//		if ((!personWantsToGoUp && !elevatorGoingUp && elevAbove) ||
			//			(!elevatorGoingUp && elevAbove && onExtremity) ||
			//			(elevatorGoingUp && !elevAbove && onExtremity) ||
			//			(personWantsToGoUp && elevatorGoingUp && !elevAbove)) {

			//			//Find the closest
			//			if (abs(tempDistance) < distance) {
			//				tempElevator = &elevator;
			//				distance = abs(tempDistance);
			//				if (distance == 0) {
			//					tempElevID = elevator.Id();
			//				}
			//			}
			//		}
			//	}
			//}
			//else {
			//	tempDistance = (int)elevator.CurrentFloor() - (int)floorPersonIsOn;
			//	//Find the closest
			//	if (abs(tempDistance) < distance) {
			//		tempElevator = &elevator;
			//		distance = abs(tempDistance);
			//		if (distance == 0) {
			//			tempElevID = elevator.Id();
			//		}
			//	}
		}
	}
	if (tempElevator == nullptr) {
		return false;
	}
	else {
		//This elevator is already at the human's location
		if (distance == 0) {
			MessageElevatorArrived m;
			m.myElevatorId = tempElevID;
			m.myFloor = floorPersonIsOn;
			SEND_TO_HUMANS(m)
		}
		tempElevator->setTargetFloor(floorPersonIsOn);
		tempElevator->setOnCall(true);
		return true;
	}

}
// TODO Add More test cases
//TEST_CASE("Can Service") {
//	Elevators elev;
//	std::vector<Elevator>	myElevators;
//
//	// Test idle elevators
//	myElevators.push_back(Elevator{ 1, 10, 6, Direction::Down });
//	elev.setElevators(myElevators);
//	MessageElevatorCall mTrue1, mTrue2, mTrue3;
//	mTrue1.myDirection = Direction::Up;
//	mTrue1.myFloor = 1;
//	mTrue2.myDirection = Direction::Down;
//	mTrue2.myFloor = 7;
//	mTrue3.myDirection = Direction::Up;
//	mTrue3.myFloor = 7;
//
//	REQUIRE(elev.canService(mTrue1) == true);
//	myElevators.clear();
//	elev.setElevators(myElevators);
//	myElevators.push_back(Elevator{ 1, 10, 6, Direction::Down });
//	elev.setElevators(myElevators);
//	REQUIRE(elev.canService(mTrue2) == true);
//	myElevators.clear();
//	elev.setElevators(myElevators);
//	myElevators.push_back(Elevator{ 1, 10, 6, Direction::Down });
//	elev.setElevators(myElevators);
//	REQUIRE(elev.canService(mTrue3) == true);
//
//	myElevators.clear();
//	elev.setElevators(myElevators);
//
//
//	// Test Moving Elevators
//	Elevator movingElev(1, 10, 1, Direction::Down);
//	movingElev.setTargetFloor(10);
//	myElevators.push_back(movingElev);
//	elev.setElevators(myElevators);
//
//	MessageElevatorCall mTrue4, mFalse1;
//
//	mTrue4.myDirection = Direction::Up;
//	mTrue4.myFloor = 4;
//	mFalse1.myDirection == Direction::Down;
//	mFalse1.myFloor = 4;
//	REQUIRE(elev.canService(mTrue4) == true);
//	REQUIRE(elev.canService(mFalse1) == false);
//}
void Elevators::ServiceElevatorCalls() {
	for (std::vector<MessageElevatorCall>::const_iterator it = callQueue.begin(); it != callQueue.end();) {
		if (canService(*it)) {
			std::string tem = it->myDirection ? "down" : "up";
			Log("[Elevator] Elevator received call to floor", it->myFloor, ", passenger wants to go", tem);
			it = callQueue.erase(it);
		}
		else {
			++it;
		}
	}
}

void Elevators::setElevators(std::vector<Elevator> el) {
	this->myElevators = el;
}

std::vector<Elevator> Elevators::getElevators()
{
	return myElevators;
}

