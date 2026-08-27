/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucat.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomvaroux <tomvaroux@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 20:07:43 by tomvaroux         #+#    #+#             */
/*   Updated: 2026/08/05 22:41:19 by tomvaroux        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucat.hpp"

/* -------------------------------------------------------------------------- */
/*                              Private functions                             */
/* -------------------------------------------------------------------------- */

void	Bureaucrat::checkGrade(int const grade) const
{
	if (grade < 1)
		throw Bureaucrat::GradeTooHighException();
	else if (grade > 150)
		throw Bureaucrat::GradeTooHighException();
}

/* -------------------------------------------------------------------------- */
/*                          Constructors & operators                          */
/* -------------------------------------------------------------------------- */

Bureaucrat::Bureaucrat() : _name("default"), _grade(LOWEST_GRADE)
{
	std::cout << "Bureaucrat default constructor called." << std::endl;
}

// Bureaucrat::Bureaucrat(std::string const & name, int grade) : _name(name), _grade(grade)
// {
// 	std::cout << "Bureaucrat base constructor called." << std::endl;
// 	if (grade < 1)
// 		throw Bureaucrat::GradeTooHighException();
// 	else if (grade > 150)
// 		throw Bureaucrat::GradeTooHighException();
// }

Bureaucrat::Bureaucrat(std::string const & name, int grade) : _name(name)
{
	std::cout << "Bureaucrat base constructor called." << std::endl;
	checkGrade(grade);
	_grade = grade;
}

Bureaucrat::Bureaucrat(Bureaucrat const & other) : _name(other.getName())
{
	std::cout << "Bureaucrat copy constructor called." << std::endl;
	*this = other;
}

Bureaucrat & Bureaucrat::operator=(Bureaucrat const & other)
{
	if (this != &other)
		this->_grade = other._grade;
	return (*this);
}

Bureaucrat::~Bureaucrat()
{
	std::cout << "Bureaucrat default destructor called." << std::endl;
}

std::ostream & operator<<(std::ostream & os, Bureaucrat const & bureaucrat)
{
	os << bureaucrat.getName()
		<< ", bureaucrat grade "
		<< bureaucrat.getGrade()
		<< ".";
	return os;
}

/* -------------------------------------------------------------------------- */
/*                              Geteurs & seteurs                             */
/* -------------------------------------------------------------------------- */

std::string const & Bureaucrat::getName() const
{
	return (_name);
}

int Bureaucrat::getGrade() const
{
	return (_grade);
}

/* -------------------------------------------------------------------------- */
/*                              Members functions                             */
/* -------------------------------------------------------------------------- */

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


