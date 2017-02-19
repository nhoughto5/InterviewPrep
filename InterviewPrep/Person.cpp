#include "stdafx.h"
#include "Person.h"


Person::Person() :
	name(""),
	age(0)
{
}

//Copy Constructor
Person::Person(const Person & p)
{
	std::cout << "Copy Constructor\n";
	name = p.name;
	age = p.age;
}

//Move Constructor
Person::Person(Person && p)
{
	name = p.name;
	age = p.age;
}

Person::Person(std::string name_, int age_) :
	name(name_),
	age(age_)
{
}

//Move Assignment Operator
const Person & Person::operator=(const Person &other)
{
	age = other.age;
	name = other.name;
	return *this;
}

Person::~Person()
{
}

void Person::print() const {
	std::cout << name << ": " << age << std::endl;
}

bool Person::operator<(const Person & other) const
{
	return age < other.age;
}

bool Person::operator>(const Person & other) const
{
	return age > other.age;
}

bool Person::operator==(const Person & other) const
{
	return (name.compare(other.name) == 0) && (age == other.age);
}

