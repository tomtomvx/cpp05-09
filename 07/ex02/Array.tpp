#include "Array.hpp"


template<typename T>
Array<T>::Array() : _data(NULL), _size(0)
{
}

template<typename T>
Array<T>::Array(unsigned int n) : _data(n ? new T[n](): NULL), _size(n)
{
}

template<typename T>
Array<T>::Array(const Array& other) : _data(NULL), _size(0)
{
	if (other._size == 0)
		return ;

	_data = new T[other._size];
	try
	{
		for (unsigned int i = 0; i < other._size; i++)
			_data[i] = other._data[i];
	}
	catch (...)
	{
		delete[] _data;
		throw ;
	}
	_size = other._size;
}

template <typename T>
Array<T>& Array<T>::operator=(const Array& other)
{
    Array<T> tmp(other);

	T* oldData = _data;
	unsigned int oldSize = _size;
	_data = tmp._data;
	_size = tmp._size;
	tmp._data = oldData;
	tmp._size = oldSize;
    return *this;
}

template<typename T>
Array<T>::~Array()
{
	delete[] _data;
}


template<typename T>
T& Array<T>::operator[](unsigned int index)
{
	if (index >= _size)
        throw std::out_of_range("Array index out of range");
	return (_data[index]);
}

template<typename T>
const T& Array<T>::operator[](unsigned int index) const
{
	if (index >= _size)
        throw std::out_of_range("Array index out of range");
	return (_data[index]);
}

template<typename T>
unsigned int Array<T>::size() const
{
	return (_size);
}
