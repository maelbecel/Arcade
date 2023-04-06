##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Makefile for unit_tests
##

NAME         =		    unit_tests

CXXFLAGS       +=         -Wall -Wextra -pedantic

SRC          =         core/Core.cpp \
					   core/Score.cpp \

TESTS        =         tests/core.cpp

OBJ          =	        $(SRC:.c=.o)

TEMPFILES    =         *~ *vgcore* #*#

RM           =         rm -f

ECHO         =         /bin/echo -e
DEFAULT      =         "\033[00m"
BOLD         =         "\e[1m"
RED          =         "\e[31m"
GREEN        =         "\e[32m"
LIGHT_BLUE   =         "\e[94m"
WHITE        =         "\e[1;37m"

tests_run:
			@g++ -o unit_tests -Wall -Wextra $(SRC) $(TESTS) -lcriterion -ldl \
			--coverage
			@./$(NAME)
fclean:		clean
			@$(RM) $(NAME) *.gcno *.gcda
			@($(ECHO) $(BOLD) $(GREEN)✓$(LIGHT_BLUE)" Fclean SRC "$(DEFAULT))
coverage:
			@gcovr -r . --exclude tests/
			@gcovr -b --exclude tests/

.PHONY: all re clean fclean debug