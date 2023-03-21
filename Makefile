##
## EPITECH PROJECT, 2023
## Arcade
## File description:
## Makefile
##

SRC = 	./main.cpp \
		./core/Core.cpp \

OBJ = $(SRC:.cpp=.o)

NAME = arcade

CXXFLAGS = -W -Wall -Wextra -Werror -ldl

CXX = g++

all: $(NAME) games graphicals

$(NAME): $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(CXXFLAGS)

core: $(NAME)

games:
	make -C libraries/gametest/

graphicals:
	make -C libraries/libtest/

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

debug: CXXFLAGS += -g
debug: all

re: fclean all

.cpp .o:
	gcc -o $@ $< $(CXXFLAGS)
