NAME		=	Intern

CXX			=	c++
CXXFLAGS	=	-Wall -Wextra -Werror -std=c++98 -pedantic -MMD -MP

SRCS		=	main.cpp Bureaucrat.cpp AForm.cpp Intern.cpp ShrubberyCreationForm.cpp RobotomyRequestForm.cpp PresidentialPardonForm.cpp
OBJS		=	$(SRCS:.cpp=.o)
DEPS		=	$(SRCS:.cpp=.d)

RM			=	rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(DEPS)

clean:
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

run: re
	./$(NAME)
	$(MAKE) fclean

test: run

.PHONY: all clean fclean re run test
