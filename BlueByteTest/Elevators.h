#pragma once
 
#include <mutex>
#include <vector>
#include <limits>
#include <queue>
#include "Elevator.h"
#include "Messages.h"
#include "catch.hpp"

class Elevators
{
public:
	Elevators();

	void Start();
	void OnMessageElevatorCall(const MessageElevatorCall& aMessage);
	void OnMessageElevatorRequest(const MessageElevatorRequest& aMessage);
	void OnMessageElevatorStep(const MessageElevatorStep& aMessage);

	// TODO delete these methods when testing done 
	void setElevators(std::vector<Elevator> el);
	std::vector<Elevator> getElevators();
	//===============//

	// TODO move back to private
	bool canService(const MessageElevatorCall& message);
private:
	void ServiceElevatorCalls();
	

	std::vector<Elevator>	myElevators;
	std::vector<MessageElevatorCall> callQueue;
};
