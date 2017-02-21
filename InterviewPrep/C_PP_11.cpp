#include "stdafx.h"
#include "C_PP_11.h"


C_PP_11::C_PP_11()
{
}


C_PP_11::~C_PP_11()
{
}

void C_PP_11::typeId()
{
	string value;
	cout << typeid(value).name() << endl;

	//Sets name to same type as value
	decltype(value) name = "Bob";
	cout << typeid(name).name() << endl;
}

//=================== Auto Keyword ===================//

// Trailing return type, determines what type to return
template <class T, class S>
auto test(T value1, S value2) -> decltype(value1 + value2) {
	return value1 + value2;
}

int get() {
	return 999;
}
auto test2() -> decltype(get()) {
	return get();
}
void C_PP_11::Auto()
{
	auto value = 7;
	auto text = "Hello";
	cout << test(5, 7.8f) << endl;
	cout << test2() << endl;
}
//====================================================//

//=================== Nested template classes ===================//
void C_PP_11::nestedTemplateClasses()
{
	ring<string> textRing(3);
	textRing.add("one");
	textRing.add("two");
	textRing.add("three");
	textRing.add("four");

	for (string value : textRing) {
		cout << value << endl;
	}
}

/*
	Cpp 11 allows a lot more capability to
		initialize variables with {}
*/
void C_PP_11::Initialization()
{
	int value{ 5 };
	cout << value << endl;

	string valueStr{ "Nick" };
	cout << valueStr << endl;

	int* pInts = new int[3]{ 1,2,3 };
	cout << pInts[2] << endl;

	int value0{};
	cout << value0 << endl;

	int *pSomething{ &value };
	cout << *pSomething << endl;

	int *pSomething2{}; // same as nullptr
	cout << pSomething2 << endl;

	int numbers1[5]{}; //Init all values to 0
	cout << numbers1[2] << endl;

	struct {
		int value;
		string text;
	} s1{ 5, "Hi" };
	cout << s1.text << ": " << s1.value << endl;

	vector<string> strings{ "one", "two", "Bowl" };
	cout << strings[2] << endl;
}

class Test {
public:
	//Default constructor
	Test() = default;

	//Default Copy Constructor
	Test(const Test& other) = default;

	//Removes the copy constructor. Use if you don't want it copyable.
	//Test(const Test& other) = delete;

	Test(int id) : id(id) {

	}

	//Default move/copy operator
	Test &operator=(const Test &other) = default;

	Test(initializer_list<string> texts) {
		for (auto value : texts) {
			cout << value << endl;
		}
	}

	void print(initializer_list<string> texts) {
		for (auto value : texts) {
			cout << value << endl;
		}
	}

	void print2() {
		cout << id << ": " << name << endl;
	}
private:
	//Default values
	int id{ 3 };
	string name{ "Mike" };
};

void C_PP_11::InitializerList()
{
	Test test{ "apple", "orange", "banana" };

	test.print({ "one", "two" });
}

void C_PP_11::ObjectInitialization()
{
	Test test;
	test.print2();

	Test test2(77);
	test2.print2();
}

void lambdaTest(void(*pFunc)()) {
	pFunc();
}

void C_PP_11::LambdaExpressions1()
{
	auto func = []() {cout << "Hello" << endl; };
	lambdaTest(func);
	lambdaTest([]() {cout << "Hello again" << endl; });
}

void lambda2Test(void(*greet)(string)) {
	greet("Bob");
}

void runDivide(double(*div)(double a, double b)) {
	auto r = div(9, 3);
	cout << r << endl;
}
void C_PP_11::LambdaExpressions2()
{
	auto pGreet = [](string name) { cout << "Hello: " << name << endl; };
	lambda2Test(pGreet);

	// Trailing return type syntax.
	auto pDivide = [](double a, double b) -> double {
		if (b == 0) {
			return 0;
		}
		return a / b;
	};

	cout << pDivide(10.0, 5.0) << endl;
	cout << pDivide(10.0, 0.0) << endl;

	runDivide(pDivide);
}

void C_PP_11::LambdaCaptureExpressions()
{
	int one = 1;
	int two = 2;
	int three = 3;

	//Capture one and two by value
	[one, two]() {cout << one << ", " << two << endl; }();

	//Capture all local variables by value
	[=]() {cout << one << ", " << two << endl; }();

	// Capture all local variables by value but capture three by reference
	// Can change reference values.
	[=, &three]() {cout << one << ", " << two << ", " << three << endl; three = 7; }();
	cout << three << endl;

	// Capture all local variables by reference
	[&]() {cout << one << ", " << two << ", " << three << endl; one = 7; }();
	cout << one << ", " << two << ", " << three << endl;

	// Capture all local variables by reference but two and three by value
	[&, two, three]() {cout << one << ", " << two << ", " << three << endl; one = 18; }();
	cout << one << ", " << two << ", " << three << endl;
}

class LambdaCaptureThisTest {
public:
	void run() {
		int three{ 3 }, four{ 4 };

		auto pLambda = [this, three, four]() {
			cout << one << endl;
			one = 111; //This members captured by reference
			cout << two << endl;
			cout << three << endl;
			cout << four << endl;
		};
		pLambda();
		cout << one << endl;
	}

private:
	int one{ 1 }, two{ 2 };
};

void C_PP_11::LambdaCaptureThis()
{
	LambdaCaptureThisTest test;
	test.run();
}

bool check(string &test) {
	return test.size() == 3;
}

class Check {
public:
	bool operator()(string &test) {
		return test.size() == 5;
	}
} check1;

// Run accepts anything that is callable which
//	returns bool and accepts a string reference
void run(function<bool(string&)> check) {
	string test = "dog";
	cout << check(test) << endl;
}
void C_PP_11::StandardFunctionType()
{
	vector<string> vec{ "One", "Two", "Three" };
	int size = 5;

	// Lambda Expression
	auto lambda = [size](string test) {return test.size() == size; };
	cout << count_if(vec.begin(), vec.end(), lambda) << endl;

	// Function pointer
	cout << count_if(vec.begin(), vec.end(), check) << endl;

	// Functor
	cout << count_if(vec.begin(), vec.end(), check1) << endl;

	run(lambda);
	run(check);
	run(check1);

	function<int(int, int)> add = [](int one, int two) {return one + two; };
	cout << add(7, 3) << endl;
}

// Use of mutable keyword allows the ability to modify the 
// value passed in.
void C_PP_11::MutableLambdas()
{
	int cats = 5;
	auto cat = [cats]() mutable {
		cout << cats << endl;
		cats = 8;
		cout << cats << endl;
	};

	cat();
	cout << cats << endl;
}

void C_PP_11::DelegatingConstructors()
{
	class L_Parent {
	public:
		L_Parent() : L_Parent("Hello") {
			cout << "No parameter parent Constructor" << endl;
		}
		L_Parent(string text) {
			this->text = text;
			cout << "String Parent Constructor" << endl;
		}
	private:
		int dogs{ 5 };
		string text;
	};

	class L_Child : public L_Parent {
	public:
		L_Child() = default;
	private:
	};

	L_Parent parent("Hello");
	L_Child child;
}

