/*
** EPITECH PROJECT, 2023
** Arcade
** File description:
** test
*/

#include "sfml3d.hpp"

namespace Arcade {

    /**
     * It returns the last input from the user
     *
     * @return The last input from the user.
     */
    Input SFML3D::getLastInput()
    {
        sf::Event   event = {};

        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                exit(0);
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::F5)
                    return (Input::MENU);
                if (event.key.code == sf::Keyboard::F6)
                    return (Input::RESTART);
                if (event.key.code == sf::Keyboard::Up)
                    return (Input::UP);
                if (event.key.code == sf::Keyboard::Down)
                    return (Input::DOWN);
                if (event.key.code == sf::Keyboard::Left)
                    return (Input::LEFT);
                if (event.key.code == sf::Keyboard::Right)
                    return (Input::RIGHT);
                if (event.key.code == sf::Keyboard::Enter)
                    return (Input::ENTER);
                if (event.key.code == sf::Keyboard::F1) {
                    _window.close();
                    return (Input::PREV_LIB);
                }
                if (event.key.code == sf::Keyboard::F2) {
                    _window.close();
                    return (Input::NEXT_LIB);
                }
                if (event.key.code == sf::Keyboard::A)
                    return (Input::A);
                if (event.key.code == sf::Keyboard::B)
                    return (Input::B);
                if (event.key.code == sf::Keyboard::C)
                    return (Input::C);
                if (event.key.code == sf::Keyboard::D)
                    return (Input::D);
                if (event.key.code == sf::Keyboard::E)
                    return (Input::E);
                if (event.key.code == sf::Keyboard::F)
                    return (Input::F);
                if (event.key.code == sf::Keyboard::G)
                    return (Input::G);
                if (event.key.code == sf::Keyboard::H)
                    return (Input::H);
                if (event.key.code == sf::Keyboard::I)
                    return (Input::I);
                if (event.key.code == sf::Keyboard::J)
                    return (Input::J);
                if (event.key.code == sf::Keyboard::K)
                    return (Input::K);
                if (event.key.code == sf::Keyboard::L)
                    return (Input::L);
                if (event.key.code == sf::Keyboard::M)
                    return (Input::M);
                if (event.key.code == sf::Keyboard::N)
                    return (Input::N);
                if (event.key.code == sf::Keyboard::O)
                    return (Input::O);
                if (event.key.code == sf::Keyboard::P)
                    return (Input::P);
                if (event.key.code == sf::Keyboard::Q)
                    return (Input::Q);
                if (event.key.code == sf::Keyboard::R)
                    return (Input::R);
                if (event.key.code == sf::Keyboard::S)
                    return (Input::S);
                if (event.key.code == sf::Keyboard::T)
                    return (Input::T);
                if (event.key.code == sf::Keyboard::U)
                    return (Input::U);
                if (event.key.code == sf::Keyboard::V)
                    return (Input::V);
                if (event.key.code == sf::Keyboard::W)
                    return (Input::W);
                if (event.key.code == sf::Keyboard::X)
                    return (Input::X);
                if (event.key.code == sf::Keyboard::Y)
                    return (Input::Y);
                if (event.key.code == sf::Keyboard::Z)
                    return (Input::Z);
            }
        }
        return (Input::UNKNOWN);
    }

    /**
     * It clears the window
     */
    void SFML3D::clear()
    {
        _window.clear(sf::Color::Black);
    }

    /**
     * It refreshes the window
     */
    void SFML3D::refresh()
    {
        _window.display();
    }

    /**
     * If the object is a rectangle, draw it as a rectangle, if it's a text, draw
     * it as a text, if it's a circle, draw it as a circle
     *
     * @param object The object to draw
     */
    void SFML3D::draw(std::shared_ptr<IObject> object)
    {
        auto    rectangle   = dynamic_cast<Arcade::Rectangle *>(object.get());
        auto    circle      = dynamic_cast<Circle *>(object.get());
        auto    text        = dynamic_cast<Text *>(object.get());

        if (rectangle != nullptr)
            drawRectangle(rectangle);
        else if (text != nullptr)
            drawText(text);
        else if (circle != nullptr)
            drawCircle(circle);
    }

    /**
     * It draws a rectangle
     *
     * @param rectangle The rectangle to draw
     */
    void SFML3D::drawRectangle(Arcade::Rectangle *rectangle)
    {
        sf::Texture         texture;
        float x = (float)rectangle->getPos().first * SQUARE_SIZE;
        float y = (float)rectangle->getPos().second * SQUARE_SIZE;
        sf::ConvexShape     shape(6);

        shape.setPoint(0, sf::Vector2f(x + (float)rectangle->getWidth() * SQUARE_SIZE, y));
        shape.setPoint(1, sf::Vector2f(x + (float)rectangle->getWidth() * SQUARE_SIZE + PROF, y + PROF));
        shape.setPoint(2, sf::Vector2f(x + (float)rectangle->getWidth() * SQUARE_SIZE + PROF,y + PROF + (float)rectangle->getHeight() * SQUARE_SIZE));
        shape.setPoint(3, sf::Vector2f(x + PROF, y + (float)rectangle->getHeight() * SQUARE_SIZE + PROF));
        shape.setPoint(4, sf::Vector2f(x, y + (float)rectangle->getHeight() * SQUARE_SIZE));
        shape.setPoint(5, sf::Vector2f(x, y));

        if (access(rectangle->getTexture().value().c_str(), F_OK ) != -1 && texture.loadFromFile(rectangle->getTexture().value())) {
            shape.setTexture(&texture);
            _window.draw(shape);
        }
        else {
            shape.setFillColor(arcadeColorToSFMLColor(rectangle->getColor()));
            _window.draw(shape);
            drawLine(sf::Vector2f(x, y),
                        sf::Vector2f(x + (float)rectangle->getWidth() * SQUARE_SIZE, y),
                        sf::Color::Black);
            drawLine(sf::Vector2f(x, y + (float)rectangle->getHeight() * SQUARE_SIZE),
                        sf::Vector2f(x + (float)rectangle->getWidth() * SQUARE_SIZE, y + (float)rectangle->getHeight() * SQUARE_SIZE),
                        sf::Color::Black);
            drawLine(sf::Vector2f(x, y),
                        sf::Vector2f(x, y + (float)rectangle->getHeight() * SQUARE_SIZE),
                        sf::Color::Black);
            drawLine(sf::Vector2f(x + (float)rectangle->getWidth() * SQUARE_SIZE, y),
                        sf::Vector2f(x + (float)rectangle->getWidth() * SQUARE_SIZE, y + (float)rectangle->getHeight() * SQUARE_SIZE),
                        sf::Color::Black);
            drawLine(sf::Vector2f(x + (float)rectangle->getWidth() * SQUARE_SIZE, y),
                        sf::Vector2f(x + (float)rectangle->getWidth() * SQUARE_SIZE + PROF, y + PROF),
                        sf::Color::Black);
            drawLine(sf::Vector2f(x + (float)rectangle->getWidth() * SQUARE_SIZE, y + (float)rectangle->getHeight() * SQUARE_SIZE),
                        sf::Vector2f(x + (float)rectangle->getWidth() * SQUARE_SIZE + PROF, y + PROF + (float)rectangle->getHeight() * SQUARE_SIZE),
                        sf::Color::Black);
            drawLine(sf::Vector2f(x, y + (float)rectangle->getHeight() * SQUARE_SIZE),
                        sf::Vector2f(x + PROF, y + (float)rectangle->getHeight() * SQUARE_SIZE + PROF),
                        sf::Color::Black);
            drawLine(sf::Vector2f(x + PROF + (float)rectangle->getWidth() * SQUARE_SIZE, y + PROF),
                     sf::Vector2f(x + PROF + (float)rectangle->getWidth() * SQUARE_SIZE, y + PROF + (float)rectangle->getHeight() * SQUARE_SIZE),
                     sf::Color::Black);
            drawLine(sf::Vector2f(x + PROF, y + PROF + (float)rectangle->getHeight() * SQUARE_SIZE),
                        sf::Vector2f(x + (float)rectangle->getWidth() * SQUARE_SIZE + PROF, y + PROF + (float)rectangle->getHeight() * SQUARE_SIZE),
                        sf::Color::Black);
        }
    }

    /**
     * It draws a text on the screen
     *
     * @param text The text to draw
     */
    void SFML3D::drawText(Arcade::Text *text)
    {
        sf::Text    sfText;
        sf::Font    font;

        sfText.setString(text->getText());
        sfText.setPosition((float)text->getPos().first * SQUARE_SIZE, (float)text->getPos().second * SQUARE_SIZE);
        sfText.setCharacterSize((unsigned int)text->getSize() / 1.2);
        sfText.setFillColor(arcadeColorToSFMLColor(text->getColor()));
        if (access(FONT, F_OK ) != -1 && font.loadFromFile(FONT))
            sfText.setFont(font);
        _window.draw(sfText);
    }

    /**
     * It draws a circle on the screen
     *
     * @param circle The circle to draw
     */
    void SFML3D::drawCircle(Arcade::Circle *circle)
    {
        sf::Texture     texture;
        sf::CircleShape sfCircle((float)circle->getRadius() * SQUARE_SIZE / 2);

        sfCircle.setPosition((float)circle->getPos().first * SQUARE_SIZE, (float)circle->getPos().second * SQUARE_SIZE);
        if (access(circle->getTexture().value().c_str(), F_OK ) != -1 && texture.loadFromFile(circle->getTexture().value()))
            sfCircle.setTexture(&texture);
        else
            sfCircle.setFillColor(arcadeColorToSFMLColor(circle->getColor()));
        _window.draw(sfCircle);
    }

    /**
     * It draws a line between two points
     *
     * @param pos1 The first position of the line
     * @param pos2 The position of the second point of the line.
     * @param color The color of the line.
     */
    void SFML3D::drawLine(sf::Vector2f pos1, sf::Vector2f pos2, sf::Color color)
    {
        sf::Vertex line[] =
        {
            sf::Vertex(pos1, color),
            sf::Vertex(pos2, color)
        };

        _window.draw(line, 2, sf::Lines);
    }

    /**
     * It converts an Arcade::Color to a sf::Color
     *
     * @param color The color of the text
     *
     * @return A sf::Color
     */
    sf::Color SFML3D::arcadeColorToSFMLColor(Arcade::Color color)
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

    /**
     * This function checks if a certain amount of time has passed and returns
     * true if it has.
     *
     * @return The function `doLoop()` returns a boolean value. If the elapsed
     * time since the last loop iteration is less than the specified delay
     * (`DELAY`), the function returns `false`, indicating that the loop should
     * not continue. Otherwise, the function returns `true`, indicating that the
     * loop should continue.
     */
    bool SFML3D::doLoop()
    {
        if (_clock.getElapsedTime().asMilliseconds() < DELAY)
            return (false);
        _clock.restart();
        return (true);
    }
}

/**
 * @brief Get a pointer to the SFML class
 *
 * @return pointer to SFML class
 */
extern "C" Arcade::IDisplayModule *entryDisplayPoint()
{
    return (new Arcade::SFML3D());
}