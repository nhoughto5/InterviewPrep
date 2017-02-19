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

	int value0{  };
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

