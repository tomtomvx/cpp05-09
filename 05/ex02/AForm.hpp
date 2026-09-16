#ifndef AFORM_HPP
# define AFORM_HPP

# include <exception>
# include <iostream>
# include <string>

class Bureaucrat;

class AForm
{
private:
	static int const	_highestGrade = 1;
	static int const	_lowestGrade = 150;

	std::string const	_name;
	bool				_isSigned;
	int const			_signGrade;
	int const			_executeGrade;

	static void			checkGrade(int grade);

protected:
	AForm();
	AForm(std::string const & name, int signGrade, int executeGrade);
	void				checkExecution(Bureaucrat const & executor) const;

public:
	AForm(AForm const & other);
	AForm &				operator=(AForm const & other);
	virtual ~AForm();

	std::string const &	getName() const;
	bool				getIsSigned() const;
	int					getSignGrade() const;
	int					getExecuteGrade() const;

	void				beSigned(Bureaucrat const & bureaucrat);
	virtual void			execute(Bureaucrat const & executor) const = 0;

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

	class FormNotSignedException : public std::exception
	{
	public:
		virtual char const *	what() const throw();
	};
};

std::ostream &	operator<<(std::ostream & out, AForm const & form);

#endif
