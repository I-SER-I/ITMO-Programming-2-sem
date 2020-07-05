#include <iostream>
#include <vector>
#include "Iterator.h"
#include "Complex.h"

template <typename T>
bool predicat(T value) {
    return value > 0;
}

template <typename T>
bool sort(T firstValue, T secondValue) {
    return firstValue <= secondValue;
}

int main() {
    size_t n = 0;
    std::cout << "Add first array size: ";
    std::cin >> n;
    std::vector<int> first(n);
	for(size_t i = 0; i < n; i++)
    std::vector<Complex> second = {Complex{1.1, 1.2 }, Complex{1.63, 2.32 }, Complex{5.4, 9.1} };
    std::cout << "First array (int):\n" << std::endl;
    std::cout << "\tall_of: ";
    std::cout << ((all_of(first.begin(), first.end(), predicat<int>)) ? "\tTRUE" : "\tFALSE") << std::endl;
    std::cout << "\tis_sorted: ";
    std::cout << ((is_sorted(first.begin(), first.end(), sort<int>)) ? "\tTRUE" : "\tFALSE") << std::endl;
    std::cout << "\tis_palindrome: ";
    std::cout << ((is_palindrome(first.begin(), first.end(), predicat<int>)) ? "\tTRUE" : "\tFALSE") << std::endl;
    std::cout << "Second array (Complex):\n" << std::endl;
    std::cout << "\tall_of: ";
    std::cout << ((all_of(second.begin(), second.end(), predicat<Complex>)) ? "\tTRUE" : "\tFALSE") << std::endl;
    std::cout << "\tis_sorted: ";
	std::cout << ((is_sorted(second.begin(), second.end(), sort<Complex>)) ? "\tTRUE" : "\tFALSE") << std::endl;
    std::cout << "\tis_palindrome: ";
	std::cout << ((is_palindrome(second.begin(), second.end(), predicat<Complex>)) ? "\tTRUE" : "\tFALSE") << std::endl;
	return 0;
}