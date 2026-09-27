#include "Array.hpp"


template<typename T>
Array<T>::Array() : _data(NULL), _size(0)
{
}

template<typename T>
Array<T>::Array(unsigned int n) : _data(n ? new[n](); NULL), _size(n)
{
	// if (n)
	// 	_data = new T[n]();
}

// template<typename T>
// Array<T>::Array(const Array& other) : _size(other._size)
// {
// 	_data = new T[other._size];
// 	for (unsigned int i = 0; i < other._size; i++)
// 		_data[i] = other._data[i];
// }

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
	_size(other._size);
}

// template<typename T>
// Array<T>& Array<T>::operator=(const Array& other)
// {
// 	if (this == &other)
// 		return (*this);

// 	T* tmp_data = new T[other._size];
// 	for (unsigned int i = 0; i < other._size; i++)
// 		tmp_data[i] = other._data[i];
// 	delete[] _data;
// 	_data = tmp_data;
// 	_size = other._size;

// 	return (*this);
// }

template<typename T>
Array<T>& Array<T>::operator=(const Array& other)
{
	if (this == &other)
		return (*this);

	T* tmp_data = new T[other._size];
	for (unsigned int i = 0; i < other._size; i++)
		tmp_data[i] = other._data[i];
	delete[] _data;
	_data = tmp_data;
	_size = other._size;

	return (*this);
}


// template <typename T>
// Array<T>& Array<T>::operator=(const Array& other)
// {
//     Array<T> copy(other);

// 	delete[] _data;

//     T* oldData = _data;

//     unsigned int oldSize = _size;
//     _data = copy._data;
//     _size = copy._size;
//     copy._data = oldData;
//     copy._size = oldSize;
//     return *this;
// }

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
