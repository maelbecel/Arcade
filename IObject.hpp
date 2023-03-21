/*
** EPITECH PROJECT, 2023
** B_OOP_400_REN_4_1_arcade_jason_lagoute
** File description:
** IObject.hpp
*/
#ifndef IOBJECT_HPP_
#define IOBJECT_HPP_

#include <string>
#include <utility>

namespace Arcade {
    enum Color {
        BLACK,
        RED,
        GREEN,
        YELLOW,
        BLUE,
        MAGENTA,
        CYAN,
        WHITE,
        DEFAULT
    };

    class IObject {
        public:
            virtual ~IObject() = default;
    };

    class Text : public IObject {
        public:
            Text(std::pair<int, int> pos, std::string text, Arcade::Color color, int size) : _pos(pos), _text(text), _color(color), _size(size) {};
            ~Text() override = default;

            std::pair<int, int> getPos() const { return _pos; };
            std::string getText() const { return _text; };
            Arcade::Color getColor() const { return _color; };
            int getSize() const { return _size; };

        private:
            std::pair<int, int> _pos;
            std::string _text;
            Arcade::Color _color;
            int _size;
    };

    class Rectangle : public IObject {
        public:
            Rectangle(std::pair<int, int> pos, std::string texture, Arcade::Color color, int width, int height) : _pos(pos), _texture(texture), _color(color), _width(width), _height(height) {};
            ~Rectangle() override = default;

            std::pair<int, int> getPos() const { return _pos; };
            std::string getTexture() const { return _texture; };
            Arcade::Color getColor() const { return _color; };
            int getWidth() const { return _width; };
            int getHeight() const { return _height; };

        private:
            std::pair<int, int> _pos;
            std::string _texture;
            Arcade::Color _color;
            int _width;
            int _height;
    };

    class Circle : public IObject {
        public:
            Circle(std::pair<int, int> pos, std::string texture, Arcade::Color color, int radius) : _pos(pos), _texture(texture), _color(color), _radius(radius) {};
            ~Circle() override = default;

            std::pair<int, int> getPos() const { return _pos; };
            std::string getTexture() const { return _texture; };
            Arcade::Color getColor() const { return _color; };
            int getRadius() const { return _radius; };

        private:
            std::pair<int, int> _pos;
            std::string _texture;
            Arcade::Color _color;
            int _radius;
    };

    class Sound : public IObject {
        public:
            Sound(std::string path, int volume) : _path(path), _volume(volume) {};
            ~Sound() override = default;

            std::string getPath() const { return _path; };
            int getVolume() const { return _volume; };
        private:
            std::string _path;
            int _volume;
    };

}

#endif /*IOBJECT_HPP_*/