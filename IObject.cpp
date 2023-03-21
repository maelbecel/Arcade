/*
** EPITECH PROJECT, 2023
** Arcade
** File description:
** IObject
*/

#include "IObject.hpp"

namespace Arcade {
    Text::Text(std::pair<int, int> pos, std::string text, Arcade::Color color, int size) : _pos(pos), _text(text), _color(color), _size(size) {}

    std::pair<int, int> Text::getPos() const {
        return _pos;
    }

    std::string Text::getText() const {
        return _text;
    }

    Arcade::Color Text::getColor() const {
        return _color;
    }

    int Text::getSize() const {
        return _size;
    }

    Rectangle::Rectangle(std::pair<int, int> pos, std::string texture, Arcade::Color color, int width, int height) : _pos(pos), _texture(texture), _color(color), _width(width), _height(height) {}

    std::pair<int, int> Rectangle::getPos() const {
        return _pos;
    }

    std::string Rectangle::getTexture() const {
        return _texture;
    }

    Arcade::Color Rectangle::getColor() const {
        return _color;
    }

    int Rectangle::getWidth() const {
        return _width;
    }

    int Rectangle::getHeight() const {
        return _height;
    }

    Circle::Circle(std::pair<int, int> pos, std::string texture, Arcade::Color color, int radius) : _pos(pos), _texture(texture), _color(color), _radius(radius) {}

    std::pair<int, int> Circle::getPos() const {
        return _pos;
    }

    std::string Circle::getTexture() const {
        return _texture;
    }

    Arcade::Color Circle::getColor() const {
        return _color;
    }

    int Circle::getRadius() const {
        return _radius;
    }

    Sound::Sound(std::string path, int volume) : _path(path), _volume(volume) {}

    std::string Sound::getPath() const {
        return _path;
    }

    int Sound::getVolume() const {
        return _volume;
    }
};