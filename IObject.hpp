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
#include <optional>


namespace Arcade {
    /*Defining a list of colors that can be used in the game.*/
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
            /*It's a destructor.*/
            virtual ~IObject() = default;
    };

    class Text : public IObject {
        public:
            /*It's a constructor.*/
            Text(std::pair<int, int> pos, std::string text, Arcade::Color color, int size) : _pos(pos), _text(text), _color(color), _size(size) {};
            ~Text() override = default;

            /*Get positions of text.*/
            std::pair<int, int> getPos() const { return _pos; };

            /*Get text content.*/
            std::string getText() const { return _text; };

            /*Get color of text .*/
            Arcade::Color getColor() const { return _color; };

            /*Get size of text.*/
            int getSize() const { return _size; };

        private:
            std::pair<int, int> _pos;
            std::string _text;
            Arcade::Color _color;
            int _size;
    };

    class Rectangle : public IObject {
        public:
            /*It's a constructor.*/
            Rectangle(std::pair<int, int> pos, const std::optional<std::string> &texture, Arcade::Color color, int width, int height) : _pos(pos), _texture(texture), _color(color), _width(width), _height(height) {};
            ~Rectangle() override = default;

            /*Get positions of rectangle.*/
            std::pair<int, int> getPos() const { return _pos; };

            /*Get rectangle texture.*/
            std::optional<std::string> getTexture() const { return _texture; };

            /*Get color of rectangle .*/
            Arcade::Color getColor() const { return _color; };

            /*Get width of rectangle .*/
            int getWidth() const { return _width; };

            /*Get height of rectangle .*/
            int getHeight() const { return _height; };

        private:
            std::pair<int, int> _pos;
            std::optional<std::string> _texture;
            Arcade::Color _color;
            int _width;
            int _height;
    };

    class Circle : public IObject {
        public:
            /*Constructor*/
            Circle(std::pair<int, int> pos, const std::optional<std::string> &texture, Arcade::Color color, int radius) : _pos(pos), _texture(texture), _color(color), _radius(radius) {};
            ~Circle() override = default;

            /*Get positions of circle.*/
            std::pair<int, int> getPos() const { return _pos; };

            /*Get circle texture.*/
            std::optional<std::string> getTexture() const { return _texture; };

            /*Get color of circle .*/
            Arcade::Color getColor() const { return _color; };

            /*Get radius of circle .*/
            int getRadius() const { return _radius; };

        private:
            std::pair<int, int> _pos;
            std::optional<std::string> _texture;
            Arcade::Color _color;
            int _radius;
    };

    class Sound : public IObject {
        public:
            /*Constructor*/
            Sound(std::string path, int volume) : _path(path), _volume(volume) {};
            ~Sound() override = default;

            /*Get path of sound.*/
            std::string getPath() const { return _path; };

            /*Get volume of sound .*/
            int getVolume() const { return _volume; };
        private:
            std::string _path;
            int _volume;
    };

}

#endif /*IOBJECT_HPP_*/