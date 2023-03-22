/*
** EPITECH PROJECT, 2023
** Arcade
** File description:
** Core
*/

#include "Core.hpp"
#include <unistd.h>

namespace Arcade {
    /**
     * It clears the display, gets the objects from the game, draws them on the
     * display and refreshes the display
     */
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