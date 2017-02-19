/*
	Instantiates the abstract class 'Animal'.
	It must implement all pure virtual methods.
*/

#pragma once
#include "stdafx.h"
class Dog : public Animal
{
public:
	Dog();
	~Dog();

	virtual void speak();
};

