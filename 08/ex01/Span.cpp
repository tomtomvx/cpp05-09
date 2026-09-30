#include "Span.hpp"


Span::Span() : _v(), _size_max(0)
{
}

Span::Span(unsigned int n) : _v(), _size_max(n)
{
}

Span::Span(const Span& other) : _v(other._v), _size_max(other._size_max)
{
}

Span& Span::operator=(const Span& other)
{
	if (this != &other)
	{
		_v = other._v;
		_size_max = other._size_max;
	}
	return (*this);
}

Span::~Span()
{
}


void Span::addNumber(int n)
{
	if (_v.size() >= _size_max)
		throw SizeOver();
	_v.push_back(n);
}

unsigned int Span::shortestSpan()
{
	if (_v.size() < 2)
		throw std::runtime_error("Span needs at least two numbers");

	std::vector<int> sorted(_v);
	std::sort(sorted.begin(), sorted.end());

	int shortest = sorted[1] - sorted[0];
	for (std::vector<int>::size_type i = 2; i < sorted.size(); i++)
	{
		int distance = sorted[i] - sorted[i - 1];
		if (distance < shortest)
			shortest = distance;
	}

	return (static_cast<unsigned int>(shortest));
}

unsigned int Span::longestSpan()
{
	if (_v.size() < 2)
		throw std::runtime_error("Span needs at least two numbers");

	std::vector<int> sorted(_v);
	std::sort(sorted.begin(), sorted.end());

	unsigned int longest = sorted[sorted.back()] - sorted[0];

	return (longest);
}

char const *Span::SizeOver::what() const throw()
{
    return ("Span capacity exceeded");
}
