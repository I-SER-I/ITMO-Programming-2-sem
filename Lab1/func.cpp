#include "func.h"

void Swap(int& a, int& b) {
    int temp = b;
    b = a;
    a = temp;
}
void Swap(int* a, int* b) {
    int temp = *b;
    *b = *a;
    *a = temp;
}

void Round(double& x) {
    x = (int)x;
}
void Round(double* x) {
    *x = (int)(*x);
}

void ComplexMultiReal(complex& z, double& x) {
    z.re *= x;
    z.im *= x;
}
void ComplexMultiReal(complex* z, double* x) {
    z->re *= *x;
    z->im *= *x;
}

void CircleMove(circle& obj, double& x, double& y) {
    obj.x += x;
    obj.y += y;
}
void CircleMove(circle* obj, double* x, double* y) {
    obj->x += *x;
    obj->y += *y;
}