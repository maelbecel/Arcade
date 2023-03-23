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
        for (auto &line : _map) {
            for (auto &wall : line)
                objects.push_back(std::make_shared<Arcade::Rectangle>(std::make_pair(wall.getPos().first, wall.getPos().second), wall.getTexture(), wall.getColor(), 1, 1));
        }
        _player.move();
        if (_player.isDead())
            start();
        if (_player.isEating(_apple)) {
            _player.eat();
            _apple = getNewPos();
            _score++;
        }
        if (_player.win()) {
            std::cout << "You win" << std::endl;
            start();
        }
        objects.push_back(std::make_shared<Arcade::Circle>(std::make_pair(_apple.first, _apple.second), "../assets/apple.png", Arcade::Color::RED, 1));
        for (auto &body : _player._body)
            objects.push_back(std::make_shared<Arcade::Rectangle>(std::make_pair(body.getPos().first, body.getPos().second), "snake", Arcade::Color::GREEN, 1, 1));
        objects.push_back(std::make_shared<Arcade::Text>(std::make_pair(0, 0), "Score: " + std::to_string(_score), Arcade::Color::BLACK, 1));
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
        _player._body.push_back(Arcade::Rectangle(std::make_pair(1, 1), "snake", Arcade::Color::GREEN, 1, 1));
        _player._body.push_back(Arcade::Rectangle(std::make_pair(2, 1), "snake", Arcade::Color::GREEN, 1, 1));
        _player._body.push_back(Arcade::Rectangle(std::make_pair(3, 1), "snake", Arcade::Color::GREEN, 1, 1));
        _player._body.push_back(Arcade::Rectangle(std::make_pair(4, 1), "snake", Arcade::Color::GREEN, 1, 1));
        _player._direction = Arcade::Input::RIGHT;
        _apple = getNewPos();
        initMap();
    }

    std::pair<int, int> Snake::getNewPos()
    {
        std::pair<int, int> pos = std::make_pair(rand() % (SIZE_MAP_X - 1) + 1, rand() % (SIZE_MAP_Y - 1) + 1);
        if (pos == _apple)
            return getNewPos();
        for (auto &body : _player._body) {
            if (body.getPos() == pos)
                return getNewPos();
        }
        return pos;
    }

    void Snake::initMap()
    {
        _map.clear();
        for (int i = 0; i < SIZE_MAP_Y + 1; i++) {
            std::vector<Arcade::Rectangle> line;
            _map.push_back(line);
        }
        for (int i = 0; i < SIZE_MAP_X + 1; i++)
            _map[0].push_back(Arcade::Rectangle(std::make_pair(i, 0), "wall", Arcade::Color::WHITE, 1, 1));
        for (int i = 1; i < SIZE_MAP_Y; i++) {
            _map[i].push_back(Arcade::Rectangle(std::make_pair(0, i), "wall", Arcade::Color::WHITE, 1, 1));
            for (int j = 1; j < SIZE_MAP_X; j++) {
                if ((i % 2 == 0 && j % 2 == 0) || (i % 2 != 0 && j % 2 != 0))
                    _map[i].push_back(Arcade::Rectangle(std::make_pair(j, i), "empty", Arcade::Color::BLUE, 1, 1));
                else
                    _map[i].push_back(Arcade::Rectangle(std::make_pair(j, i), "empty", Arcade::Color::CYAN, 1, 1));
            }
            _map[i].push_back(Arcade::Rectangle(std::make_pair(SIZE_MAP_X, i), "wall", Arcade::Color::WHITE, 1, 1));
        }
        for (int i = 0; i < SIZE_MAP_X + 1; i++)
            _map[SIZE_MAP_Y].push_back(Arcade::Rectangle(std::make_pair(i, SIZE_MAP_Y), "wall", Arcade::Color::WHITE, 1, 1));
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
        if (_body[0].getPos().first < 1 || _body[0].getPos().first >= SIZE_MAP_X || _body[0].getPos().second < 1 || _body[0].getPos().second >= SIZE_MAP_Y)
            return true;
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

    bool Snake::Player::win()
    {
        if (_body.size() == (SIZE_MAP_X - 1) * (SIZE_MAP_Y - 1) + 1)
            return true;
        return false;
    }
}

extern "C" Arcade::IGameModule *entryGamePoint()
{
    return (new Arcade::Snake());
}