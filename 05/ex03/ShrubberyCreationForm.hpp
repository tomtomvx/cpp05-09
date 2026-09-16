#ifndef SHRUBBERYCREATIONFORM_HPP
# define SHRUBBERYCREATIONFORM_HPP

# include "AForm.hpp"

class ShrubberyCreationForm : public AForm
{
private:
	std::string	_target;

public:
	ShrubberyCreationForm();
	ShrubberyCreationForm(std::string const & target);
	ShrubberyCreationForm(ShrubberyCreationForm const & other);
	ShrubberyCreationForm &	operator=(ShrubberyCreationForm const & other);
	virtual ~ShrubberyCreationForm();

	virtual void		execute(Bureaucrat const & executor) const;
};

#endif
