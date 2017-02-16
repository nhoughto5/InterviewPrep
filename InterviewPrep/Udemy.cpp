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

	for (int row = 0; row < grid.size(); ++row) {
		for (int col = 0; col < grid[row].size(); ++col) {
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
