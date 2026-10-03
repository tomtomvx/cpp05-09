#include "Span.hpp"

#include <algorithm>

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
		throw SpanException("Span capacity exceeded");
	_v.push_back(n);
}

unsigned int Span::shortestSpan()
{
	if (_v.size() < 2)
		throw SpanException("Span needs at least two numbers");

	std::vector<int> sorted(_v);
	std::sort(sorted.begin(), sorted.end());

	unsigned int shortest = static_cast<unsigned int>(sorted[1])
							- static_cast<unsigned int>(sorted[0]);

	for (std::vector<int>::size_type i = 2; i < sorted.size(); i++)
	{
		unsigned int distance = static_cast<unsigned int>(sorted[i])
								- static_cast<unsigned int>(sorted[i - 1]);

		if (distance < shortest)
			shortest = distance;
	}

	return (shortest);
}

unsigned int Span::longestSpan()
{
	if (_v.size() < 2)
		throw SpanException("Span needs at least two numbers");

	std::vector<int> sorted(_v);
	std::sort(sorted.begin(), sorted.end());

	unsigned int longest = static_cast<unsigned int>(sorted.back())
						   - static_cast<unsigned int>(sorted.front());

	return (longest);
}

Span::SpanException::SpanException(const char *message) throw()
	: _message(message)
{
}

char const *Span::SpanException::what() const throw()
{
	return (_message);
}
