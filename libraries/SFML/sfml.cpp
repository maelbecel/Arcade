/*
** EPITECH PROJECT, 2023
** Arcade
** File description:
** test
*/

#include "sfml.hpp"

namespace Arcade {

    Input SFML::getLastInput()
    {
        sf::Event event;
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                exit(0);
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up)
                    return (Input::UP);
                if (event.key.code == sf::Keyboard::Down)
                    return (Input::DOWN);
                if (event.key.code == sf::Keyboard::Left)
                    return (Input::LEFT);
                if (event.key.code == sf::Keyboard::Right)
                    return (Input::RIGHT);
            }
        }
        return (Input::UNKNOWN);
    }

    void SFML::clear()
    {
        _window.clear(sf::Color::White);
    }

    void SFML::refresh()
    {
        _window.display();
    }

    void SFML::draw(std::shared_ptr<IObject> object)
    {
        Arcade::Rectangle *rectangle = dynamic_cast<Arcade::Rectangle *>(object.get());
        if (dynamic_cast<Arcade::Rectangle *>(object.get()))
            drawRectangle(rectangle);

        Text *text = dynamic_cast<Text *>(object.get());
        if (text != nullptr)
            drawText(text);

        Circle *circle = dynamic_cast<Circle *>(object.get());
        if (circle != nullptr)
            drawCircle(circle);
    }

    void SFML::drawRectangle(Arcade::Rectangle *rectangle)
    {
        sf::Texture texture;
        sf::RectangleShape rect(sf::Vector2f(rectangle->getWidth(), rectangle->getHeight()));
        rect.setPosition(rectangle->getPos().first, rectangle->getPos().second);
        if (access(rectangle->getTexture().c_str(), F_OK ) != -1 && texture.loadFromFile(rectangle->getTexture()))
            rect.setTexture(&texture);
        else
            rect.setFillColor(arcadeColorToSFMLColor(rectangle->getColor()));
        _window.draw(rect);
    }

    sf::Color SFML::arcadeColorToSFMLColor(Arcade::Color color)
    {
        switch (color) {
            case Arcade::Color::BLACK:
                return (sf::Color::Black);
            case Arcade::Color::RED:
                return (sf::Color::Red);
            case Arcade::Color::GREEN:
                return (sf::Color::Green);
            case Arcade::Color::YELLOW:
                return (sf::Color::Yellow);
            case Arcade::Color::BLUE:
                return (sf::Color::Blue);
            case Arcade::Color::MAGENTA:
                return (sf::Color::Magenta);
            case Arcade::Color::CYAN:
                return (sf::Color::Cyan);
            case Arcade::Color::WHITE:
                return (sf::Color::White);
            default:
                return (sf::Color::Black);
        }
    }
}

extern "C" Arcade::IDisplayModule *entryPoint()
{
    return (new Arcade::SFML());
}