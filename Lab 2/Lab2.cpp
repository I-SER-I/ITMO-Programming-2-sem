#include <iostream>
#include "Complex.h"

void first_task() {
    std::cout << std::endl;
    std::cout << "    Task 1:" << std::endl;
    std::cout << "Enter complex number: ";
    Complex FirstValue;
    std::cin >> FirstValue;
    std::cout << "Enter real number: ";
    double SecondValue;
    std::cin >> SecondValue;
    std::cout << "Multiply a complex number on real number: " << FirstValue * SecondValue << std::endl;
}
void second_task() {
    std::cout << std::endl;
    std::cout << "    Task 2:" << std::endl;
    std::cout << "Enter complex number: ";
    Complex FirstValue;
    std::cin >> FirstValue;
    std::cout << "Enter complex number: ";
    Complex SecondValue;
    std::cin >> SecondValue;
    std::cout << "Sum of two complex numbers: " << FirstValue + SecondValue << std::endl;
}
void third_task() {
    std::cout << std::endl;
    std::cout << "    Task 3:" << std::endl;
    std::cout << "Enter complex number: ";
    Complex FirstValue;
    std::cin >> FirstValue;
    std::cout << "Enter complex number: ";
    Complex SecondValue;
    std::cin >> SecondValue;
    std::cout << "Multiply of two complex numbers: " << FirstValue * SecondValue << std::endl;
}

int main() {
    std::cout << "\t --- LAB #2 ---" << std::endl;
    first_task();
    second_task();
    third_task();
}