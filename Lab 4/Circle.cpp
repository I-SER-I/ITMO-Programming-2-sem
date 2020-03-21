#include "Circle.h"
#include "Base.h"

#include <corecrt_math_defines.h>
#include <iostream>
const double pi = M_PI;

Circle::~Circle() = default;
Circle::Circle()
{
	this->Circle::initFromDialogue();
}
double Circle::square() 
{
	return pi * pow(radius, 2);
}
double Circle::perimeter() 
{
	return 2 * pi * radius;
}
double Circle::mass() const
{
	return weight;
}
CVector2D Circle::position() const
{
	return center;
}
bool Circle::operator==(const IPhysObject& object) const
{
	return mass() == object.mass();
}
bool Circle::operator<(const IPhysObject& object) const
{
	return mass() < object.mass();
} 
void Circle::draw()
{
	std::cout << "Name: " << name << std::endl;
	std::cout << "Position: " << center << std::endl;
	std::cout << "Radius: " << radius << std::endl;
	std::cout << "Weight: " << weight << std::endl;
	std::cout << "Size: " << size() << std::endl;
	std::cout << std::endl;
}
void Circle::initFromDialogue()
{
	std::cout << "\t\tAdd center coords: ";
	std::cin >> center;
	std::cout << "\t\tAdd radius: ";
	std::cin >> radius;
	std::cout << "\t\tAdd weight: ";
	std::cin >> weight;
	std::cout << std::endl;
}
const char* Circle::className() 
{
	return name;
}
unsigned Circle::size() 
{
	return sizeof(*this);
}