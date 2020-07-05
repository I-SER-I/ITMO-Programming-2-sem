#pragma once
#include <algorithm>

template <class T>
typename CircleBuffer<T>::iterator::difference_type CircleBuffer<T>::iterator::operator-(const iterator& other) const
{
	return _data - other._data;
}

template <class T>
CircleBuffer<T>::iterator::iterator(T* start)
{
	data_ = start;
}

template <class T>
CircleBuffer<T>::iterator::iterator(const iterator& obj)
{
	data_ = obj.data_;
}

template <class T>
CircleBuffer<T>::iterator::~iterator() = default;

template <class T>
T& CircleBuffer<T>::iterator::operator*()
{
	return *(data_);
}

template <class T>
T* CircleBuffer<T>::iterator::operator->()
{
	return data_;
}

template <class T>
CircleBuffer<T>::iterator CircleBuffer<T>::iterator::operator++()
{
	++data_;
	return *this;
}

template <class T>
CircleBuffer<T>::iterator CircleBuffer<T>::iterator::operator--()
{
	--data_;
	return *this;
}

template <class T>
CircleBuffer<T>::iterator CircleBuffer<T>::iterator::operator+(int value)
{
	data_ = data_ + value;
	return *this;
}

template <class T>
CircleBuffer<T>::iterator CircleBuffer<T>::iterator::operator-(int value)
{
	data_ = data_ - value;
	return *this;
}

template <class T>
bool CircleBuffer<T>::iterator::operator==(const iterator& obj) const
{
	return data_ == obj.data_;
}

template <class T>
bool CircleBuffer<T>::iterator::operator!=(const iterator& obj) const
{
	return data_ != obj.data_;
}

template <class T>
bool CircleBuffer<T>::iterator::operator<(const iterator& obj) const
{
	return data_ < obj.data_;
}

template <class T>
bool CircleBuffer<T>::iterator::operator<=(const iterator& obj) const
{
	return data_ <= obj.data_;
}

template <class T>
bool CircleBuffer<T>::iterator::operator>(const iterator& obj) const
{
	return data_ > obj.data_;
}

template <class T>
bool CircleBuffer<T>::iterator::operator>=(const iterator& obj) const
{
	return data_ >= obj.data_;
}

template <class T>
CircleBuffer<T>::CircleBuffer(size_t capacity)
{
	capacity_ = capacity;
	data = new T[capacity_];
}

template <class T>
CircleBuffer<T>::CircleBuffer(const CircleBuffer& other) : size_(other.size_), capacity_(other.capacity_), data(other.data)
{
}

template <class T>
CircleBuffer<T>::~CircleBuffer()
{
	delete[] data;
}

template <class T>
size_t CircleBuffer<T>::capacity() const
{
	return this->capacity_;
}

template <class T>
size_t CircleBuffer<T>::size() const
{
	return this->size_;
}

template <class T>
typename CircleBuffer<T>::iterator CircleBuffer<T>::begin() const
{
	return iterator(data);
}

template <class T>
typename CircleBuffer<T>::iterator CircleBuffer<T>::end() const
{
	return iterator(data + size_);
}

template <class T>
void CircleBuffer<T>::push_front(T x)
{
	if (size_ < capacity_)
	{
		for (size_t i = size_; i >= 1; i--)
			data[i] = data[i - 1];
		data[0] = x;
		size_++;
	}
	else
	{
		for (size_t i = capacity_ - 1; i >= 1; i--)
			data[i] = data[i - 1];
		data[0] = x;
	}
}

template <class T>
void CircleBuffer<T>::pop_front()
{
	for (size_t i = 0; i < size_ - 1; i++)
		data[i] = data[i + 1];
	size_--;
}

template <class T>
void
CircleBuffer<T>::push_back(T x)
{
	if (size_ < capacity_)
	{
		data[size_] = x;
		size_++;
	}
	else
	{
		for (size_t i = 1; i < capacity_; i++)
			data[i - 1] = data[i];
		data[capacity_ - 1] = x;
	}
}

template <class T>
void CircleBuffer<T>::pop_back()
{
	if (size_ > 0)
		size_--;
}

template <class T>
void CircleBuffer<T>::insert(size_t ind, T x)
{
	data[ind % capacity_] = x;
}

template <class T>
void CircleBuffer<T>::insert(iterator ind, T x)
{
	*(begin() + (ind - begin()) % size_) = x;
}

template <class T>
void CircleBuffer<T>::remove(size_t ind)
{
	for (size_t i = ind + 1; i < size_; i++)
		data[(i - 1) % capacity_] = data[i % capacity_];
	size_--;
}

template <class T>
void CircleBuffer<T>::resize(size_t new_capacity)
{
	T* new_data = new T[new_capacity];
	size_ = std::min(size_, new_capacity);
	for (size_t i = 0; i < size_; i++)
		new_data[i] = data[i];
	delete[] data;
	data = new_data;
	capacity_ = new_capacity;
}

template <class T>
T CircleBuffer<T>::operator[](size_t ind)
{
	return data[ind % capacity_];
}

template <class T>
CircleBuffer<T>& CircleBuffer<T>::operator=(std::initializer_list<T> list)
{
	capacity_ = list.size();
	data = new T[list.size()];
	for (auto it = list.begin(); it != list.end(); ++it)
		push_back(*it);
	return *this;
}