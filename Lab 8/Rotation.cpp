#include "Rotation.h"
#include <cmath>
#include <algorithm>

double Vector3D::operator*(const Vector3D& r) const
{
	return x * r.x + y * r.y + z * r.z;
}

Vector3D Vector3D::cross(const Vector3D& r) const
{
	return {y * r.z - z * r.y, x * r.z - z * r.x, y * r.x - x * r.y};
}

double Vector3D::normalize() const { return sqrt((*this) * (*this)); }

VirtualOrb::VirtualOrb()
{
	R = 0.5;
	isStarted = false;
	clear();
}

VirtualOrb::operator bool() const { return isStarted; }

void VirtualOrb::setRotate(double deg, Vector3D v)
{
	clear();
	glPushMatrix();
	glRotated(deg, v.x, v.y, v.z);
	glGetFloatv(GL_MODELVIEW_MATRIX, M);
	glPopMatrix();
}

void VirtualOrb::setStart(double x, double y)
{
	isStarted = true;
	start = screenToOrb(x, y);
}

void VirtualOrb::setMiddle(double x, double y)
{
	static const double coeff = 180.0 / acos(-1.0);
	end = screenToOrb(x, y);
	double alpha = acos(start * end / start.normalize() / end.normalize());
	deg = alpha * coeff;
	Vector3D v = start.cross(end);
	axis.x = v.x * M[0] + v.y * M[1] + v.z * M[2];
	axis.y = v.x * M[4] + v.y * M[5] + v.z * M[6];
	axis.z = v.x * M[8] + v.y * M[9] + v.z * M[10];
}

void VirtualOrb::setEnd(double x, double y)
{
	isStarted = false;
	setMiddle(x, y);
	glPushMatrix();
	glLoadMatrixf(M);
	glRotated(deg, axis.x, axis.y, axis.z);
	glGetFloatv(GL_MODELVIEW_MATRIX, M);
	glPopMatrix();
	clear();
}

void VirtualOrb::rotate()
{
	glMultMatrixf(M);
	glRotated(deg, axis.x, axis.y, axis.z);
}

Vector3D VirtualOrb::screenToOrb(double x, double y)
{
	double len = sqrt(x * x + y * y);
	if (len > R) return {R * x / len, R * y / len, 0};
	return {x, y, sqrt(R * R - x * x - y * y)};
}

void VirtualOrb::clear()
{
	deg = 0;
	axis.x = 1;
	axis.y = axis.z = 0;
}
