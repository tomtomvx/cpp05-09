#include "Intern.hpp"

#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

#include <iostream>

Intern::Intern()
{
}

Intern::Intern(Intern const & other)
{
	(void)other;
}

Intern &	Intern::operator=(Intern const & other)
{
	(void)other;
	return (*this);
}

Intern::~Intern()
{
}

AForm *	Intern::createShrubberyCreationForm(std::string const & target) const
{
	return (new ShrubberyCreationForm(target));
}

AForm *	Intern::createRobotomyRequestForm(std::string const & target) const
{
	return (new RobotomyRequestForm(target));
}

AForm *	Intern::createPresidentialPardonForm(std::string const & target) const
{
	return (new PresidentialPardonForm(target));
}

AForm *	Intern::makeForm(std::string const & name,
	std::string const & target) const
{
	static std::string const	formNames[] = {
		"shrubbery creation", "robotomy request", "presidential pardon"
	};
	static FormCreator const	formCreators[] = {
		&Intern::createShrubberyCreationForm,
		&Intern::createRobotomyRequestForm,
		&Intern::createPresidentialPardonForm
	};
	int						index;

	index = 0;
	while (index < 3)
	{
		if (name == formNames[index])
		{
			std::cout << "Intern creates " << name << std::endl;
			return ((this->*formCreators[index])(target));
		}
		++index;
	}
	std::cout << "Intern cannot create " << name << std::endl;
	return (NULL);
}
