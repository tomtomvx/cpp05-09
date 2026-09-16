#include "Bureaucrat.hpp"
#include "Form.hpp"

#include <iostream>

static void	tryCreateForm(std::string const & name, int signGrade,
	int executeGrade)
{
	try
	{
		Form	form(name, signGrade, executeGrade);

		std::cout << form << std::endl;
	}
	catch (std::exception const & e)
	{
		std::cout << name << ": " << e.what() << std::endl;
	}
}

int	main()
{
	Bureaucrat	boss("Boss", 1);
	Bureaucrat	intern("Intern", 150);
	Form		important("Important paper", 50, 25);
	Form		easy("Easy paper", 150, 150);

	std::cout << boss << std::endl;
	std::cout << intern << std::endl;
	std::cout << important << std::endl;
	std::cout << easy << std::endl;

	intern.signForm(important);
	std::cout << important << std::endl;
	boss.signForm(important);
	std::cout << important << std::endl;
	intern.signForm(easy);
	std::cout << easy << std::endl;

	tryCreateForm("Too high sign", 0, 100);
	tryCreateForm("Too high execute", 100, 0);
	tryCreateForm("Too low sign", 151, 100);
	tryCreateForm("Too low execute", 100, 151);
	return (0);
}
