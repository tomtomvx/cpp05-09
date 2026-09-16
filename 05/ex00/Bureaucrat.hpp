#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

# include <exception>
# include <iostream>
# include <string>

class Bureaucrat
{
private:
	static int const	_highestGrade = 1;
	static int const	_lowestGrade = 150;

	std::string const	_name;
	int					_grade;

	static void			checkGrade(int grade);

public:
	Bureaucrat();
	Bureaucrat(std::string const & name, int grade);
	Bureaucrat(Bureaucrat const & other);
	Bureaucrat &		operator=(Bureaucrat const & other);
	~Bureaucrat();

	std::string const &	getName() const;
	int					getGrade() const;

	void				incrementGrade();
	void				decrementGrade();

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

std::ostream &			operator<<(std::ostream & out,
							Bureaucrat const & bureaucrat);

#endif
