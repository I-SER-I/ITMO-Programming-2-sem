#include <iostream>
#include "CircleBuffer.hpp"

template <class T>
void info(const CircleBuffer<T>& v) {
    std::cout << "Capacity: " << v.capacity() << "\n";
    std::cout << "Size: " << v.size() << "\n";
    std::cout << "Items: ";
    for (auto it : v)
	    std::cout << it << ' ';
    std::cout << "\n";
}

int main() {
    CircleBuffer<int> test(3);
    test.push_front(1);
    test.push_back(5);
    test.pop_back();
    test.pop_front();
	info(test);
    return 0;
}