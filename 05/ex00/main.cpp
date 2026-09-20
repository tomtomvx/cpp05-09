#include "Bureaucrat.hpp"

#include <iostream>

static void TryTest(std::string const &name, int grade)
{
	try
	{
		Bureaucrat bureaucrat(name, grade);
		std::cout << bureaucrat << std::endl;
		bureaucrat.incrementGrade();
		std::cout << bureaucrat << std::endl;
		bureaucrat.decrementGrade();
		std::cout << bureaucrat << std::endl;
	}
	catch (std::exception const &e)
	{
		std::cout << name << ": " << e.what() << std::endl;
	}
}

static void tryCreate(std::string const &name, int grade)
{
	try
	{
		Bureaucrat bureaucrat(name, grade);

		std::cout << bureaucrat << std::endl;
	}
	catch (std::exception const &e)
	{
		std::cout << name << ": " << e.what() << std::endl;
	}
}

static void tryIncrement(std::string const &name, int grade)
{
	try
	{
		Bureaucrat top(name, grade);
		top.incrementGrade();
	}
	catch (std::exception const &e)
	{
		std::cout << "Top increment: " << e.what() << std::endl;
	}
}

static void tryDecrement(std::string const &name, int grade)
{
	try
	{
		Bureaucrat bottom(name, grade);

		bottom.decrementGrade();
	}
	catch (std::exception const &e)
	{
		std::cout << "Bottom decrement: " << e.what() << std::endl;
	}
}

int main()
{
	TryTest("arthur", 75);
	tryCreate("Highest", 1);
	tryCreate("Too high", 0);
	tryCreate("Lowest", 150);
	tryCreate("Too low", 151);
	tryIncrement("Top", 1);
	tryDecrement("Bottom", 150);

	return (0);
}
