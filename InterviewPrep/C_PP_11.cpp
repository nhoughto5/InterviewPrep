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

	//for (int i = 0; i < textRing.size(); ++i) {
	//	cout << textRing.get(i) << endl;
	//}

	for (string value : textRing) {
		cout << value << endl;
	}
	//for (ring<string>::iterator it = textRing.begin(); it != textRing.end(); ++it) {
	//	string t = *it;
	//	cout << t << endl;
	//}
}