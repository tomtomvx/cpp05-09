#include "Span.hpp"

#include <cassert>
#include <climits>
#include <iostream>
#include <stdexcept>
#include <vector>

static void testBasic()
{
	Span span(5);

	span.addNumber(6);
	span.addNumber(3);
	span.addNumber(17);
	span.addNumber(9);
	span.addNumber(11);
	assert(span.shortestSpan() == 2);
	assert(span.longestSpan() == 14);
	std::cout << "Basic: OK" << std::endl;
}

static void expectTooFewNumbers(Span& span)
{
	bool shortestThrew = false;
	bool longestThrew = false;

	try
	{
		span.shortestSpan();
	}
	catch (const std::runtime_error&)
	{
		shortestThrew = true;
	}
	try
	{
		span.longestSpan();
	}
	catch (const std::runtime_error&)
	{
		longestThrew = true;
	}
	assert(shortestThrew && longestThrew);
}

static void testTooFewNumbers()
{
	Span empty(2);
	Span one(2);

	expectTooFewNumbers(empty);
	one.addNumber(42);
	expectTooFewNumbers(one);
	std::cout << "Too few numbers: OK" << std::endl;
}

static void testCapacity()
{
	Span zero(0);
	Span full(2);
	bool zeroThrew = false;
	bool fullThrew = false;

	try
	{
		zero.addNumber(1);
	}
	catch (const Span::SizeOver&)
	{
		zeroThrew = true;
	}
	full.addNumber(4);
	full.addNumber(5);
	try
	{
		full.addNumber(6);
	}
	catch (const Span::SizeOver&)
	{
		fullThrew = true;
	}
	assert(zeroThrew && fullThrew);
	assert(full.shortestSpan() == 1);
	assert(full.longestSpan() == 1);
	std::cout << "Capacity: OK" << std::endl;
}

static void testValues()
{
	Span duplicates(3);
	Span extremes(2);

	duplicates.addNumber(-10);
	duplicates.addNumber(-10);
	duplicates.addNumber(5);
	assert(duplicates.shortestSpan() == 0);
	assert(duplicates.longestSpan() == 15);
	extremes.addNumber(INT_MIN);
	extremes.addNumber(INT_MAX);
	assert(extremes.shortestSpan() == UINT_MAX);
	assert(extremes.longestSpan() == UINT_MAX);
	std::cout << "Values: OK" << std::endl;
}

static void testRange()
{
	int numbers[] = {4, 10, 20};
	int tooMany[] = {10, 20, 30};
	Span exact(3);
	Span overflow(3);
	bool rangeThrew = false;

	exact.addNumber(numbers, numbers + 3);
	assert(exact.shortestSpan() == 6);
	assert(exact.longestSpan() == 16);
	overflow.addNumber(1);
	try
	{
		overflow.addNumber(tooMany, tooMany + 3);
	}
	catch (const Span::SizeOver&)
	{
		rangeThrew = true;
	}
	assert(rangeThrew);
	overflow.addNumber(50);
	overflow.addNumber(100);
	assert(overflow.shortestSpan() == 49);
	assert(overflow.longestSpan() == 99);
	std::cout << "Range insertion: OK" << std::endl;
}

static void testLargeRange()
{
	std::vector<int> numbers;
	for (int i = 0; i < 10000; ++i)
		numbers.push_back(i);

	Span span(10000);
	span.addNumber(numbers.begin(), numbers.end());
	assert(span.shortestSpan() == 1);
	assert(span.longestSpan() == 9999);
	std::cout << "10,000 numbers: OK" << std::endl;
}

static void testCopyAndAssignment()
{
	Span original(3);
	original.addNumber(1);
	original.addNumber(4);

	Span copied(original);
	Span assigned(1);
	assigned.addNumber(99);
	assigned = original;
	original.addNumber(10);
	assert(original.longestSpan() == 9);
	assert(copied.longestSpan() == 3);
	assert(assigned.longestSpan() == 3);
	copied.addNumber(7);
	assigned.addNumber(8);
	assert(copied.longestSpan() == 6);
	assert(assigned.longestSpan() == 7);
	std::cout << "Copy and assignment: OK" << std::endl;
}

int main()
{
	testBasic();
	testTooFewNumbers();
	testCapacity();
	testValues();
	testRange();
	testLargeRange();
	testCopyAndAssignment();
	std::cout << "All tests passed" << std::endl;
	return (0);
}
