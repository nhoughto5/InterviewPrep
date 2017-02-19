#include "stdafx.h"
#include "Complex.h"


Complex::Complex()
{
}

Complex::Complex(double real_, double imaginary_)
{
	real = real_;
	imaginary = imaginary_;
}

//Copy Constructor
Complex::Complex(const Complex & p)
{
	real = p.real;
	imaginary = p.imaginary;
}

//Move Constructor
Complex::Complex(Complex && p)
{
	real = p.real;
	imaginary = p.imaginary;
}


const Complex & Complex::operator=(const Complex & p)
{
	real = p.real;
	imaginary = p.imaginary;
	return *this;
}

Complex::~Complex()
{
}

double Complex::getReal() const
{
	return real;
}

double Complex::getImaginary() const
{
	return imaginary;
}

Complex Complex::operator+(const Complex & other)
{
	return Complex(real + other.real, imaginary + other.imaginary);
}

Complex Complex::operator+(double d)
{
	return Complex(real + d, imaginary);
}

Complex Complex::operator-(const Complex & other)
{
	return Complex(real - other.real, imaginary - other.imaginary);
}

Complex operator+(double d, Complex & c)
{
	return Complex(c.real + d, c.imaginary);
}

Complex Complex::operator*() const
{
	return Complex(real, -imaginary);
}
