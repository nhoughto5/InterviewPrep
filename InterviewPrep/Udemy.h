#pragma once
#include "Person.h"
class Udemy
{
public:
	Udemy();
	~Udemy();

	void TwoDVector();
	void List();
	void Map();

	void ObjectInMap();
	void MultiMap();

	void Stack();

	void SortVector();

	void LeftBitShiftOverload();

	void ComplexNumber();

	void TemplateClass();

	template<class T> void templatePrint(T n);

	void testTemplateMethod();

	void functionPointers();

	void functionPointerMatch();

	void ObjectSplitting();

	void AbstractClassesAndPureVirtualFunctions();

	void Functors();
};

// Again, better to do template definitions in header files.
// Can use typename or class. Both work for either a class or a primitive type.
template<class T>
inline void Udemy::templatePrint(T n)
{
	n.print();
}
