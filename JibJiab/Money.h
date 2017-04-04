#pragma once

#include <iomanip> // setprecision


class Money
{
public:
	Money();

	// Explicit prevents implicit construction, avoids hard to find bugs
	explicit Money(float value);

	// Copy Constructor
	Money(const Money& other);

	// Move Constructor, no except b/c this constructor
	// will never throw an error
	Money(Money&& other) noexcept;

	// Copy Assignment operator
	Money& operator=(const Money& other);

	// Move Assignment operator, no except b/c this operator
	// will never throw an error
	Money& operator=(Money&& other) noexcept;


    //Operators
	Money& operator+=(const Money& m);
	Money& operator-=(const Money& m);
    Money& operator+=(const float& f);
    Money& operator-=(const float& f);

    Money& operator*=(const Money& m);
    Money& operator/=(const Money& m);
    Money& operator*=(const float& f);
    Money& operator/=(const float& f);

	// Print the value to a human readable value
	std::string toString() const;

	//Getters, setters
	float m_value() const;
	void set_m_value(const float value);

	~Money() = default;
private:
	float mValue;
};

