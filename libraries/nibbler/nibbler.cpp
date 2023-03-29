/*
** EPITECH PROJECT, 2023
** Arcade
** File description:
** test
*/

#include "nibbler.hpp"

namespace Arcade {
    std::vector<std::shared_ptr<Arcade::IObject>> Nibbler::loop(Arcade::Input input)
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
        _player.move(_map);
        if (_player._changeInput)
            _input = _player._direction;
        if (_player.isDead())
            start();
        if (_player.isEating(_apple)) {
            _player.eat();
            _score++;
        }
        if (win()) {
            std::cout << "You win" << std::endl;
            start();
        }
        for (auto &apple : _apple)
            objects.push_back(std::make_shared<Arcade::Circle>(std::make_pair(apple.first, apple.second), "../assets/apple.png", Arcade::Color::RED, 1));
        for (auto &body : _player._body)
            objects.push_back(std::make_shared<Arcade::Rectangle>(std::make_pair(body.getPos().first, body.getPos().second), "snake", Arcade::Color::GREEN, 1, 1));
        objects.push_back(std::make_shared<Arcade::Text>(std::make_pair(0, 0), "Score: " + std::to_string(_score), Arcade::Color::BLACK, 1));
        return objects;
    }

    int Nibbler::getScore()
    {
        return 0;
    }

    void Nibbler::start()
    {
        _score = 0;
        _input = Arcade::Input::RIGHT;
        _player._body.clear();
        _player._body.push_back(Arcade::Rectangle(std::make_pair(7, 10), "snake", Arcade::Color::GREEN, 1, 1));
        _player._body.push_back(Arcade::Rectangle(std::make_pair(6, 10), "snake", Arcade::Color::GREEN, 1, 1));
        _player._body.push_back(Arcade::Rectangle(std::make_pair(5, 10), "snake", Arcade::Color::GREEN, 1, 1));
        _player._body.push_back(Arcade::Rectangle(std::make_pair(4, 10), "snake", Arcade::Color::GREEN, 1, 1));
        _player._direction = Arcade::Input::RIGHT;
        initMap();
    }

    void Nibbler::initMap()
    {
        _map.clear();
        for (int i = 0; i < SIZE_MAP_Y + 1; i++) {
            std::vector<Arcade::Rectangle> line;
            _map.push_back(line);
        }
        for (int i = 0; i < SIZE_MAP_Y + 1; i++) {
            for (int j = 0; j < SIZE_MAP_X + 1; j++) {
                if (map[i][j] == '0')
                    _map[i].push_back(Arcade::Rectangle(std::make_pair(j, i), "wall", Arcade::Color::WHITE, 1, 1));
                else if (map[i][j] == '2') {
                    _apple.push_back(std::make_pair(j, i));
                    _map[i].push_back(Arcade::Rectangle(std::make_pair(j, i), "empty", Arcade::Color::BLUE, 1, 1));
                } else
                    _map[i].push_back(Arcade::Rectangle(std::make_pair(j, i), "empty", Arcade::Color::BLUE, 1, 1));
            }
        }
    }

    void Nibbler::Player::move(std::vector<std::vector<Arcade::Rectangle>> map)
    {
        std::vector<Arcade::Rectangle> body;
        Arcade::Rectangle block = getBlock("top", map);
        Arcade::Rectangle right = getBlock("right", map);
        Arcade::Rectangle left = getBlock("left", map);
        if (block.getTexture() == "empty") {
            if (_direction == Arcade::Input::LEFT)
                body.push_back(Arcade::Rectangle(std::make_pair(_body[0].getPos().first - 1, _body[0].getPos().second), "snake", Arcade::Color::GREEN, 1, 1));
            if (_direction == Arcade::Input::RIGHT)
                body.push_back(Arcade::Rectangle(std::make_pair(_body[0].getPos().first + 1, _body[0].getPos().second), "snake", Arcade::Color::GREEN, 1, 1));
            if (_direction == Arcade::Input::UP)
                body.push_back(Arcade::Rectangle(std::make_pair(_body[0].getPos().first, _body[0].getPos().second - 1), "snake", Arcade::Color::GREEN, 1, 1));
            if (_direction == Arcade::Input::DOWN)
                body.push_back(Arcade::Rectangle(std::make_pair(_body[0].getPos().first, _body[0].getPos().second + 1), "snake", Arcade::Color::GREEN, 1, 1));
        } else if (block.getTexture() == "wall") {
            if (right.getTexture() == "wall" && left.getTexture() != "wall") {
                if (_direction == Arcade::Input::UP) {
                    body.push_back(Arcade::Rectangle(std::make_pair(_body[0].getPos().first - 1, _body[0].getPos().second), "snake", Arcade::Color::GREEN, 1, 1));
                    _direction = Arcade::Input::LEFT;
                    _changeInput = true;
                }
                else if (_direction == Arcade::Input::DOWN) {
                    body.push_back(Arcade::Rectangle(std::make_pair(_body[0].getPos().first + 1, _body[0].getPos().second), "snake", Arcade::Color::GREEN, 1, 1));
                    _direction = Arcade::Input::RIGHT;
                    _changeInput = true;
                }
                else if (_direction == Arcade::Input::LEFT) {
                    body.push_back(Arcade::Rectangle(std::make_pair(_body[0].getPos().first , _body[0].getPos().second + 1), "snake", Arcade::Color::GREEN, 1, 1));
                    _direction = Arcade::Input::DOWN;
                    _changeInput = true;
                }
                else if (_direction == Arcade::Input::RIGHT) {
                    body.push_back(Arcade::Rectangle(std::make_pair(_body[0].getPos().first , _body[0].getPos().second - 1), "snake", Arcade::Color::GREEN, 1, 1));
                    _direction = Arcade::Input::UP;
                    _changeInput = true;
                }
            } else if (right.getTexture() != "wall" && left.getTexture() == "wall") {
                if (_direction == Arcade::Input::UP) {
                    body.push_back(Arcade::Rectangle(std::make_pair(_body[0].getPos().first + 1, _body[0].getPos().second), "snake", Arcade::Color::GREEN, 1, 1));
                    _direction = Arcade::Input::RIGHT;
                    _changeInput = true;
                }
                else if (_direction == Arcade::Input::DOWN) {
                    body.push_back(Arcade::Rectangle(std::make_pair(_body[0].getPos().first - 1, _body[0].getPos().second), "snake", Arcade::Color::GREEN, 1, 1));
                    _direction = Arcade::Input::LEFT;
                    _changeInput = true;
                }
                else if (_direction == Arcade::Input::LEFT) {
                    body.push_back(Arcade::Rectangle(std::make_pair(_body[0].getPos().first , _body[0].getPos().second - 1), "snake", Arcade::Color::GREEN, 1, 1));
                    _direction = Arcade::Input::UP;
                    _changeInput = true;
                }
                else if (_direction == Arcade::Input::RIGHT) {
                    body.push_back(Arcade::Rectangle(std::make_pair(_body[0].getPos().first , _body[0].getPos().second + 1), "snake", Arcade::Color::GREEN, 1, 1));
                    _direction = Arcade::Input::DOWN;
                    _changeInput = true;
                }
            } else {
                std::cout << "GAME OVER" << std::endl;
                std::cout << "direction : " << _direction << std::endl;
                body.push_back(Arcade::Rectangle(std::make_pair(_body[0].getPos().first, _body[0].getPos().second), "snake", Arcade::Color::GREEN, 1, 1));
                for (std::size_t i = 1; i < _body.size(); i++) {
                    body.push_back(Arcade::Rectangle(std::make_pair(_body[i].getPos().first, _body[i].getPos().second), "snake", Arcade::Color::GREEN, 1, 1));
                }
                _body = body;
                return;
            }
        }
        for (std::size_t i = 1; i < _body.size(); i++) {
                body.push_back(Arcade::Rectangle(std::make_pair(_body[i - 1].getPos().first, _body[i - 1].getPos().second), "snake", Arcade::Color::GREEN, 1, 1));
        }
        _body = body;
    }

    Arcade::Rectangle Nibbler::Player::getBlock(std::string direction, std::vector<std::vector<Arcade::Rectangle>> map)
    {
        if (direction == "top") {
            if (_direction == Arcade::Input::LEFT)
                return map[_body[0].getPos().second][_body[0].getPos().first - 1];
            if (_direction == Arcade::Input::RIGHT)
                return map[_body[0].getPos().second][_body[0].getPos().first + 1];
            if (_direction == Arcade::Input::UP)
                return map[_body[0].getPos().second - 1][_body[0].getPos().first];
            if (_direction == Arcade::Input::DOWN)
                return map[_body[0].getPos().second + 1][_body[0].getPos().first];
        } else if (direction == "right") {
            if (_direction == Arcade::Input::LEFT)
                return map[_body[0].getPos().second - 1][_body[0].getPos().first];
            if (_direction == Arcade::Input::RIGHT)
                return map[_body[0].getPos().second + 1][_body[0].getPos().first];
            if (_direction == Arcade::Input::UP)
                return map[_body[0].getPos().second][_body[0].getPos().first + 1];
            if (_direction == Arcade::Input::DOWN)
                return map[_body[0].getPos().second][_body[0].getPos().first - 1];
        } else if (direction == "left") {
            if (_direction == Arcade::Input::LEFT)
                return map[_body[0].getPos().second + 1][_body[0].getPos().first];
            if (_direction == Arcade::Input::RIGHT)
                return map[_body[0].getPos().second - 1][_body[0].getPos().first];
            if (_direction == Arcade::Input::UP)
                return map[_body[0].getPos().second][_body[0].getPos().first - 1];
            if (_direction == Arcade::Input::DOWN)
                return map[_body[0].getPos().second][_body[0].getPos().first + 1];
        }
        return Arcade::Rectangle(std::make_pair(0, 0), "snake", Arcade::Color::GREEN, 1, 1);
    }

    bool Nibbler::Player::isDead()
    {
        for (std::size_t i = 1; i < _body.size(); i++) {
            if (_body[i].getPos() == _body[0].getPos())
                return true;
        }
        return false;
    }

    void Nibbler::Player::eat()
    {
        _body.push_back(Arcade::Rectangle(std::make_pair(_body[_body.size() - 1].getPos().first, _body[_body.size() - 1].getPos().second), "snake", Arcade::Color::GREEN, 10, 10));
    }

    bool Nibbler::Player::isEating(std::vector<std::pair<int, int>> &apple)
    {
        int i = 0;
        for (auto app : apple) {
            if (_body[0].getPos() == app) {
                apple.erase(apple.begin() + i);
                return true;
            }
            i++;
        }
        return false;
    }

    bool Nibbler::win()
    {
        if (_apple.size() == 0)
            return true;
        return false;
    }
}

extern "C" Arcade::IGameModule *entryGamePoint()
{
    return (new Arcade::Nibbler());
}