#pragma once
#include "Åxception.h"

template <size_t N, typename T>
class Stack {
public:
	Stack();
	~Stack();
	void push(const T& value);
	void pop();
private:
	int top;
    T* array;
};

template <size_t N, typename T>
Stack<N, T>::Stack() {
	array = new T[N];
	top = 0;
}
template <size_t N, typename T>
Stack<N, T>::~Stack() {
	delete[] array;
}

template <size_t N, typename T>
void Stack<N, T>::push(const T& value) {
	if (top == N) {
		throw Exception("ERROR. Stack over flow", 1);
	}
	else {
		array[top] = value;
		top++;
	}
}

template <size_t N, typename T>
void Stack<N, T>::pop() {
	if (top < 0)
		throw Exception("ERROR. Out of range", 1);
	else
		array[top--];
}

template<typename T>
T Max(T* array) {
	T max = array[0];
	for (size_t i = 1; i < sizeof(array); i++)
		if (array[i] > max)
			max = array[i];
	return max;
}