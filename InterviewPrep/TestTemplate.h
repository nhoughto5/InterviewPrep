#pragma once
#include "stdafx.h"
/*
	It is better to put implementation of a template class in a header file.
	Not good practice to interegate the input class i.e. are you this type? or do you have this method?
*/
template<class T>
class TestTemplate
{
public:
	TestTemplate(T obj) {
		this->Obj = obj;
	}
	~TestTemplate() {

	}

	void print() {
		std::cout << this->Obj << std::endl;
	}
private:
	T Obj;
};

