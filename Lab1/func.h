#pragma once

void Swap(int&, int&);
void Swap(int*, int*);

void Round(double&);
void Round(double*);

struct complex {
	double re;
	double im;
};
void ComplexMultiReal(complex&, double&);
void ComplexMultiReal(complex*, double*);

struct circle {
	double x;
	double y;
	double r;
};
void CircleMove(circle&, double&, double&);
void CircleMove(circle*, double*, double*);
