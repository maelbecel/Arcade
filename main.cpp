/*
** EPITECH PROJECT, 2023
** Arcade
** File description:
** main
*/

#include <dlfcn.h>
#include <iostream>
#include <time.h>
#include "Input.hpp"
#include "IDisplayModule.hpp"
#include "./core/DLLoader.hpp"
#include "./core/Core.hpp"

using namespace Arcade;

int main(int ac, char **av)
{
    if (ac != 2)
        return (84);
    DLLoader<IDisplayModule> loader;
    DLLoader<IGameModule> game;
    Core core(av[1]);
    srand(time(NULL));

    core.setGamePath("lib/libarcade_snake.so");

    try {
        core.setDisplay(loader.load(core.getDisplayPath()));
        core.setGame(game.load(core.getGamePath()));
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return (84);
    }

    core.mainLoop();
    return (0);
}
