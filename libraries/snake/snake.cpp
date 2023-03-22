/*
** EPITECH PROJECT, 2023
** Arcade
** File description:
** test
*/

#include "snake.hpp"

namespace Arcade {
    std::vector<std::shared_ptr<Arcade::IObject>> Snake::loop(Arcade::Input input)
    {
        std::vector<std::shared_ptr<Arcade::IObject>> objects;
        if (input != Arcade::Input::UNKNOWN) {
            _input = input;
        }
        if (_input == Arcade::Input::LEFT && _player._direction != Arcade::Input::RIGHT)
            _player._direction = Arcade::Input::LEFT;
        if (_input == Arcade::Input::RIGHT && _player._direction != Arcade::Input::LEFT)
            _player._direction = Arcade::Input::RIGHT;
        if (_input == Arcade::Input::UP && _player._direction != Arcade::Input::DOWN)
            _player._direction = Arcade::Input::UP;
        if (_input == Arcade::Input::DOWN && _player._direction != Arcade::Input::UP)
            _player._direction = Arcade::Input::DOWN;
        if (_player.isEating(_apple)) {
            _player.eat();
            _apple = getNewPos();
        }
        objects.push_back(std::make_shared<Arcade::Circle>(std::make_pair(_apple.first, _apple.second), "apple", Arcade::Color::RED, 1));
        _player.move();
        if (_player.isDead())
            start();
        for (auto &body : _player._body)
            objects.push_back(std::make_shared<Arcade::Rectangle>(std::make_pair(body.getPos().first, body.getPos().second), "snake", Arcade::Color::GREEN, 1, 1));
        return objects;
    }

    int Snake::getScore()
    {
        return 0;
    }

    void Snake::start()
    {
        _score = 0;
        _input = Arcade::Input::RIGHT;
        _player._body.clear();
        _player._body.push_back(Arcade::Rectangle(std::make_pair(4, 4), "snake", Arcade::Color::GREEN, 1, 1));
        _player._body.push_back(Arcade::Rectangle(std::make_pair(3, 4), "snake", Arcade::Color::GREEN, 1, 1));
        _player._body.push_back(Arcade::Rectangle(std::make_pair(2, 4), "snake", Arcade::Color::GREEN, 1, 1));
        _player._body.push_back(Arcade::Rectangle(std::make_pair(1, 4), "snake", Arcade::Color::GREEN, 1, 1));
        _player._direction = Arcade::Input::RIGHT;
        _apple = getNewPos();
    }

    std::pair<int, int> Snake::getNewPos()
    {
        std::pair<int, int> pos = std::make_pair(rand() % 16, rand() % 12);
        if (pos == _apple)
            return getNewPos();
        for (auto &body : _player._body) {
            if (body.getPos() == pos)
                return getNewPos();
        }
        return pos;
    }

    void Snake::Player::move()
    {
        std::vector<Arcade::Rectangle> body;
        for (std::size_t i = 0; i < _body.size(); i++) {
            if (i == 0) {
                if (_direction == Arcade::Input::LEFT)
                    body.push_back(Arcade::Rectangle(std::make_pair(_body[i].getPos().first - 1, _body[i].getPos().second), "snake", Arcade::Color::GREEN, 1, 1));
                if (_direction == Arcade::Input::RIGHT)
                    body.push_back(Arcade::Rectangle(std::make_pair(_body[i].getPos().first + 1, _body[i].getPos().second), "snake", Arcade::Color::GREEN, 1, 1));
                if (_direction == Arcade::Input::UP)
                    body.push_back(Arcade::Rectangle(std::make_pair(_body[i].getPos().first, _body[i].getPos().second - 1), "snake", Arcade::Color::GREEN, 1, 1));
                if (_direction == Arcade::Input::DOWN)
                    body.push_back(Arcade::Rectangle(std::make_pair(_body[i].getPos().first, _body[i].getPos().second + 1), "snake", Arcade::Color::GREEN, 1, 1));
            } else {
                body.push_back(Arcade::Rectangle(std::make_pair(_body[i - 1].getPos().first, _body[i - 1].getPos().second), "snake", Arcade::Color::GREEN, 1, 1));
            }
        }
        _body = body;
    }

    bool Snake::Player::isDead()
    {
        for (std::size_t i = 1; i < _body.size(); i++) {
            if (_body[i].getPos() == _body[0].getPos())
                return true;
        }
        return false;
    }

    void Snake::Player::eat()
    {
        _body.push_back(Arcade::Rectangle(std::make_pair(_body[_body.size() - 1].getPos().first, _body[_body.size() - 1].getPos().second), "snake", Arcade::Color::GREEN, 10, 10));
    }

    bool Snake::Player::isEating(std::pair<int, int> apple)
    {
        if (_body[0].getPos() == apple)
            return true;
        return false;
    }
}

extern "C" Arcade::IGameModule *entryPoint()
{
    return (new Arcade::Snake());
}