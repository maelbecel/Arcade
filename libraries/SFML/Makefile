##
## EPITECH PROJECT, 2023
## Arcade
## File description:
## Makefile
##

SRC	=	./sfml.cpp

OBJ	=	$(SRC:.cpp=.o)

NAME	=	arcade_sfml.so

CXXFLAGS	=	-W -Wall -Wextra -fPIC -lsfml-graphics -lsfml-window -lsfml-system

CXX	=	g++

all:	$(NAME)

$(NAME):	$(OBJ)
	gcc -shared -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

debug:	CXXFLAGS += -g
debug:  all

re:	fclean all

%.o:	%.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)

.PHONY: all clean fclean re debug
