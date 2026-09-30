#ifndef INTERN_HPP
# define INTERN_HPP

# include <string>

class AForm;

class Intern
{
private:
	typedef AForm *	(Intern::*FormCreator)(std::string const & target) const;

	AForm *	createShrubberyCreationForm(std::string const & target) const;
	AForm *	createRobotomyRequestForm(std::string const & target) const;
	AForm *	createPresidentialPardonForm(std::string const & target) const;

public:
	Intern();
	Intern(Intern const & other);
	Intern &	operator=(Intern const & other);
	~Intern();

	AForm *	makeForm(std::string const & name,
				std::string const & target) const;
};

#endif
