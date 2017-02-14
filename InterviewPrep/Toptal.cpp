#include "stdafx.h"
#include "Toptal.h"


Toptal::Toptal()
{
}


Toptal::~Toptal()
{
}

//What will the line of code below print out and why ?
void Toptal::Q1()
{
	std::cout << "Hello World: " << 25u - 50 << std::endl;
}

/*
What is the problem in the code below? What would be an alternate way of implementing this that would avoid the problem?
	sz will never become negative as size_t is unsigned
*/
void Toptal::Q5()
{
	size_t sz = 4u;
	while (--sz >= 0) {
		std::cout << "sz: " << sz << std::endl;
	}
}

/*
Implement a template function IsDerivedFrom() that takes class C and class P as template parameters.
It should return true when class C is derived from class P and false otherwise.
*/
template <typename T> bool Toptal::IsDerivedFrom(T C, T P) {

}