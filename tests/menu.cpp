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

#include "../libraries/menu/menu.hpp"

Test(Menu, loop)
{
    Arcade::Menu menu;
    menu.start();
    std::vector<std::shared_ptr<Arcade::IObject>> objects = menu.loop(Arcade::Input::NONE);
}

Test(Menu, getScore)
{
    Arcade::Menu menu;
    menu.start();
    std::cout << "Score : " << menu.getScore() << std::endl;
}

Test(Menu, start)
{
    Arcade::Menu menu;
    menu.start();
}