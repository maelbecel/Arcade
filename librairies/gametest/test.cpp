/*
** EPITECH PROJECT, 2023
** Arcade
** File description:
** test
*/

#include "test.hpp"

namespace Arcade {
    std::vector<std::shared_ptr<Arcade::IObject>> GameLib::loop(Arcade::Input input)
    {
        Rectangle *rectangle = dynamic_cast<Rectangle *>(_objects[0].get());
        std::pair<int, int> pos = rectangle->getPos();
        if (input == Arcade::Input::LEFT)
            pos.first -= 1;
        if (input == Arcade::Input::RIGHT)
            pos.first += 1;
        if (input == Arcade::Input::UP)
            pos.second -= 1;
        if (input == Arcade::Input::DOWN)
            pos.second += 1;
        _objects[0] = std::make_shared<Arcade::Rectangle>(Arcade::Rectangle(pos, "test", Arcade::Color::RED, 10, 10));
        return _objects;
    }

    int GameLib::getScore()
    {
        return 0;
    }

    void GameLib::start()
    {
        _objects.push_back(std::make_shared<Arcade::Rectangle>(Arcade::Rectangle(std::make_pair(0, 0), "test", Arcade::Color::RED, 10, 10)));
        _objects.push_back(std::make_shared<Arcade::Rectangle>(Arcade::Rectangle(std::make_pair(10, 10), "UWU", Arcade::Color::RED, 10, 10)));
    }
}

extern "C" Arcade::IGameModule *entryPoint()
{
    return (new Arcade::GameLib());
}