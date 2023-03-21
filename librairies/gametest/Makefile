##
## EPITECH PROJECT, 2023
## Arcade
## File description:
## Makefile
##

SRC	=	./test.cpp

OBJ	=	$(SRC:.cpp=.o)

NAME	=	libgame.so

CXXFLAGS	=	-W -Wall -Wextra -fPIC -g

CXX	=	g++

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CXX) -shared -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all
