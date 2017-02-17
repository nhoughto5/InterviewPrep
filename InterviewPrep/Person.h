#pragma once
class Person
{
public:
	//Default Constructor
	Person();

	//Copy Constructor
	Person(const Person &p);

	//Move Constructor
	Person(Person && p);

	Person(std::string name, int age);
	~Person();

	void print() const;

	bool operator<(const Person &other) const;
	bool operator>(const Person &other) const;
	bool operator==(const Person &other) const;
private:
	std::string name;
	int age;
};

