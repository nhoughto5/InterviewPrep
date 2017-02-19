#pragma once
class Complex
{
public:
	Complex();
	Complex(double real, double imaginary);

	//Copy Constructor
	Complex(const Complex &p);

	//Move Constructor
	Complex(Complex &&p);

	//Move Assignment Operator
	const Complex& operator=(const Complex &other);

	~Complex();

	friend std::ostream &operator<<(std::ostream &out, const Complex &other) {
		if (other.imaginary < 0) {
			out << other.real << " " << other.imaginary << "i";
		}
		else {
			out << other.real << " +" << other.imaginary << "i";
		}
		return out;
	}

	double getReal() const;
	double getImaginary() const;

	Complex operator+(const Complex &other);

	// Complex + double
	Complex operator+(double d);

	// Double + Complex
	friend Complex operator+(double d, Complex& c);

	Complex operator-(const Complex &other);

	//Complex Conjugate
	Complex operator*() const;

private:
	double real, imaginary;
};

