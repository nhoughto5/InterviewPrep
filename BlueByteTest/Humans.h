#pragma once

#include <condition_variable>
#include <mutex>
#include <vector>
#include <map>
#include "Messages.h"
#include "catch.hpp"

enum HumanState
{
	HumanState_Idle = 0,
	HumanState_Waiting,
	HumanState_Traveling,
	HumanState_Arrived
};

class Human {
public:
	Human(const unsigned int aFloor, const unsigned int	aDestinationFloor);

	unsigned int myFloor;
	unsigned int myDestinationFloor;

	HumanState GetState() const;
	void SetStateWaiting();
	void SetStateTraveling();
	void SetStateArrived();

	void Step();
	unsigned int GetWaitingCounter() const;
	unsigned int GetTravelingCounter() const;

private:
	HumanState myState;
	unsigned int myWaitingCounter;
	unsigned int myTravelingCounter;
};

class Humans {
public:
	Humans();

	void Start();
	void OnMessageElevatorReady(const MessageElevatorReady&	aMessage);
	void OnMessageElevatorArrived(const MessageElevatorArrived&	aMessage);
	void OnMessageHumanStep(const MessageHumanStep&	aMessage);

	// TODO Delete/Move when done testing
	std::vector<Human> getHumans();
	void setHumans(std::vector<Human> h);
private:
	void addNewHuman(int num);
	std::vector<Human> myHumans;
	void PrivPrintTimers();
};
