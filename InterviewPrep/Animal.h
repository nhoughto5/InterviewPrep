/*
	Inclusion of a pure virtual function 
	makes this and abstract class.
*/

#pragma once
#include "stdafx.h"
class Animal
{
public:
	// Pure virtual Methods
	virtual void speak() = 0;
	virtual void run() = 0;
};

