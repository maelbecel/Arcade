##
## EPITECH PROJECT, 2023
## Arcade
## File description:
## Makefile
##

SRC = ./main.cpp

OBJ = $(SRC:.cpp=.o)

NAME = arcade

CXXFLAGS = -W -Wall -Wextra -Werror -ldl

CXX = g++

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.cpp .o:
	gcc -o $@ $< $(CXXFLAGS)
