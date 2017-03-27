#include "Elevator.h"
#include "MessageBus.h"

#include "Elevators.h"

Elevator::Elevator(
	const unsigned int			aId,
	const unsigned int			aFloorCount)
	: myId(aId)
	, myFloorCount(aFloorCount)
	, myCurrentFloor(1)
	, myCurrentDirection(Direction::Up)
	, targetFloor(1)
	, onCall(false)
	, onRequest(false)
{
	Log("[Elevator]", myId, "Created", ToString());
}

Elevator::Elevator(
	const unsigned int		aId,
	const unsigned int		aFloorCount,
	const unsigned int		aCurrentFloor,
	const Direction			aDirection)
	: myId(aId)
	, myFloorCount(aFloorCount)
	, myCurrentFloor(aCurrentFloor)
	, myCurrentDirection(aDirection)
	, targetFloor(aCurrentFloor)
	, onCall(false)
	, onRequest(false)
{
	Log("[Elevator]", myId, "Created", ToString());
}

void Elevator::SelectFloor(const unsigned int aFloorId) {
	// TODO Implement me! - Done
	if (aFloorId <= myFloorCount && aFloorId >= BOTTOM_FLOOR) {
		targetFloor = aFloorId;
		myCurrentDirection = aFloorId > myCurrentFloor ? Direction::Up : Direction::Down;
	}
	else {
		std::cerr << "ERROR: ElevatorId " << myId <<
			" was requested on floor " << aFloorId <<
			". Max reachable floor: " << myFloorCount << "\n";
		Log("[Elevator] Floor ", aFloorId, " is not a valid flood for elevator number ", myId);
	}
}

unsigned int Elevator::CurrentFloor() const {
	return myCurrentFloor;
}

Direction Elevator::CurrentDirection() const {
	return myCurrentDirection;
}

bool Elevator::HasWork() const
{
	// TODO Implement me! - Done

	// TODO Check that this logic is correct
	if (onCall || onRequest) {
		return true;
	}
	else {
		return false;
	}

}

void Elevator::Step()
{
	// TODO Implement me! - Done

	// TODO Optimize these if statements
	if (!HasWork()) {
		return;
	}
	if (myCurrentDirection == Direction::Up && myCurrentFloor < myFloorCount) {
		if (myCurrentFloor < targetFloor) {
			++myCurrentFloor;
			if (myCurrentFloor == targetFloor) {
				MessageElevatorArrived m;
				m.myElevatorId = myId;
				m.myFloor = targetFloor;
				m.floorCount = myFloorCount;
				SEND_TO_HUMANS(m);
				Log("[Elevator] Elevator", myId, "Arrived at target floor ", targetFloor);
				if (onCall && !onRequest) {
					onRequest = true;
				}
				else if (onCall && onRequest) {
					Log("[Elevator] Elevator", myId, "Reset");
					onCall = onRequest = false;
				}
				else {

				}
			}
		}
	}
	if (myCurrentDirection == Direction::Down && myCurrentFloor > BOTTOM_FLOOR) {
		if (myCurrentFloor > targetFloor) {
			--myCurrentFloor;
			if (myCurrentFloor == targetFloor) {
				MessageElevatorArrived m;
				m.myElevatorId = myId;
				m.myFloor = targetFloor;
				m.floorCount = myFloorCount;
				SEND_TO_HUMANS(m);
				Log("[Elevator] Elevator", myId, "Arrived at target floor ", targetFloor);
				if (onCall && !onRequest) {
					onRequest = true;
				}
				else if (onCall && onRequest) {
					Log("[Elevator] Elevator", myId, "Reset");
					onCall = onRequest = false;
				}
				else {

				}
			}
		}
	}
}

unsigned int Elevator::Id() const
{
	return myId;
}

std::string Elevator::ToString() const
{
	return "- State: "
		+ std::to_string(myCurrentFloor)
		+ "/"
		+ std::to_string(myFloorCount)
		+ " "
		+ ::ToString(myCurrentDirection);
}

unsigned int Elevator::getTargetFloor()
{
	return targetFloor;
}

void Elevator::setTargetFloor(unsigned int t)
{
	targetFloor = t;
	myCurrentDirection = ((int)targetFloor - (int)myCurrentFloor > 0) ? Direction::Up : Direction::Down;
}

unsigned int Elevator::getMyFloorCount() const
{
	return myFloorCount;
}
void Elevator::setOnCall(bool i) {
	onCall = i;
}
bool Elevator::getOnCall() {
	return onCall;
}

void Elevator::setOnRequest(bool i)
{
	onRequest = i;
}

bool Elevator::getOnRequest()
{
	return onRequest;
}
