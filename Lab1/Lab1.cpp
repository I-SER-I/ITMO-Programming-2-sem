#include <iostream>
#include "func.h"
#include "Lab1.h"

int main() {
    std::cout << "\t --- LAB #1 ---" << std::endl;
    std::cout << std::endl;
    std::cout << "    Task 1:" << std::endl;
    int a1 = 12, b1 = 453;
    std::cout << "Values: " << a1 << " " << b1 << std::endl;
    Swap(a1, b1);
    std::cout << "Swap with links: " << a1 << " " << b1 << std::endl;
    Swap(&a1, &b1);
    std::cout << "Swap with pointers: " << a1 << " " << b1 << std::endl;

    std::cout << std::endl;
    std::cout << "    Task 2:" << std::endl;
    double a2 = 10.15, b2 = 54.45;
    std::cout << "Values: " << a2 << " " << b2 << std::endl;
    Round(a2);
    std::cout << "Discards the fractional part with links: " << a1 << std::endl;
    Round(&b2);
    std::cout << "Discards the fractional part with pointers: " << b2 << std::endl;

    std::cout << std::endl;
    std::cout << "    Task 3:" << std::endl;
    complex a3;
    a3.im = 2, a3.re = 3;
    double b3 = 1.25;
    std::cout << "Values: " << a3.re << "+" << a3.im << "i" << " " << b3 << std::endl;
    ComplexMultiReal(a3, b3);
    std::cout << "Multiplies a complex variable by real number with links: " << a3.re << "+" << a3.im << "i" << std::endl;
    ComplexMultiReal(&a3, &b3);
    std::cout << "Multiplies a complex variable by real number with pointers: " << a3.re << "+" << a3.im << "i" << std::endl;

    std::cout << std::endl;
    std::cout << "    Task 4:" << std::endl;
    circle a4;
    a4.x = 1, a4.y = 5;
    double x = 5, y = -3;
    std::cout << "Circle center coords: " << "(" << a4.x << ";" << a4.y << ")" << std::endl;
    std::cout << "Vector: " << "{" << x << ";" << y << "}" << std::endl;
    CircleMove(a4, x, y);
    std::cout << "Move center of the circle coords with links: " << "(" << a4.x << ";" << a4.y << ")" << std::endl;
    CircleMove(&a4, &x, &y);
    std::cout << "Move center of the circle coords with pointers: " << "(" << a4.x << ";" << a4.y << ")" << std::endl;
}