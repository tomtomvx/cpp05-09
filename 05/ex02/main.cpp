#include "Bureaucrat.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

#include <cstdlib>
#include <ctime>
#include <iostream>

static void	testShrubbery(Bureaucrat const & gardener,
	Bureaucrat const & manager, ShrubberyCreationForm & shrubbery)
{
	std::cout << "--- Shrubbery ---" << std::endl;
	gardener.executeForm(shrubbery);
	gardener.signForm(shrubbery);
	gardener.executeForm(shrubbery);
	manager.executeForm(shrubbery);
}

static void	testRobotomy(Bureaucrat const & manager,
	Bureaucrat const & chief, RobotomyRequestForm & robotomy)
{
	std::cout << "--- Robotomy ---" << std::endl;
	manager.signForm(robotomy);
	manager.executeForm(robotomy);
	chief.executeForm(robotomy);
}

static void	testPardon(Bureaucrat const & manager,
	Bureaucrat const & chief, PresidentialPardonForm & pardon)
{
	std::cout << "--- Presidential pardon ---" << std::endl;
	manager.signForm(pardon);
	chief.signForm(pardon);
	manager.executeForm(pardon);
	chief.executeForm(pardon);
}

int	main()
{
	Bureaucrat	chief("Chief", 1);
	Bureaucrat	manager("Manager", 50);
	Bureaucrat	gardener("Gardener", 140);
	ShrubberyCreationForm	shrubbery("home");
	RobotomyRequestForm		robotomy("Bender");
	PresidentialPardonForm	pardon("Arthur Dent");

	std::srand(std::time(NULL));
	testShrubbery(gardener, manager, shrubbery);
	testRobotomy(manager, chief, robotomy);
	testPardon(manager, chief, pardon);
	return (0);
}
