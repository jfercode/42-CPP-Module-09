# Static library name
NAME		= PmergeMe

# Compiler and flags
CXX			= c++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98

# Directories and files
SRC			= main.cpp source/PmergeMe.cpp
OBJ			= $(SRC:.cpp=.o)

all:	$(NAME)
$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean:	clean
	rm -rf $(NAME)

re:	fclean all

MIN     ?= 1
MAX     ?= 10000
COUNT   ?= 3000

random: 
	./$(NAME) $(shell shuf -i $(MIN)-$(MAX) -n $(COUNT) | tr '\n' ' ')

.PHONY: all clean fclean re random