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
            Text(std::pair<int, int> pos, std::string text, Arcade::Color color, int size);
            ~Text() override = default;

            std::pair<int, int> getPos() const;
            std::string getText() const;
            Arcade::Color getColor() const;
            int getSize() const;

        private:
            std::pair<int, int> _pos;
            std::string _text;
            Arcade::Color _color;
            int _size;
    };

    class Rectangle : public IObject {
        public:
            Rectangle(std::pair<int, int> pos, std::string texture, Arcade::Color color, int width, int height);
            ~Rectangle() override = default;

            std::pair<int, int> getPos() const;
            std::string getTexture() const;
            Arcade::Color getColor() const;
            int getWidth() const;
            int getHeight() const;

        private:
            std::pair<int, int> _pos;
            std::string _texture;
            Arcade::Color _color;
            int _width;
            int _height;
    };

    class Circle : public IObject {
        public:
            Circle(std::pair<int, int> pos, std::string texture, Arcade::Color color, int radius);
            ~Circle() override = default;

            std::pair<int, int> getPos() const;
            std::string getTexture() const;
            Arcade::Color getColor() const;
            int getRadius() const;

        private:
            std::pair<int, int> _pos;
            std::string _texture;
            Arcade::Color _color;
            int _radius;
    };

    class Sound : public IObject {
        public:
            Sound(std::string path, int volume);
            ~Sound() override = default;

            std::string getPath() const;
            int getVolume() const;
        private:
            std::string _path;
            int _volume;
    };

}

#endif /*IOBJECT_HPP_*/