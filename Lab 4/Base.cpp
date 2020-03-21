#include "Base.h"

CVector2D::CVector2D(): x(0), y(0)
{
	double x = 0;
	double y = 0;
}
std::istream& operator>>(std::istream& stream, CVector2D& vector)
{
	stream >> vector.x >> vector.y;
	return stream;
}
std::ostream& operator<<(std::ostream& stream, const CVector2D& vector)
{
	stream << "(" << vector.x << ";" << vector.y << ")";
	return stream;
}