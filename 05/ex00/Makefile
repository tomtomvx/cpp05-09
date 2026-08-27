NAME		=	a.out
# NAME		=	Bureaucat


CXX			=	c++
CXXFLAGS	=	-Wall -Wextra -Werror -std=c++98 -pedantic -MMD -MP
# CXXFLAGS	=	-Wall -Wextra -Werror -std=c++98 -MMD -MP


SRCS		=	$(wildcard *.cpp)
OBJS		=	$(SRCS:%.cpp=%.o)
DEPS		=	$(SRCS:%.cpp=%.d)

HEADERS		=	$(wildcard *.hpp)
# DS			=	$(wildcard *.d)

RM			=	rm -rf

MAKE		=	make
MAKEFLAGS	+=	--no-print-directory


all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(DEPS)

clean:
	@$(RM) $(OBJS) $(DEPS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

run:
	$(MAKE) re
	./$(NAME)
	$(MAKE) fclean

test: run

.PHONY: all clean fclean re test
