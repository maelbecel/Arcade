/*
** EPITECH PROJECT, 2023
** Arcade
** File description:
** test
*/

#include "nibbler.hpp"

namespace Arcade {
    /**
     * It takes the input, moves the player, checks if the player is dead, checks
     * if the player is eating an apple, checks if the player won, and returns a
     * vector of objects to be displayed
     *
     * @param input The input that the player has given.
     *
     * @return A vector of shared pointers to IObjects
     */
    std::vector<std::shared_ptr<Arcade::IObject>> Nibbler::loop(Arcade::Input input)
    {
        std::vector<std::shared_ptr<Arcade::IObject>> objects;
        if (input != Arcade::Input::UNKNOWN) {
            _input = input;
        }
        if (_scene == GAME) {
            if (_input == Arcade::Input::LEFT && _player._direction != Arcade::Input::RIGHT)
                _player._direction = Arcade::Input::LEFT;
            if (_input == Arcade::Input::RIGHT && _player._direction != Arcade::Input::LEFT)
                _player._direction = Arcade::Input::RIGHT;
            if (_input == Arcade::Input::UP && _player._direction != Arcade::Input::DOWN)
                _player._direction = Arcade::Input::UP;
            if (_input == Arcade::Input::DOWN && _player._direction != Arcade::Input::UP)
                _player._direction = Arcade::Input::DOWN;
            _player.move(_map, walls);
            if (_player._changeInput)
                _input = _player._direction;
            if (_player.isDead()) {
                _scene = END;
                end("You lose", objects);
                return objects;
            }
            if (_player.isEating(_apple)) {
                _player.eat();
                _score++;
            }
            if (win()) {
                _scene = WIN;
            }
            for (auto &line : _map) {
                for (auto &wall : line)
                    objects.push_back(std::make_shared<Arcade::Rectangle>(std::make_pair(wall.getPos().first, wall.getPos().second),wall.getTexture().value() , wall.getColor(), 1, 1));
            }
            for (auto &apple : _apple)
                objects.push_back(std::make_shared<Arcade::Circle>(std::make_pair(apple.first, apple.second), "assets/apple.png", Arcade::Color::RED, 1));
            std::vector<Arcade::Rectangle> snake = _player._body;
            std::sort(snake.begin(), snake.end(), comparePos);
            for (auto &body : snake) {
                if (body.getTexture().has_value())
                    objects.push_back(std::make_shared<Arcade::Rectangle>(std::make_pair(body.getPos().first, body.getPos().second), body.getTexture().value(), Arcade::Color::GREEN, 1, 1));
                else
                    objects.push_back(std::make_shared<Arcade::Rectangle>(std::make_pair(body.getPos().first, body.getPos().second), "", Arcade::Color::GREEN, 1, 1));
            }
            objects.push_back(std::make_shared<Arcade::Text>(std::make_pair(0, 0), "Score: " + std::to_string(_score), Arcade::Color::WHITE, 50));
        }  else if (_scene == END) {
            end("You lose", objects);
        } else if (_scene == WIN) {
            end("You win", objects);
        }
        return objects;
    }


    bool Nibbler::comparePos(Arcade::Rectangle rect1, Arcade::Rectangle rect2)
    {
        if (rect1.getPos().second == rect2.getPos().second)
            return rect1.getPos().first < rect2.getPos().first;
        else
            return rect1.getPos().second < rect2.getPos().second;
    }


    void Nibbler::end(std::string str, std::vector<std::shared_ptr<Arcade::IObject>> &objects)
    {
        objects.push_back(std::make_shared<Arcade::Text>(std::make_pair(6, 4), str, Arcade::Color::WHITE, 50));
        objects.push_back(std::make_shared<Arcade::Text>(std::make_pair(6, 5), "Score: " + std::to_string(_score), Arcade::Color::WHITE, 50));
        objects.push_back(std::make_shared<Arcade::Text>(std::make_pair(4, 6), "Press F5 to play", Arcade::Color::WHITE, 50));
        if (_input == Arcade::Input::RESTART)
            start();
    }

    /**
     * This function returns the score of the player
     *
     * @return The score of the player.
     */
    int Nibbler::getScore()
    {
        return _score;
    }

    /**
     * It initializes the game
     */
    void Nibbler::start()
    {
        _score = 0;
        _scene = GAME;
        _input = Arcade::Input::RIGHT;
        _player._body.clear();
        _player._body.push_back(Arcade::Rectangle(std::make_pair(7, 10), "snake", Arcade::Color::GREEN, 1, 1));
        _player._body.push_back(Arcade::Rectangle(std::make_pair(6, 10), "snake", Arcade::Color::GREEN, 1, 1));
        _player._body.push_back(Arcade::Rectangle(std::make_pair(5, 10), "snake", Arcade::Color::GREEN, 1, 1));
        _player._body.push_back(Arcade::Rectangle(std::make_pair(4, 10), "snake", Arcade::Color::GREEN, 1, 1));
        _player._direction = Arcade::Input::RIGHT;
        initMap();
    }

    /**
     * It initializes the map
     */
    void Nibbler::initMap()
    {
        _map.clear();
        for (int i = 0; i < SIZE_MAP_Y + 1; i++) {
            std::vector<Arcade::Rectangle> line;
            _map.push_back(line);
        }
        for (int i = 0; i < SIZE_MAP_Y + 1; i++) {
            for (int j = 0; j < SIZE_MAP_X + 1; j++) {
                if (walls[i][j] == '0')
                    _map[i].push_back(Arcade::Rectangle(std::make_pair(j, i), "./assets/wall.jpg", Arcade::Color::WHITE, 1, 1));
                else if (walls[i][j] == '2') {
                    _apple.push_back(std::make_pair(j, i));
                    _map[i].push_back(Arcade::Rectangle(std::make_pair(j, i), "./assets/grass.png", Arcade::Color::BLUE, 1, 1));
                } else
                    _map[i].push_back(Arcade::Rectangle(std::make_pair(j, i), "./assets/grass.png", Arcade::Color::BLUE, 1, 1));
            }
        }
    }

    /**
     * It moves the snake
     *
     * @param map The map of the game
     * @param wall The map of the game
     *
     * @return a vector of Arcade::Rectangle.
     */
    void Nibbler::Player::move(std::vector<std::vector<Arcade::Rectangle>> map, std::string wall[12])
    {
        int x = 0;
        int y = 0;
        std::vector<Arcade::Input> direction;
        for (std::size_t i = 0; i < _body.size(); i++) {
            if (i == 0)
                direction.push_back(_direction);
            else if (i == _body.size() - 1) {
                direction.push_back(direction[i - 1]);
                _directionTail = direction[i - 1];
            }
            else {
                x = _body[i].getPos().first - _body[i - 1].getPos().first;
                y = _body[i].getPos().second - _body[i - 1].getPos().second;
                if (x == 1 && y == 0)
                    direction.push_back(Arcade::Input::LEFT);
                else if (x == -1 && y == 0)
                    direction.push_back(Arcade::Input::RIGHT);
                else if (x == 0 && y == 1)
                    direction.push_back(Arcade::Input::UP);
                else if (x == 0 && y == -1)
                    direction.push_back(Arcade::Input::DOWN);
                else
                    direction.push_back(direction[i - 1]);
            }
        }
        std::vector<Arcade::Rectangle> body;
        Arcade::Rectangle block = getBlock("top", map);
        Arcade::Rectangle right = getBlock("right", map);
        Arcade::Rectangle left = getBlock("left", map);
        if (wall[block.getPos().second][block.getPos().first] != '0') {
            if (_direction == Arcade::Input::LEFT)
                body.push_back(Arcade::Rectangle(std::make_pair(_body[0].getPos().first - 1, _body[0].getPos().second), getTextureDir("head", 0, direction), Arcade::Color::GREEN, 1, 1));
            if (_direction == Arcade::Input::RIGHT)
                body.push_back(Arcade::Rectangle(std::make_pair(_body[0].getPos().first + 1, _body[0].getPos().second), getTextureDir("head", 0, direction), Arcade::Color::GREEN, 1, 1));
            if (_direction == Arcade::Input::UP)
                body.push_back(Arcade::Rectangle(std::make_pair(_body[0].getPos().first, _body[0].getPos().second - 1), getTextureDir("head", 0, direction), Arcade::Color::GREEN, 1, 1));
            if (_direction == Arcade::Input::DOWN)
                body.push_back(Arcade::Rectangle(std::make_pair(_body[0].getPos().first, _body[0].getPos().second + 1), getTextureDir("head", 0, direction), Arcade::Color::GREEN, 1, 1));
        } else if (wall[block.getPos().second][block.getPos().first] == '0') {
            if (wall[right.getPos().second][right.getPos().first] == '0' && wall[left.getPos().second][left.getPos().first] != '0') {
                if (_direction == Arcade::Input::UP) {
                    _direction = Arcade::Input::LEFT;
                    direction[0] = _direction;
                    body.push_back(Arcade::Rectangle(std::make_pair(_body[0].getPos().first - 1, _body[0].getPos().second), getTextureDir("head", 0, direction), Arcade::Color::GREEN, 1, 1));
                    _changeInput = true;
                }
                else if (_direction == Arcade::Input::DOWN) {
                    _direction = Arcade::Input::RIGHT;
                    direction[0] = _direction;
                    body.push_back(Arcade::Rectangle(std::make_pair(_body[0].getPos().first + 1, _body[0].getPos().second), getTextureDir("head", 0, direction), Arcade::Color::GREEN, 1, 1));
                    _changeInput = true;
                }
                else if (_direction == Arcade::Input::LEFT) {
                    _direction = Arcade::Input::DOWN;
                    direction[0] = _direction;
                    body.push_back(Arcade::Rectangle(std::make_pair(_body[0].getPos().first , _body[0].getPos().second + 1), getTextureDir("head", 0, direction), Arcade::Color::GREEN, 1, 1));
                    _changeInput = true;
                }
                else if (_direction == Arcade::Input::RIGHT) {
                    _direction = Arcade::Input::UP;
                    direction[0] = _direction;
                    body.push_back(Arcade::Rectangle(std::make_pair(_body[0].getPos().first , _body[0].getPos().second - 1), getTextureDir("head", 0, direction), Arcade::Color::GREEN, 1, 1));
                    _changeInput = true;
                }
            } else if (wall[right.getPos().second][right.getPos().first] != '0' && wall[left.getPos().second][left.getPos().first] == '0') {
                if (_direction == Arcade::Input::UP) {
                    _direction = Arcade::Input::RIGHT;
                    direction[0] = _direction;
                    body.push_back(Arcade::Rectangle(std::make_pair(_body[0].getPos().first + 1, _body[0].getPos().second), getTextureDir("head", 0, direction), Arcade::Color::GREEN, 1, 1));
                    _changeInput = true;
                }
                else if (_direction == Arcade::Input::DOWN) {
                    _direction = Arcade::Input::LEFT;
                    direction[0] = _direction;
                    body.push_back(Arcade::Rectangle(std::make_pair(_body[0].getPos().first - 1, _body[0].getPos().second), getTextureDir("head", 0, direction), Arcade::Color::GREEN, 1, 1));
                    _changeInput = true;
                }
                else if (_direction == Arcade::Input::LEFT) {
                    _direction = Arcade::Input::UP;
                    direction[0] = _direction;
                    body.push_back(Arcade::Rectangle(std::make_pair(_body[0].getPos().first , _body[0].getPos().second - 1), getTextureDir("head", 0, direction), Arcade::Color::GREEN, 1, 1));
                    _changeInput = true;
                }
                else if (_direction == Arcade::Input::RIGHT) {
                    _direction = Arcade::Input::DOWN;
                    direction[0] = _direction;
                    body.push_back(Arcade::Rectangle(std::make_pair(_body[0].getPos().first , _body[0].getPos().second + 1), getTextureDir("head", 0, direction), Arcade::Color::GREEN, 1, 1));
                    _changeInput = true;
                }
            } else {
                body.push_back(Arcade::Rectangle(std::make_pair(_body[0].getPos().first, _body[0].getPos().second), getTextureDir("head", 0, direction), Arcade::Color::GREEN, 1, 1));
                for (std::size_t i = 1; i < _body.size(); i++) {
                    if (i == _body.size() - 1)
                        body.push_back(Arcade::Rectangle(std::make_pair(_body[i].getPos().first, _body[i].getPos().second), getTextureDir("tail", i, direction), Arcade::Color::GREEN, 1, 1));
                    else
                        body.push_back(Arcade::Rectangle(std::make_pair(_body[i].getPos().first, _body[i].getPos().second), getTextureDir("body", i + 1, direction), Arcade::Color::GREEN, 1, 1));
                }
                _body = body;
                return;
            }
        }
        for (std::size_t i = 1; i < _body.size(); i++) {
            if (i == _body.size() - 1)
                body.push_back(Arcade::Rectangle(std::make_pair(_body[i - 1].getPos().first, _body[i - 1].getPos().second), getTextureDir("tail", i, direction), Arcade::Color::GREEN, 1, 1));
            else
                body.push_back(Arcade::Rectangle(std::make_pair(_body[i - 1].getPos().first, _body[i - 1].getPos().second), getTextureDir("body", i, direction), Arcade::Color::GREEN, 1, 1));
        }
        _body = body;
    }

    std::optional<std::string> Nibbler::Player::getTextureDir(std::string bodyPart, int i, std::vector<Arcade::Input> direction)
    {
        if (bodyPart == "head") {
            if (_direction == Arcade::Input::LEFT)
                return "./assets/snake/head_left.png";
            if (_direction == Arcade::Input::RIGHT)
                return "./assets/snake/head_right.png";
            if (_direction == Arcade::Input::UP)
                return "./assets/snake/head_up.png";
            if (_direction == Arcade::Input::DOWN)
                return "./assets/snake/head_down.png";
        } else if (bodyPart == "tail") {
            if (direction[i] == Arcade::Input::LEFT)
                return "./assets/snake/tail_right.png";
            if (direction[i] == Arcade::Input::RIGHT)
                return "./assets/snake/tail_left.png";
            if (direction[i] == Arcade::Input::UP)
                return "./assets/snake/tail_down.png";
            if (direction[i] == Arcade::Input::DOWN)
                return "./assets/snake/tail_up.png";
        } else if (bodyPart == "body") {
            if (direction[i] == direction[i - 1] && (direction[i] == Arcade::Input::LEFT || direction[i] == Arcade::Input::RIGHT))
                return "./assets/snake/body_horizontal.png";
            if (direction[i] == direction[i - 1] && (direction[i] == Arcade::Input::UP || direction[i] == Arcade::Input::DOWN))
                return "./assets/snake/body_vertical.png";
            if (direction[i] == Arcade::Input::LEFT && direction[i - 1] == Arcade::Input::UP)
                return "./assets/snake/body_topright.png";
            if (direction[i] == Arcade::Input::LEFT && direction[i - 1] == Arcade::Input::DOWN)
                return "./assets/snake/body_bottomright.png";
            if (direction[i] == Arcade::Input::RIGHT && direction[i - 1] == Arcade::Input::UP)
                return "./assets/snake/body_topleft.png";
            if (direction[i] == Arcade::Input::RIGHT && direction[i - 1] == Arcade::Input::DOWN)
                return "./assets/snake/body_bottomleft.png";
            if (direction[i] == Arcade::Input::UP && direction[i - 1] == Arcade::Input::LEFT)
                return "./assets/snake/body_bottomleft.png";
            if (direction[i] == Arcade::Input::UP && direction[i - 1] == Arcade::Input::RIGHT)
                return "./assets/snake/body_bottomright.png";
            if (direction[i] == Arcade::Input::DOWN && direction[i - 1] == Arcade::Input::LEFT)
                return "./assets/snake/body_topleft.png";
            if (direction[i] == Arcade::Input::DOWN && direction[i - 1] == Arcade::Input::RIGHT)
                return "./assets/snake/body_topright.png";
        }
        return "";
    }

    std::optional<std::string> Nibbler::Player::getTextureDir(Arcade::Input direction)
    {
        if (direction == Arcade::Input::LEFT)
            return "./assets/snake/tail_right.png";
        if (direction == Arcade::Input::RIGHT)
            return "./assets/snake/tail_left.png";
        if (direction == Arcade::Input::UP)
            return "./assets/snake/tail_down.png";
        if (direction == Arcade::Input::DOWN)
            return "./assets/snake/tail_up.png";
        return "";
    }

    /**
     * It returns the block in front of the player
     *
     * @param direction The direction of the block you want to get.
     * @param map The map of the game
     *
     * @return The block in front of the player
     */
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

    /**
     * If the head of the snake is in the same position as any other part of the
     * snake, the snake is dead
     *
     * @return A boolean value.
     */
    bool Nibbler::Player::isDead()
    {
        for (std::size_t i = 1; i < _body.size(); i++) {
            if (_body[i].getPos() == _body[0].getPos())
                return true;
        }
        return false;
    }

    /**
     * It adds a new rectangle to the body of the snake
     */
    void Nibbler::Player::eat()
    {
        _body.push_back(Arcade::Rectangle(std::make_pair(_body[_body.size() - 1].getPos().first, _body[_body.size() - 1].getPos().second), getTextureDir(_directionTail), Arcade::Color::GREEN, 10, 10));
    }

    /**
     * If the head of the snake is on the same position as an apple, remove the
     * apple from the vector and return true
     *
     * @param apple vector of all the apples on the map
     *
     * @return A boolean value.
     */
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

    /**
     * It returns true if the snake has eaten all the apples
     *
     * @return A boolean value.
     */
    bool Nibbler::win()
    {
        if (_apple.size() == 0)
            return true;
        return false;
    }
}

/* Creating a function that returns a pointer to a new instance of the Nibbler
class. */
extern "C" Arcade::IGameModule *entryGamePoint()
{
    return (new Arcade::Nibbler());
}