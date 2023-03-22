/*
** EPITECH PROJECT, 2023
** Arcade
** File description:
** main
*/

#include <dlfcn.h>
#include "Input.hpp"
#include <iostream>
#include "IDisplayModule.hpp"
#include "./core/DLLoader.hpp"
#include "./core/Core.hpp"

using namespace Arcade;

int main(int ac, char **av)
{
    if (ac != 2)
        return (84);
    Core core(av[1]);

    core.setGamePath("lib/libarcade_snake.so");

    try {
        core.setDisplay(core.getDisplayLoader().load(core.getDisplayPath()));
        core.setGame(core.getGameLoader().load(core.getGamePath()));
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return (84);
    }

    core.mainLoop();
    return (0);
}
