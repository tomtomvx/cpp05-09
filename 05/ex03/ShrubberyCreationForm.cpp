#include "ShrubberyCreationForm.hpp"

#include <fstream>

ShrubberyCreationForm::ShrubberyCreationForm() : AForm("ShrubberyCreationForm",
	145, 137), _target("default")
{
}

ShrubberyCreationForm::ShrubberyCreationForm(std::string const & target)
	: AForm("ShrubberyCreationForm", 145, 137), _target(target)
{
}

ShrubberyCreationForm::ShrubberyCreationForm(ShrubberyCreationForm const & other)
	: AForm(other), _target(other._target)
{
}

ShrubberyCreationForm &	ShrubberyCreationForm::operator=(
	ShrubberyCreationForm const & other)
{
	if (this != &other)
	{
		AForm::operator=(other);
		_target = other._target;
	}
	return (*this);
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{
}

void	ShrubberyCreationForm::execute(Bureaucrat const & executor) const
{
	std::ofstream	file;

	checkExecution(executor);
	file.open((_target + "_shrubbery").c_str());
	if (!file)
	{
		std::cerr << "couldn't create " << _target << "_shrubbery" << std::endl;
		return ;
	}
	file << "       _-_" << std::endl;
	file << "    /~~   ~~\\\\" << std::endl;
	file << " /~~         ~~\\\\" << std::endl;
	file << "{               }" << std::endl;
	file << " \\\\  _-     -_  /" << std::endl;
	file << "   ~  \\\\\\\\ //  ~" << std::endl;
	file << "_- -   | | _- _" << std::endl;
	file << "  _ -  | |   -_" << std::endl;
	file << "      // \\\\\\\\" << std::endl;
}
