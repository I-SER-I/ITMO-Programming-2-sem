#include "Triangle.h"

Triangle::Point::Point(double x = 0, double y = 0)
{
	this->x = x;
	this->y = y;
}
Triangle::Point::~Point() = default;
double distance(Triangle::Point a, Triangle::Point b)
{
	return sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}
double area(Triangle a) {
	double A_B = distance(a.A, a.B);
	double B_C = distance(a.B, a.C);
	double C_A = distance(a.C, a.A);
	double p = (A_B + B_C + C_A) / 2.0;
	return sqrt(p * (p - A_B) * (p - B_C) * (p - C_A));
}
Triangle::Triangle()
{
}
Triangle::Triangle(Triangle::Point A_, Triangle::Point B_, Triangle::Point C_)
{
	A = A_;
	B = B_;
	C = C_;
}
Triangle::~Triangle() = default;

std::istream& operator>>(std::istream& stream, Triangle::Point& a)
{
	stream >> a.x >> a.y;
	return stream;
}
std::ostream& operator<<(std::ostream& stream, const Triangle::Point& a)
{
	stream << a.x << " " << a.y;
	return stream;
}
std::istream& operator>>(std::istream& stream, Triangle& a)
{
	stream >> a.A.x >> a.A.y >> a.B.x >> a.B.y >> a.C.x >> a.C.y;
	return stream;
}
std::ostream& operator<<(std::ostream& stream, const Triangle& a)
{
	stream << "(" << a.A.x << ";" << a.A.y << ")\n(" << a.B.x << ";" << a.B.y << ")\n(" << a.C.x << ";" << a.C.y << ")";
	return stream;
}
bool operator==(Triangle& a, Triangle& b) {
	if (area(a) == area(b))
		return true;
	else
		return false;
}
bool operator!=(Triangle& a, Triangle& b) {
	if (area(a) != area(b))
		return true;
	else
		return false;
}
bool operator<(Triangle& a, Triangle& b) {
	if (area(a) < area(b))
		return true;
	else
		return false;
}
bool operator>(Triangle& a, Triangle& b) {
	if (area(a) > area(b))
		return true;
	else
		return false;
}