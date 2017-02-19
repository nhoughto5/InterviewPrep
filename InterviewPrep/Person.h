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
	
	//Move Assignment Operator
	const Person& operator=(const Person &other);

	~Person();

	void print() const;

	bool operator<(const Person &other) const;
	bool operator>(const Person &other) const;
	bool operator==(const Person &other) const;


	friend std::ostream &operator<<(std::ostream &out, const Person &other) {
		out << other.name << ": " << other.age;
		return out;
	}

	friend bool compare(const Person& A, const Person& B);
private:
	std::string name;
	int age;
};

