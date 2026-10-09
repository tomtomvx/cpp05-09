#include "RPN.hpp"

#include <deque>
#include <limits>
#include <sstream>
#include <stdexcept>

RPN::RPN()
{
}

RPN::RPN(const RPN& other)
{
	(void)other;
}

RPN& RPN::operator=(const RPN& other)
{
	(void)other;
	return *this;
}

RPN::~RPN()
{
}

static int calculate(int left, int right, char operation)
{
	const int minimum = std::numeric_limits<int>::min();
	const int maximum = std::numeric_limits<int>::max();

	if (operation == '+')
	{
		if ((right > 0 && left > maximum - right)
			|| (right < 0 && left < minimum - right))
			throw std::runtime_error("Error");
		return left + right;
	}
	if (operation == '-')
	{
		if ((right < 0 && left > maximum + right)
			|| (right > 0 && left < minimum + right))
			throw std::runtime_error("Error");
		return left - right;
	}
	if (operation == '*')
	{
		const double product = static_cast<double>(left) * right;
		if (product < minimum || product > maximum)
			throw std::runtime_error("Error");
		return left * right;
	}
	if (right == 0 || (left == minimum && right == -1))
		throw std::runtime_error("Error");
	return left / right;
}

int RPN::evaluate(const std::string& expression) const
{
	std::istringstream input(expression);
	std::deque<int> numbers;
	std::string token;

	while (input >> token)
	{
		if (token.size() != 1)
			throw std::runtime_error("Error");
		const char symbol = token[0];
		if (symbol >= '0' && symbol <= '9')
			numbers.push_back(symbol - '0');
		else if (symbol == '+' || symbol == '-' || symbol == '*'
			|| symbol == '/')
		{
			if (numbers.size() < 2)
				throw std::runtime_error("Error");
			const int right = numbers.back();
			numbers.pop_back();
			const int left = numbers.back();
			numbers.pop_back();
			numbers.push_back(calculate(left, right, symbol));
		}
		else
			throw std::runtime_error("Error");
	}
	if (numbers.size() != 1)
		throw std::runtime_error("Error");
	return numbers.back();
}
