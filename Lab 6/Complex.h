#pragma once
#include <fstream>

class Complex {
private:
	double re_;
	double im_;
public:
	Complex();
	explicit Complex(double re, double im);
	Complex(const Complex&);
	Complex& operator=(const Complex&);
	~Complex();

	friend std::istream& operator>>(std::istream&, Complex&);
	double re() const;
	double im() const;
	double length() const;
};

Complex operator*(Complex&, double&);
Complex operator+(Complex&, Complex&);
Complex operator*(Complex&, Complex&);
std::ostream& operator<<(std::ostream&, const Complex&);