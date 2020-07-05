#pragma once
#include <algorithm>
#include <iterator>
#include <initializer_list>

template <class T>
class CircleBuffer
{
public:
	class iterator : public std::iterator<std::random_access_iterator_tag, T>
	{
	public:
		using difference_type = typename std::iterator<std::random_access_iterator_tag, T>::difference_type;
		difference_type operator-(const iterator& obj) const
		{
			return _data - obj._data;
		}
		explicit iterator(T* start)
		{
			_data = start;
		}
		iterator(const iterator& obj)
		{
			_data = obj._data;
		}
		~iterator() = default;
		T& operator*()
		{
			return *(_data);
		}
		T* operator->()
		{
			return _data;
		}
		iterator operator++()
		{
			++_data;
			return *this;
		}
		iterator operator--()
		{
			--_data;
			return *this;
		}
		iterator operator+(int value)
		{
			_data = _data + value;
			return *this;
		}
		iterator operator-(int value)
		{
			_data = _data - value;
			return *this;
		}
		bool operator==(const iterator& it) const
		{
			return _data == it._data;
		}
		bool operator!=(const iterator& it) const
		{
			return _data != it._data;
		}
		bool operator<(const iterator& it) const
		{
			return _data < it._data;
		}
		bool operator<=(const iterator& it) const
		{
			return _data <= it._data;
		}
		bool operator>(const iterator& it) const
		{
			return _data > it._data;
		}
		bool operator>=(const iterator& it) const
		{
			return _data >= it._data;
		}
	private:
		T* _data = nullptr;
	};
	iterator begin() const
	{
		return iterator(_data);
	}
	iterator end() const
	{
		return iterator(_data + _size);
	}
	size_t capacity() const
	{
		return this->_capacity;
	}
	size_t size() const
	{
		return this->_size;
	}
	explicit CircleBuffer(size_t capacity)
	{
		_capacity = capacity;
		_data = new T[_capacity];
	}
        CircleBuffer(const CircleBuffer& buffer)
            : _size(buffer._size),
              _capacity(buffer._capacity),
              _data(buffer._data)
	{
	};
	~CircleBuffer()
	{
		delete[] _data;
	}
	void push_front(T value)
	{
		if (_size < _capacity)
		{
			for (size_t i = _size; i >= 1; i--)
				_data[i] = _data[i - 1];
			_data[0] = value;
			_size++;
		}
		else
		{
			for (size_t i = _capacity - 1; i >= 1; i--)
				_data[i] = _data[i - 1];
			_data[0] = value;
		}
	}
	void pop_front()
	{
		for (size_t i = 0; i < _size - 1; i++)
			_data[i] = _data[i + 1];
		_size--;
	}
	void push_back(T value)
	{
		if (_size < _capacity)
		{
			_data[_size] = value;
			_size++;
		}
		else
		{
			for (size_t i = 1; i < _capacity; i++)
				_data[i - 1] = _data[i];
			_data[_capacity - 1] = value;
		}
	}
	void pop_back()
	{
		if (_size > 0)
			_size--;
	}
	void insert(size_t it, T value)
	{
		_data[it % _capacity] = value;
	}
	void insert(iterator it, T value)
	{
		*(begin() + (it - begin()) % _size) = value;
	}
	void remove(size_t it)
	{
		for (size_t i = it + 1; i < _size; i++)
			_data[(i - 1) % _capacity] = _data[i % _capacity];
		_size--;
	}
	void resize(size_t new_capacity)
	{
		T* new_data = new T[new_capacity];
		_size = std::min(_size, new_capacity);
		for (size_t i = 0; i < _size; i++)
			new_data[i] = _data[i];
		delete _data;
		_data = new_data;
		_capacity = new_capacity;
	}
	T operator[](size_t it)
	{
		return _data[it % _capacity];
	}
	CircleBuffer& operator=(std::initializer_list<T> list)
	{
		_capacity = list.size();
		_data = new T[list.size()];
		for (auto it = list.begin(); it != list.end(); ++it)
			push_back(*it);
		return *this;
	}
private:
	size_t _size = 0;
	size_t _capacity = 0;
	T* _data = nullptr;
};