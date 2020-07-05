#pragma once
#include <GLFW/glut.h>

struct Vector3D
{
	double x, y, z;
	double operator *(const Vector3D&) const;
	Vector3D cross(const Vector3D&) const;
	double normalize() const;
};

class VirtualOrb
{
public:
	VirtualOrb();
	operator bool() const;
	void setRotate(double, Vector3D);
	void setStart(double, double);
	void setMiddle(double, double);
	void setEnd(double, double);
	void rotate();

private:
	bool isStarted;
	double R, deg;
	Vector3D start, end, axis;
	GLfloat M[16];
	Vector3D screenToOrb(double, double);
	void clear();
};

