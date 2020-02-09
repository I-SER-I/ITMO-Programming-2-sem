#include "Complex.h"

Complex::Complex(const double re = 0, const double im = 0) : re_(re), im_(im)
{

}
Complex::Complex() : re_(0), im_(0)
{

}
Complex::Complex(const Complex& a)
{
	this->im_ = a.im_;
	this->re_ = a.re_;
}
Complex& Complex::operator=(const Complex& a)
{
	if (this != &a)
	{
		this->re_ = a.re();
		this->im_ = a.im();
	}
	return *this;
}
Complex::~Complex() = default;

double Complex::re() const
{
	return this->re_;
}
double Complex::im() const
{
	return this->im_;
}
double Complex::length() const
{
	return sqrt(pow(this->re(), 2) + pow(this->im(), 2));
}

std::istream& operator>>(std::istream& stream, Complex& a)
{
	stream >> a.re_ >> a.im_;
	return stream;	
}
std::ostream& operator<<(std::ostream& stream, const Complex& a) 
{
	stream << a.re() << (a.im() >= 0 ? "+" : "") << a.im() << 'i';
	return stream;
}

Complex operator*(Complex& a, double& b)
{
	return Complex(a.re() * b, a.im() * b);
}
Complex operator+(Complex& a, Complex& b)
{
	return Complex(a.re() + b.re(), a.im() + b.im());
}
Complex operator*(Complex& a, Complex& b)
{
	return Complex(a.re() * b.re() - a.im() * b.im(), a.re() * b.im() + a.im() * b.re());
}