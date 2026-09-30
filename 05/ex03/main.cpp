#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include "Intern.hpp"

#include <cstdlib>
#include <ctime>

static void	testForm(Bureaucrat const & bureaucrat, AForm * form)
{
	if (form == NULL)
		return ;
	bureaucrat.signForm(*form);
	bureaucrat.executeForm(*form);
	delete form;
}

int	main()
{
	Bureaucrat	chief("Chief", 1);
	Intern		intern;
	AForm		*form;

	std::srand(std::time(NULL));
	form = intern.makeForm("shrubbery creation", "garden");
	testForm(chief, form);
	form = intern.makeForm("robotomy request", "Bender");
	testForm(chief, form);
	form = intern.makeForm("presidential pardon", "Arthur Dent");
	testForm(chief, form);
	form = intern.makeForm("coffee request", "office");
	testForm(chief, form);
	return (0);
}
