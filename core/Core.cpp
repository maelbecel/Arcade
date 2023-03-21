/*
** EPITECH PROJECT, 2023
** Arcade
** File description:
** Core
*/

#include "Core.hpp"
#include <unistd.h>

namespace Arcade {
    void Core::mainLoop()
    {
        std::vector<std::shared_ptr<Arcade::IObject>> objects;
        _game->start();
        while (true) {
            _display->clear();
            objects = _game->loop(_display->getLastInput());
            for (auto &object : objects) {
                _display->draw(object);
            }
            _display->refresh();
            sleep(1);
        }
    }
}