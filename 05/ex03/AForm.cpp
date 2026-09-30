#include "AForm.hpp"
#include "Bureaucrat.hpp"

AForm::AForm()
	: _name("default"), _isSigned(false), _signGrade(_lowestGrade),
	_executeGrade(_lowestGrade)
{
}

AForm::AForm(std::string const & name, int signGrade, int executeGrade)
	: _name(name), _isSigned(false), _signGrade(signGrade),
	_executeGrade(executeGrade)
{
	checkGrade(_signGrade);
	checkGrade(_executeGrade);
}

AForm::AForm(AForm const & other)
	: _name(other._name), _isSigned(other._isSigned),
	_signGrade(other._signGrade), _executeGrade(other._executeGrade)
{
}

AForm &	AForm::operator=(AForm const & other)
{
	if (this != &other)
		_isSigned = other._isSigned;
	return (*this);
}

AForm::~AForm()
{
}

std::string const &	AForm::getName() const
{
	return (_name);
}

bool	AForm::getIsSigned() const
{
	return (_isSigned);
}

int	AForm::getSignGrade() const
{
	return (_signGrade);
}

int	AForm::getExecuteGrade() const
{
	return (_executeGrade);
}

void	AForm::beSigned(Bureaucrat const & bureaucrat)
{
	if (bureaucrat.getGrade() > _signGrade)
		throw (GradeTooLowException());
	_isSigned = true;
}

void	AForm::checkExecution(Bureaucrat const & executor) const
{
	if (!_isSigned)
		throw (FormNotSignedException());
	if (executor.getGrade() > _executeGrade)
		throw (GradeTooLowException());
}

void	AForm::checkGrade(int grade)
{
	if (grade < _highestGrade)
		throw (GradeTooHighException());
	if (grade > _lowestGrade)
		throw (GradeTooLowException());
}

char const *	AForm::GradeTooHighException::what() const throw()
{
	return ("AForm grade is too high");
}

char const *	AForm::GradeTooLowException::what() const throw()
{
	return ("AForm grade is too low");
}

char const *	AForm::FormNotSignedException::what() const throw()
{
	return ("AForm is not signed");
}

std::ostream &	operator<<(std::ostream & out, AForm const & form)
{
	out << form.getName() << ", form is ";
	if (form.getIsSigned())
		out << "signed";
	else
		out << "not signed";
	out << ", sign grade " << form.getSignGrade()
		<< ", execute grade " << form.getExecuteGrade() << ".";
	return (out);
}
