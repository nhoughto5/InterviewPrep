#include "stdafx.h"
#include "Udemy.h"


Udemy::Udemy()
{
}


Udemy::~Udemy()
{
}

void Udemy::TwoDVector()
{
	//Create a 2D vector with 3 rows and 4 columns;
	std::vector<std::vector<int>> grid(3, std::vector<int>(4, 0));

	for (size_t row = 0; row < grid.size(); ++row) {
		for (size_t col = 0; col < grid[row].size(); ++col) {
			std::cout << grid[row][col] << std::flush;
		}
		std::cout << std::endl;
	}
}

void Udemy::List()
{
	std::list<int> numbers;
	numbers.push_back(1);
	numbers.push_back(2);
	numbers.push_back(3);
	numbers.push_front(0);

	std::list<int>::iterator it = numbers.begin();
	++it;
	numbers.insert(it, 100);
	std::cout << "Element: " << *it << std::endl;

	std::list<int>::iterator eraseIt = numbers.begin();
	eraseIt++;
	eraseIt = numbers.erase(eraseIt);
	std::cout << "Element: " << *eraseIt << std::endl;

	for (std::list<int>::const_iterator it = numbers.begin(); it != numbers.end(); ++it) {
		if (*it == 2) {
			numbers.insert(it, 1234);
		}
	}

	for (std::list<int>::const_iterator it = numbers.begin(); it != numbers.end(); ++it) {
		std::cout << *it << std::endl;
	}
}

void Udemy::Map()
{
	std::map<std::string, int> ages;
	ages["Mike"] = 4;
	ages["Raj"] = 20;
	ages["Vicky"] = 25;

	for (std::map<std::string, int>::iterator it = ages.begin(); it != ages.end(); ++it) {
		std::cout << it->first << ": " << it->second << std::endl;
	}
}

void Udemy::ObjectInMap()
{
	std::map<Person, int> people;

	people[Person("Mike", 40)] = 40;
	people[Person("Viki", 100)] = 41;
	people[Person("Raj", 140)] = 42;

	for (std::map<Person, int>::iterator it = people.begin(); it != people.end(); ++it) {
		it->first.print();
		std::cout << it->second << std::endl;
	}
}

void Udemy::MultiMap()
{
	std::multimap<int, std::string> lookup;

	lookup.insert(std::make_pair(30, "Mike"));
	lookup.insert(std::make_pair(10, "Steve"));
	lookup.insert(std::make_pair(30, "nick"));
	lookup.insert(std::make_pair(20, "Devon"));

	for (std::multimap<int, std::string>::iterator it = lookup.find(30); it != lookup.end(); ++it) {
		std::cout << it->first << ": " << it->second << std::endl;
	}

	std::cout << std::endl;
	auto its = lookup.equal_range(30);

	for (std::multimap<int, std::string>::iterator it = its.first; it != its.second; ++it) {
		std::cout << it->first << ": " << it->second << std::endl;
	}
}

void Udemy::Stack()
{
	std::stack<Person> testStack;
	testStack.push(Person("Mike", 45));
	testStack.push(Person("John", 48));
	testStack.push(Person("Ed", 47));
	testStack.push(Person("Steve", 46));

	Person testPerson = testStack.top();
	testPerson.print();
}

//A Friend of Person Class
bool compare(const Person& A, const Person& B) {
	return A.age < B.age;
}

void Udemy::SortVector()
{
	std::vector<Person> vector;

	vector.push_back(Person("Mike", 45));
	vector.push_back(Person("John", 48));
	vector.push_back(Person("Ed", 47));
	vector.push_back(Person("Steve", 46));

	//Uses < operator overloaded by Person
	//std::sort(vector.begin(), vector.end());

	//Uses a function pointer with a friend method.
	std::sort(vector.begin(), vector.end(), compare);

	for (Person p : vector) {
		p.print();
	}
}

void Udemy::LeftBitShiftOverload()
{
	Person Me("Nick", 28);

	std::cout << Me << std::endl;
}

void Udemy::ComplexNumber()
{
	Complex c1(3, 4.6);
	Complex c2(10, 41);

	std::cout << c1 + c2 << std::endl;
	std::cout << c1 - c2 << std::endl;
	std::cout << c1 + 7 << std::endl;
	std::cout << 7 + c1 << std::endl;
	std::cout << *c1 << std::endl;
}

void Udemy::TemplateClass()
{
	TestTemplate<std::string> test1("Hello");
	test1.print();
}

void Udemy::testTemplateMethod()
{
	templatePrint(Person("Nick", 28));
}


void test(int value) {
	std::cout << "Function pointer: " << value << std::endl;
}

void Udemy::functionPointers()
{
	//Function pointer to test.
	void (*pTest)(int) = test;

	//Calls test method
	pTest(6);
}

bool match(std::string test) {
	return test.compare("Two") == 0;
}

int countStrings(std::vector<std::string> &texts, bool (*match)(std::string test)) {
	int count = 0;
	for (std::string S : texts) {
		if (match(S)) { ++count; }
	}
	return count;
}
void Udemy::functionPointerMatch()
{
	std::vector<std::string> texts;
	texts.push_back("One");
	texts.push_back("Two");
	texts.push_back("Tree");
	texts.push_back("Plant");
	texts.push_back("Orange");
	texts.push_back("Moo");
	texts.push_back("Two");


	std::cout << countStrings(texts, match) << std::endl;
}

/*
	Slicing away a part of the child.
	When the copy constructor is run on the parent class
		we can not determine what to do with the childs
		member 'two'.
*/
void Udemy::ObjectSplitting()
{
	Child c1;
	Parent &p1 = c1;
	p1.print();

	// Known as 'Up casting'
	// Causes Object slicing
	Parent p2 = Child();
	p2.print();
}

void Udemy::AbstractClassesAndPureVirtualFunctions()
{
	Labrador lab;
	Dog dog;
	dog.speak();
	lab.run();
	lab.speak();


	//Can create pointers to animal
	Animal *animals[5];
	animals[0] = &lab;

	animals[0]->speak();
}

struct Test {
	virtual bool operator()(std::string &text) = 0;

	virtual ~Test() {}
};

// Functors overload the () operator.
struct MatchTest : public Test{
	bool operator()(std::string &text) {
		return text.compare("lion") == 0;
	}
};

void check(std::string text, Test &test) {
	if(test(text)){
		std::cout << "Text Matches\n";
	}
	else {
		std::cout << "No Match\n";
	}
}
//An alternative to function pointers
void Udemy::Functors()
{
	MatchTest pred;
	std::string value = "lion";
	check(value, pred);
}


