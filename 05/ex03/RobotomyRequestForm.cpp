#include "RobotomyRequestForm.hpp"

#include <cstdlib>
#include <iostream>

RobotomyRequestForm::RobotomyRequestForm() : AForm("RobotomyRequestForm",
	72, 45), _target("default")
{
}

RobotomyRequestForm::RobotomyRequestForm(std::string const & target)
	: AForm("RobotomyRequestForm", 72, 45), _target(target)
{
}

RobotomyRequestForm::RobotomyRequestForm(RobotomyRequestForm const & other)
	: AForm(other), _target(other._target)
{
}

RobotomyRequestForm &	RobotomyRequestForm::operator=(
	RobotomyRequestForm const & other)
{
	if (this != &other)
	{
		AForm::operator=(other);
		_target = other._target;
	}
	return (*this);
}

RobotomyRequestForm::~RobotomyRequestForm()
{
}

void	RobotomyRequestForm::execute(Bureaucrat const & executor) const
{
	checkExecution(executor);
	std::cout << "Bzzzzzz... drilling noises..." << std::endl;
	if (std::rand() % 2 == 0)
		std::cout << _target << " has been robotomized successfully." << std::endl;
	else
		std::cout << "Robotomy failed for " << _target << "." << std::endl;
}
