#include <iostream>
#include "Triangle.h"
#include "Array.h"

void FirstTask() {
	std::cout << std::endl;
	std::cout << "    Task 1:" << std::endl;
	Triangle First, Second;
	std::cin >> First >> Second;
	if (First < Second)
		std::cout << "First triangle is smaler than second" << std::endl;
	if (First > Second)
		std::cout << "First triangle is larger than second" << std::endl;
	if (First == Second)
		std::cout << "Triangles are same" << std::endl;
	if (First != Second)
		std::cout << "Triangles are different" << std::endl;
	std::cout << std::endl;
	std::cout << First << std::endl;
	std::cout << std::endl;
	std::cout << Second << std::endl;
}
void SecondTask() {
	std::cout << std::endl;
	std::cout << "    Task 2:" << std::endl;
	Array First, Second;
	std::cin >> First >> Second;
	if (First < Second)
		std::cout << "First array is smaler than second" << std::endl;
	if (First > Second)
		std::cout << "First array is larger than second" << std::endl;
	if (First == Second)
		std::cout << "Arrays are same" << std::endl;
	if (First != Second)
		std::cout << "Arrays are different" << std::endl;
	std::cout << std::endl;
	std::cout << First << std::endl;
	std::cout << std::endl;
	std::cout << Second << std::endl;
	std::cout << std::endl;
	Array Third = First.operator+(Second);
	std::cout << Third << std::endl;
}

int main() { 
	std::cout << "\t --- LAB #3 ---" << std::endl;
	FirstTask();
	SecondTask();
}