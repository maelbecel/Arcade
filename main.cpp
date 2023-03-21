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
    DLLoader<IDisplayModule> loader;
    DLLoader<IGameModule> game;
    Core core(av[1]);

    core.setGamePath("libraries/gametest/libgame.so");

    try {
        core.setDisplay(loader.load(core.getDisplayPath()));
        core.setGame(game.load(core.getGamePath()));
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return (84);
    }

    core.mainLoop();

    std::shared_ptr<IObject> text = std::make_shared<Text>(std::make_pair(10, 0), "Hello World", Color::WHITE, 20);
    std::shared_ptr<IObject> circle = std::make_shared<Circle>(std::make_pair(0, 0), "test", Color::WHITE, 10);
    std::shared_ptr<Arcade::IObject> rectangle = std::make_shared<Arcade::Rectangle>(std::make_pair(0, 0), "test", Arcade::Color::WHITE, 10, 10);
    core.getDisplay()->draw(rectangle);
    core.getDisplay()->draw(circle);
    core.getDisplay()->draw(text);
    return (0);
}
