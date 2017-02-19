#pragma once
#include "stdafx.h"
class Parent
{
public:
	Parent();

	//Copy Constructor
	Parent(const Parent &other);
	virtual ~Parent();
	virtual void print();

private:
	int one;
};

