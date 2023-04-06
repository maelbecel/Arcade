/*
** EPITECH PROJECT, 2023
** Arcade
** File description:
** Unit tests
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <fstream>
#include <iostream>
#include <string>

#include "../core/Score.hpp"
#include "../core/Core.hpp"
#include "../core/DLLoader.hpp"

Test(Score, getScore)
{
    Arcade::Score score;
    std::cout << score.getScore("Pacman") << std::endl;
    std::cout << score.getScore("arcade_snake.so") << std::endl;
}

Test(Score, setScore)
{
    Arcade::Score score;
    score.setScore("Pacman", 100, "test");
    cr_assert_eq(score.getScore("Pacman"), 100);
}

Test(Score, getCurrentPlayer)
{
    Arcade::Score score;
    std::cout << score.getCurrentPlayer() << std::endl;
}

Test(Score, setCurrentPlayer)
{
    Arcade::Score score;
    score.setCurrentPlayer("test");
    cr_assert_eq(score.getCurrentPlayer(), "test");
}

Test(Score, getBestPlayer)
{
    Arcade::Score score;
    std::cout << score.getBestPlayer("Pacman") << std::endl;
    std::cout << score.getBestPlayer("arcade_snake.so") << std::endl;
}

Test(Core, initCore)
{
    try {
        Arcade::Core core("jej");
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    Arcade::Core core("lib/lib_arcade_sfml.so");
}



