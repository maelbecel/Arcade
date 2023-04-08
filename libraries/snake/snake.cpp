/*
** EPITECH PROJECT, 2023
** Arcade
** File description:
** test
*/

#include "snake.hpp"

std::ostream& operator<<(std::ostream& os, Arcade::Input dir)
{
    switch (dir) {
        case Arcade::Input::LEFT:
            os << "LEFT";
            break;
        case Arcade::Input::RIGHT:
            os << "RIGHT";
            break;
        case Arcade::Input::UP:
            os << "UP";
            break;
        case Arcade::Input::DOWN:
            os << "DOWN";
            break;
        default:
            os << "NONE";
            break;
    }
    return os;
}

namespace Arcade {
    /**
     * It moves the snake, checks if it's dead, checks if it's eating, checks if
     * it's winning, and returns the objects to be displayed
     *
     * @param input The input from the user
     *
     * @return A vector of shared pointers to IObjects
     */
    std::vector<std::shared_ptr<Arcade::IObject>> Snake::loop(Arcade::Input input)
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
            _player.move();
            if (_player.isDead()) {
                _scene = END;
                end("You lose", objects);
                return objects;
            }
            if (_player.isEating(_apple)) {
                _player.eat();
                _apple = getNewPos();
                _score++;
            }
            if (_player.win()) {
                _scene = WIN;
            }
            for (auto &line : _map) {
                for (auto &wall : line)
                    objects.push_back(std::make_shared<Arcade::Rectangle>(std::make_pair(wall.getPos().first, wall.getPos().second), wall.getTexture().value(), wall.getColor(), 1, 1));
            }
            objects.push_back(std::make_shared<Arcade::Circle>(std::make_pair(_apple.first, _apple.second), "assets/apple.png", Arcade::Color::RED, 1));
            for (auto &body : _player._body) {
                if (body.getTexture().has_value())
                    objects.push_back(std::make_shared<Arcade::Rectangle>(std::make_pair(body.getPos().first, body.getPos().second), body.getTexture().value(), Arcade::Color::GREEN, 1, 1));
                else
                    objects.push_back(std::make_shared<Arcade::Rectangle>(std::make_pair(body.getPos().first, body.getPos().second), "", Arcade::Color::GREEN, 1, 1));
            }
            objects.push_back(std::make_shared<Arcade::Text>(std::make_pair(0, 0), "Score: " + std::to_string(_score), Arcade::Color::WHITE, 50));
        } else if (_scene == END) {
            end("You lose", objects);
        } else if (_scene == WIN) {
            end("You win", objects);
        }
        return objects;
    }

    /**
     * The function "end" adds text objects to a vector and restarts the game if
     * the input is "RESTART".
     *
     * @param str A string that represents the message to be displayed on the
     * screen when the game ends.
     * @param objects A reference to a vector of shared pointers to objects that
     * implement the Arcade::IObject interface. This vector is used to store the
     * objects that will be displayed on the screen.
     */
    void Snake::end(std::string str, std::vector<std::shared_ptr<Arcade::IObject>> &objects)
    {
        objects.push_back(std::make_shared<Arcade::Text>(std::make_pair(6, 4), str, Arcade::Color::WHITE, 50));
        objects.push_back(std::make_shared<Arcade::Text>(std::make_pair(6, 5), "Score: " + std::to_string(_score), Arcade::Color::WHITE, 50));
        objects.push_back(std::make_shared<Arcade::Text>(std::make_pair(4, 6), "Press F6 to play", Arcade::Color::WHITE, 50));
        if (_input == Arcade::Input::RESTART)
            start();
    }

    /**
     * This function returns the score of the snake
     *
     * @return The score of the snake.
     */
    int Snake::getScore()
    {
        return _score;
    }

    /**
     * It initializes the game
     */
    void Snake::start()
    {
        _score = 0;
        _scene = GAME;
        _input = Arcade::Input::RIGHT;
        _player._body.clear();
        _player._direction = Arcade::Input::RIGHT;
        _player._body.push_back(Arcade::Rectangle(std::make_pair(7, 5), "./assets/snake/head_right", Arcade::Color::GREEN, 1, 1));
        _player._body.push_back(Arcade::Rectangle(std::make_pair(6, 5), "./assets/snake/body_horizontal.png", Arcade::Color::GREEN, 1, 1));
        _player._body.push_back(Arcade::Rectangle(std::make_pair(5, 5), "./assets/snake/body_horizontal.png", Arcade::Color::GREEN, 1, 1));
        _player._body.push_back(Arcade::Rectangle(std::make_pair(4, 5), "./assets/snake/tail_right.png", Arcade::Color::GREEN, 1, 1));
        _apple = getNewPos();
        initMap();
    }

    /**
     * It returns a random position on the map, but it makes sure that the
     * position is not the same as the apple's position, and that it is not the
     * same as any of the snake's body parts
     *
     * @return A pair of ints
     */
    std::pair<int, int> Snake::getNewPos()
    {
        std::pair<int, int> pos = std::make_pair(rand() % (SIZE_MAP_X - 1) + 1, rand() % (SIZE_MAP_Y - 1) + 1);
        if (pos == _apple)
            return getNewPos();
        if (_player.win())
            return pos;
        for (auto &body : _player._body) {
            if (body.getPos() == pos)
                return getNewPos();
        }
        return pos;
    }

    /**
     * It initializes the map
     */
    void Snake::initMap()
    {
        _map.clear();
        for (int i = 0; i < SIZE_MAP_Y + 1; i++) {
            std::vector<Arcade::Rectangle> line;
            _map.push_back(line);
        }
        for (int i = 0; i < SIZE_MAP_X + 1; i++)
            _map[0].push_back(Arcade::Rectangle(std::make_pair(i, 0), "./assets/wall.jpg", Arcade::Color::WHITE, 1, 1));
        for (int i = 1; i < SIZE_MAP_Y; i++) {
            _map[i].push_back(Arcade::Rectangle(std::make_pair(0, i), "./assets/wall.jpg", Arcade::Color::WHITE, 1, 1));
            for (int j = 1; j < SIZE_MAP_X; j++) {
                if ((i % 2 == 0 && j % 2 == 0) || (i % 2 != 0 && j % 2 != 0))
                    _map[i].push_back(Arcade::Rectangle(std::make_pair(j, i), "./assets/grass.png", Arcade::Color::BLUE, 1, 1));
                else
                    _map[i].push_back(Arcade::Rectangle(std::make_pair(j, i), "./assets/grass2.png", Arcade::Color::CYAN, 1, 1));
            }
            _map[i].push_back(Arcade::Rectangle(std::make_pair(SIZE_MAP_X, i), "./assets/wall.jpg", Arcade::Color::WHITE, 1, 1));
        }
        for (int i = 0; i < SIZE_MAP_X + 1; i++)
            _map[SIZE_MAP_Y].push_back(Arcade::Rectangle(std::make_pair(i, SIZE_MAP_Y), "./assets/wall.jpg", Arcade::Color::WHITE, 1, 1));
    }

    /**
     * It moves the snake
     */
    void Snake::Player::move()
    {
        int x = 0;
        int y = 0;
        std::vector<Arcade::Input> direction;
        for (std::size_t i = 0; i < _body.size(); i++) {
            if (i == 0)
                direction.push_back(_direction);
            else if (i == _body.size() - 1)
                direction.push_back(direction[i - 1]);
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
        for (std::size_t i = 0; i < _body.size(); i++) {
            if (i == 0) {
                if (_direction == Arcade::Input::LEFT)
                    body.push_back(Arcade::Rectangle(std::make_pair(_body[i].getPos().first - 1, _body[i].getPos().second), getTextureDir("head", 0, direction), Arcade::Color::GREEN, 1, 1));
                if (_direction == Arcade::Input::RIGHT)
                    body.push_back(Arcade::Rectangle(std::make_pair(_body[i].getPos().first + 1, _body[i].getPos().second), getTextureDir("head", 0, direction), Arcade::Color::GREEN, 1, 1));
                if (_direction == Arcade::Input::UP)
                    body.push_back(Arcade::Rectangle(std::make_pair(_body[i].getPos().first, _body[i].getPos().second - 1), getTextureDir("head", 0, direction), Arcade::Color::GREEN, 1, 1));
                if (_direction == Arcade::Input::DOWN)
                    body.push_back(Arcade::Rectangle(std::make_pair(_body[i].getPos().first, _body[i].getPos().second + 1), getTextureDir("head", 0, direction), Arcade::Color::GREEN, 1, 1));
            } else if (i == _body.size() - 1) {
                body.push_back(Arcade::Rectangle(std::make_pair(_body[i - 1].getPos().first, _body[i - 1].getPos().second), getTextureDir("tail", i, direction), Arcade::Color::GREEN, 1, 1));
            } else {
                body.push_back(Arcade::Rectangle(std::make_pair(_body[i - 1].getPos().first, _body[i - 1].getPos().second), getTextureDir("body", i, direction), Arcade::Color::GREEN, 1, 1));
            }
        }
        _body = body;
    }

    std::optional<std::string> Snake::Player::getTextureDir(std::string bodyPart, int i, std::vector<Arcade::Input> direction)
    {
        if (bodyPart == "head") {
            if (direction[i] == Arcade::Input::LEFT)
                return "./assets/snake/head_left.png";
            if (direction[i] == Arcade::Input::RIGHT)
                return "./assets/snake/head_right.png";
            if (direction[i] == Arcade::Input::UP)
                return "./assets/snake/head_up.png";
            if (direction[i] == Arcade::Input::DOWN)
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

    std::optional<std::string> Snake::Player::getTextureDir(Arcade::Input direction)
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
     * If the head of the snake is in the same position as any other part of the
     * snake, or if the head of the snake is outside the map, the snake is dead
     *
     * @return A boolean value.
     */
    bool Snake::Player::isDead()
    {
        for (std::size_t i = 1; i < _body.size(); i++) {
            if (_body[i].getPos() == _body[0].getPos())
                return true;
        }
        if (_body[0].getPos().first < 1 || _body[0].getPos().first >= SIZE_MAP_X || _body[0].getPos().second < 1 || _body[0].getPos().second == SIZE_MAP_Y)
            return true;
        return false;
    }

    /**
     * It adds a new rectangle to the body of the snake
     */
    void Snake::Player::eat()
    {
        _body.push_back(Arcade::Rectangle(std::make_pair(_body[_body.size() - 1].getPos().first, _body[_body.size() - 1].getPos().second), getTextureDir(Arcade::Input::RIGHT), Arcade::Color::GREEN, 10, 10));
    }

    /**
     * If the head of the snake is in the same position as the apple, return true
     *
     * @param apple The position of the apple.
     *
     * @return A boolean value.
     */
    bool Snake::Player::isEating(std::pair<int, int> apple)
    {
        if (_body[0].getPos() == apple)
            return true;
        return false;
    }

    /**
     * If the size of the snake's body is equal to the size of the map minus the
     * walls, then the player has won
     *
     * @return A boolean value.
     */
    bool Snake::Player::win()
    {
        if (_body.size() == (SIZE_MAP_X - 1) * (SIZE_MAP_Y - 1) + 1)
            return true;
        return false;
    }
}

/* It's a function that returns a pointer to an Arcade::IGameModule. */
extern "C" Arcade::IGameModule *entryGamePoint()
{
    return (new Arcade::Snake());
}