#ifndef BUREAUCAT_HPP
# define BUREAUCAT_HPP

# include <string>		// std::string
# include <iostream>	// std::ostream, operator<<
# include <exception>	// std::exception

# define HIGHEST_GRADE 1
# define LOWEST_GRADE 150


class Bureaucrat
{
private:
	const std::string	_name;
	int					_grade;

	void	checkGrade(int const grade) const;

public:
	Bureaucrat();
	Bureaucrat(std::string const & name, int grade);
	Bureaucrat(Bureaucrat const & other);
	Bureaucrat & operator=(Bureaucrat const & other);
	~Bureaucrat();

	std::string const &	getName() const;
	int					getGrade() const;

	void	incrementGrade();
	void	decrementGrade();

	class GradeTooHighException : public std::exception
	{
	public:
		virtual const char *	what() const throw();
	};

	class GradeTooLowException : public std::exception
	{
	public:
		virtual const char *	what() const throw();
	};
};

std::ostream & operator<<(std::ostream & os, Bureaucrat const & bureaucrat);

#endif
