/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomvaroux <tomvaroux@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 00:00:00 by tomvaroux         #+#    #+#             */
/*   Updated: 2026/09/13 00:00:00 by tomvaroux        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORM_HPP
# define FORM_HPP

# include <exception>
# include <iostream>
# include <string>

class Bureaucrat;

class Form
{
private:
	static int const	_highestGrade = 1;
	static int const	_lowestGrade = 150;

	std::string const	_name;
	bool				_isSigned;
	int const			_signGrade;
	int const			_executeGrade;

	static void			checkGrade(int grade);

public:
	Form();
	Form(std::string const & name, int signGrade, int executeGrade);
	Form(Form const & other);
	Form &				operator=(Form const & other);
	~Form();

	std::string const &	getName() const;
	bool				getIsSigned() const;
	int					getSignGrade() const;
	int					getExecuteGrade() const;

	void				beSigned(Bureaucrat const & bureaucrat);

	class GradeTooHighException : public std::exception
	{
	public:
		virtual char const *	what() const throw();
	};

	class GradeTooLowException : public std::exception
	{
	public:
		virtual char const *	what() const throw();
	};
};

std::ostream &			operator<<(std::ostream & out, Form const & form);

#endif
