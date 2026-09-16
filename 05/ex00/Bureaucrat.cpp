#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat() : _name("default"), _grade(_lowestGrade)
{
}

Bureaucrat::Bureaucrat(std::string const & name, int grade) : _name(name)
{
	checkGrade(grade);
	_grade = grade;
}

Bureaucrat::Bureaucrat(Bureaucrat const & other)
	: _name(other._name), _grade(other._grade)
{
}

Bureaucrat &	Bureaucrat::operator=(Bureaucrat const & other)
{
	if (this != &other)
		_grade = other._grade;
	return (*this);
}

Bureaucrat::~Bureaucrat()
{
}

std::string const &	Bureaucrat::getName() const
{
	return (_name);
}

int	Bureaucrat::getGrade() const
{
	return (_grade);
}

void	Bureaucrat::incrementGrade()
{
	checkGrade(_grade - 1);
	--_grade;
}

void	Bureaucrat::decrementGrade()
{
	checkGrade(_grade + 1);
	++_grade;
}

void	Bureaucrat::checkGrade(int grade)
{
	if (grade < _highestGrade)
		throw (GradeTooHighException());
	if (grade > _lowestGrade)
		throw (GradeTooLowException());
}

char const *	Bureaucrat::GradeTooHighException::what() const throw()
{
	return ("grade is too high");
}

char const *	Bureaucrat::GradeTooLowException::what() const throw()
{
	return ("grade is too low");
}

std::ostream &	operator<<(std::ostream & out, Bureaucrat const & bureaucrat)
{
	out << bureaucrat.getName() << ", bureaucrat grade "
		<< bureaucrat.getGrade() << ".";
	return (out);
}
