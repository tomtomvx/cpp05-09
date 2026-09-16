#include "Bureaucrat.hpp"

#include <iostream>

static void	tryCreate(std::string const & name, int grade)
{
	try
	{
		Bureaucrat	bureaucrat(name, grade);

		std::cout << bureaucrat << std::endl;
	}
	catch (std::exception const & e)
	{
		std::cout << name << ": " << e.what() << std::endl;
	}
}

int	main()
{
	Bureaucrat	arthur("Arthur", 75);

	std::cout << arthur << std::endl;
	arthur.incrementGrade();
	std::cout << arthur << std::endl;
	arthur.decrementGrade();
	std::cout << arthur << std::endl;

	tryCreate("Highest", 1);
	tryCreate("Too high", 0);
	tryCreate("Lowest", 150);
	tryCreate("Too low", 151);

	try
	{
		Bureaucrat	top("Top", 1);

		top.incrementGrade();
	}
	catch (std::exception const & e)
	{
		std::cout << "Top increment: " << e.what() << std::endl;
	}

	try
	{
		Bureaucrat	bottom("Bottom", 150);

		bottom.decrementGrade();
	}
	catch (std::exception const & e)
	{
		std::cout << "Bottom decrement: " << e.what() << std::endl;
	}
	return (0);
}
