#include "stdafx.h"
#include "Parent.h"


Parent::Parent() : one(0)
{
}


Parent::Parent(const Parent & other) : one(0)
{
	std::cout << "Copy Parent\n";
	one = other.one;
}

Parent::~Parent()
{
}

void Parent::print()
{
	std::cout << "Parent\n";
}
