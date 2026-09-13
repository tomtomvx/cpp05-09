/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomvaroux <tomvaroux@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 00:00:00 by tomvaroux         #+#    #+#             */
/*   Updated: 2026/09/13 00:00:00 by tomvaroux        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"
#include "Bureaucrat.hpp"

Form::Form()
	: _name("default"), _isSigned(false), _signGrade(_lowestGrade),
	_executeGrade(_lowestGrade)
{
}

Form::Form(std::string const & name, int signGrade, int executeGrade)
	: _name(name), _isSigned(false), _signGrade(signGrade),
	_executeGrade(executeGrade)
{
	checkGrade(_signGrade);
	checkGrade(_executeGrade);
}

Form::Form(Form const & other)
	: _name(other._name), _isSigned(other._isSigned),
	_signGrade(other._signGrade), _executeGrade(other._executeGrade)
{
}

Form &	Form::operator=(Form const & other)
{
	if (this != &other)
		_isSigned = other._isSigned;
	return (*this);
}

Form::~Form()
{
}

std::string const &	Form::getName() const
{
	return (_name);
}

bool	Form::getIsSigned() const
{
	return (_isSigned);
}

int	Form::getSignGrade() const
{
	return (_signGrade);
}

int	Form::getExecuteGrade() const
{
	return (_executeGrade);
}

void	Form::beSigned(Bureaucrat const & bureaucrat)
{
	if (bureaucrat.getGrade() > _signGrade)
		throw (GradeTooLowException());
	_isSigned = true;
}

void	Form::checkGrade(int grade)
{
	if (grade < _highestGrade)
		throw (GradeTooHighException());
	if (grade > _lowestGrade)
		throw (GradeTooLowException());
}

char const *	Form::GradeTooHighException::what() const throw()
{
	return ("grade is too high");
}

char const *	Form::GradeTooLowException::what() const throw()
{
	return ("grade is too low");
}

std::ostream &	operator<<(std::ostream & out, Form const & form)
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
