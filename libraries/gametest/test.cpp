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
        Rectangle *rectangle = dynamic_cast<Rectangle *>(_objects[1].get());
        std::pair<int, int> pos = rectangle->getPos();
        if (input == Arcade::Input::LEFT)
            pos.first = (pos.first == 0) ? 0 : pos.first -1;
        if (input == Arcade::Input::RIGHT)
            pos.first += 1;
        if (input == Arcade::Input::UP)
            pos.second = (pos.second == 0) ? 0 : pos.second -1;
        if (input == Arcade::Input::DOWN)
            pos.second += 1;
        _objects[1] = std::make_shared<Arcade::Rectangle>(Arcade::Rectangle(pos, "test", Arcade::Color::WHITE, 1, 1));
        return _objects;
    }

    int GameLib::getScore()
    {
        return 0;
    }

    void GameLib::start()
    {
        _objects.push_back(std::make_shared<Arcade::Rectangle>(Arcade::Rectangle(std::make_pair(0, 0), "UWU", Arcade::Color::WHITE, 10, 10)));
        _objects.push_back(std::make_shared<Arcade::Rectangle>(Arcade::Rectangle(std::make_pair(2, 2), "test", Arcade::Color::WHITE, 1, 1)));
    }
}

extern "C" Arcade::IGameModule *entryGamePoint()
{
    return (new Arcade::GameLib());
}