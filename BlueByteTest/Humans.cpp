#include "MessageBus.h"

#include "Humans.h"

Human::Human(
	const unsigned int		aFloor,
	const unsigned int		aDestinationFloor)
	: myFloor(aFloor)
	, myDestinationFloor(aDestinationFloor)
	, myState(HumanState_Idle)
	, myWaitingCounter(0)
	, myTravelingCounter(0)
{
	if (myFloor == myDestinationFloor)
	{
		Log("[Human][Error] Same floor and destination floor: ", myFloor);
		assert(false);
	}
	Log("[Human] Human created at floor ", myFloor, " going to ", myDestinationFloor);
}

HumanState Human::GetState() const {
	return myState;
}

void Human::SetStateWaiting() {
	myState = HumanState_Waiting;
}

void Human::SetStateTraveling() {
	myState = HumanState_Traveling;
}

void Human::SetStateArrived() {
	myState = HumanState_Arrived;
}

void Human::Step() {
	if (myState == HumanState_Traveling)
	{
		++myTravelingCounter;
	}
	if (myState == HumanState_Waiting)
	{
		++myWaitingCounter;
	}
}

unsigned int Human::GetWaitingCounter() const {
	return myWaitingCounter;
}

unsigned int Human::GetTravelingCounter() const {
	return myTravelingCounter;
}

///

Humans::Humans()
{
}

void Humans::Start()
{
	REGISTER_HUMAN(MessageElevatorReady, Humans::OnMessageElevatorReady);
	REGISTER_HUMAN(MessageElevatorArrived, Humans::OnMessageElevatorArrived);
	REGISTER_HUMAN(MessageHumanStep, Humans::OnMessageHumanStep);

	myHumans.push_back(Human(1, 4));
	myHumans.push_back(Human(6, 2));
	myHumans.push_back(Human(3, 8));
	myHumans.push_back(Human(9, 5));
}

void Humans::OnMessageElevatorReady(const MessageElevatorReady&	aMessage) {
	Log("[Humans] Elevator system ready");

	MessageHumanStep message;
	SEND_TO_HUMANS(message);
}

//Look at each human, any on the floor the elevator arrived to, switch state to travelling
void Humans::OnMessageElevatorArrived(const MessageElevatorArrived&	aMessage) {
	bool elevatorTaken = false;
	// TODO Implement me! - Done
	for (Human& human : myHumans) {

		// TODO Allow for more than one person to get on an elevator

		// Person is waiting in the lobby to travel
		// First person gets the elevator
		if (human.GetState() == HumanState_Waiting && human.myFloor == aMessage.myFloor && !elevatorTaken) {
			human.SetStateTraveling();
			MessageElevatorRequest m;
			m.myElevatorId = aMessage.myElevatorId;
			m.myFloor = human.myDestinationFloor;
			SEND_TO_ELEVATORS(m);
			elevatorTaken = true;
		}

		//Person has arrived at destination
		if (human.GetState() == HumanState_Traveling && human.myDestinationFloor == aMessage.myFloor) {
			// TODO should this person be removed from the myHumans list?
			human.SetStateArrived();
			Log("[Humans] Human arrived at floor ", human.myDestinationFloor, " from floor ", human.myFloor);
		}
	}
}

//TEST_CASE("Elevator Arrived") {
//	Humans humans;
//	std::vector<Human> h;
//	h.push_back(Human(1, 4));
//	h[0].SetStateWaiting();
//	h.push_back(Human(2, 3));
//	h[1].SetStateTraveling();
//	h.push_back(Human(1, 2));
//	h[2].SetStateWaiting();
//	humans.setHumans(h);
//
//	MessageElevatorArrived mHumansPickedUp, mHumanDroppedOff;
//	mHumansPickedUp.myElevatorId = 1;
//	mHumansPickedUp.myFloor = 1;
//	humans.OnMessageElevatorArrived(mHumansPickedUp);
//
//	//Test that first person on floor one got on elevator
//	REQUIRE(humans.getHumans()[0].GetState() == HumanState_Traveling);
//	//Test that second person on floor one is still waiting
//	REQUIRE(humans.getHumans()[2].GetState() == HumanState_Waiting);
//
//	mHumanDroppedOff.myElevatorId = 1;
//	mHumanDroppedOff.myFloor = 3;
//	humans.OnMessageElevatorArrived(mHumanDroppedOff);
//
//	//Test that person dropped off was able to get off elevator
//	REQUIRE(humans.getHumans()[1].GetState() == HumanState_Arrived);
//
//	mHumansPickedUp.myElevatorId = 1;
//	mHumansPickedUp.myFloor = 1;
//	humans.OnMessageElevatorArrived(mHumansPickedUp);
//	//Test that second person was able to get on the elevator
//	REQUIRE(humans.getHumans()[2].GetState() == HumanState_Traveling);
//}

void Humans::OnMessageHumanStep(const MessageHumanStep& aMessage) {
	Log("[Humans] Step");

	for (Human& human : myHumans)
	{
		human.Step();
	}

	PrivPrintTimers();

	// TODO Implement me! - Done	
	for (auto& it = myHumans.begin(); it != myHumans.end();) {
		if(it->GetState() == HumanState_Idle){
			// Call an Elevator
			MessageElevatorCall call;
			call.myDirection = (it->myDestinationFloor > it->myFloor) ? Direction::Up : Direction::Down;
			call.myFloor = it->myFloor;
			SEND_TO_ELEVATORS(call);
			it->SetStateWaiting();
		}

		// Remove humans who have completed their journey
		if (it->GetState() == HumanState_Arrived) {
			it = myHumans.erase(it);
			// TODO - Remove add human
			if (myHumans.empty()) {
				addNewHuman(1);
				it = myHumans.end();
			}

		}
		else {
			++it;
		}
	}

	MessageHumanStep message;
	SEND_TO_HUMANS(message);
}
void Humans::addNewHuman(int num) {
	srand(time(0));
	for (int i = 0; i < num; ++i) {
		unsigned int goTo = rand() % 10 + BOTTOM_FLOOR;
		unsigned int at = rand() % 10 + BOTTOM_FLOOR;
		while (goTo == at) {
			goTo = rand() % 10 + BOTTOM_FLOOR;
			at = rand() % 10 + BOTTOM_FLOOR;
		}
		myHumans.push_back(Human(at, goTo));
	}
}
void Humans::PrivPrintTimers() {
	unsigned int sumWaiting = 0;
	unsigned int sumTraveling = 0;
	unsigned int humansArrivedCounter = 0;

	for (const Human& human : myHumans)
	{
		if (human.GetState() != HumanState_Arrived)
		{
			continue;
		}

		sumWaiting += human.GetWaitingCounter();
		sumTraveling += human.GetTravelingCounter();
		++humansArrivedCounter;
	}

	if (humansArrivedCounter == 0)
	{
		return;
	}

	Log("[Stats] Average wait time (steps): ", (sumWaiting / static_cast<float>(humansArrivedCounter)));
	Log("[Stats] Average travel time (steps): ", (sumTraveling / static_cast<float>(humansArrivedCounter)));
}

std::vector<Human> Humans::getHumans() {
	return myHumans;
}
void Humans::setHumans(std::vector<Human> h) {
	myHumans = h;
}