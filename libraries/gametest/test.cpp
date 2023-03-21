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
        _objects.push_back(std::make_shared<Arcade::Rectangle>(Arcade::Rectangle(std::make_pair(100, 10), "UWU", Arcade::Color::BLUE, 100, 100)));
        _objects.push_back(std::make_shared<Arcade::Circle>(Arcade::Circle(std::make_pair(400, 10), "OwO", Arcade::Color::GREEN, 10)));
        _objects.push_back(std::make_shared<Arcade::Text>(Arcade::Text(std::make_pair(400, 200), "UwU", Arcade::Color::BLACK, 100)));
    }
}

extern "C" Arcade::IGameModule *entryPoint()
{
    return (new Arcade::GameLib());
}