#pragma once

#include "Messages.h"
#include "Utils.h"
#include <cassert>
#include <iostream>
#include <map>
#include <string>

enum Direction;

class Elevator {
public:
	Elevator(const unsigned int aId, const unsigned int	aFloorCount);
	Elevator(const unsigned int aId, const unsigned int	aFloorCount, const unsigned int	aCurrentFloor, const Direction aDirection);

	void SelectFloor(const unsigned int	aFloorId);
	unsigned int CurrentFloor() const;
	Direction CurrentDirection() const;
	bool HasWork() const;

	void Step();
	unsigned int Id() const;
	std::string ToString() const;

	unsigned int getTargetFloor();
	void setTargetFloor(unsigned int t);

	unsigned int getMyFloorCount();

	// TODO - Try to not need this boolean
	void setOnCall(bool i);
	bool getOnCall();
private:
	unsigned int myId;
	unsigned int myFloorCount;
	unsigned int myCurrentFloor;
	unsigned int targetFloor;
	Direction myCurrentDirection;
	bool onCall, onRequest;
};
