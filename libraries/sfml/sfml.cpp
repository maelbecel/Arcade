/*
** EPITECH PROJECT, 2023
** Arcade
** File description:
** test
*/

#include "sfml.hpp"

namespace Arcade {

    /**
     * It returns the last input from the user
     *
     * @return The last input from the user.
     */
    Input SFML::getLastInput()
    {
        sf::Event   event = {};

        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                return (Input::ESCAPE);
            if (event.type != sf::Event::KeyPressed)
                continue;
            switch (event.key.code) {
                case sf::Keyboard::Escape:
                    return (Input::ESCAPE);
                case sf::Keyboard::F1:
                    return (Input::PREV_LIB);
                case sf::Keyboard::F2:
                    return (Input::NEXT_LIB);
                case sf::Keyboard::F3:
                    return (Input::PREV_GAME);
                case sf::Keyboard::F4:
                    return (Input::NEXT_GAME);
                case sf::Keyboard::F5:
                    return (Input::MENU);
                case sf::Keyboard::F6:
                    return (Input::RESTART);
                case sf::Keyboard::Up:
                    return (Input::UP);
                case sf::Keyboard::Down:
                    return (Input::DOWN);
                case sf::Keyboard::Left:
                    return (Input::LEFT);
                case sf::Keyboard::Right:
                    return (Input::RIGHT);
                case sf::Keyboard::Enter:
                    return (Input::ENTER);
                case sf::Keyboard::Backspace:
                    return (Input::BACKSPACE);
                case sf::Keyboard::A:
                    return (Input::A);
                case sf::Keyboard::B:
                    return (Input::B);
                case sf::Keyboard::C:
                    return (Input::C);
                case sf::Keyboard::D:
                    return (Input::D);
                case sf::Keyboard::E:
                    return (Input::E);
                case sf::Keyboard::F:
                    return (Input::F);
                case sf::Keyboard::G:
                    return (Input::G);
                case sf::Keyboard::H:
                    return (Input::H);
                case sf::Keyboard::I:
                    return (Input::I);
                case sf::Keyboard::J:
                    return (Input::J);
                case sf::Keyboard::K:
                    return (Input::K);
                case sf::Keyboard::L:
                    return (Input::L);
                case sf::Keyboard::M:
                    return (Input::M);
                case sf::Keyboard::N:
                    return (Input::N);
                case sf::Keyboard::O:
                    return (Input::O);
                case sf::Keyboard::P:
                    return (Input::P);
                case sf::Keyboard::Q:
                    return (Input::Q);
                case sf::Keyboard::R:
                    return (Input::R);
                case sf::Keyboard::S:
                    return (Input::S);
                case sf::Keyboard::T:
                    return (Input::T);
                case sf::Keyboard::U:
                    return (Input::U);
                case sf::Keyboard::V:
                    return (Input::V);
                case sf::Keyboard::W:
                    return (Input::W);
                case sf::Keyboard::X:
                    return (Input::X);
                case sf::Keyboard::Y:
                    return (Input::Y);
                case sf::Keyboard::Z:
                    return (Input::Z);
                default:
                    break;
            }
        }
        return (Input::UNKNOWN);
    }

    /**
     * It clears the window
     */
    void SFML::clear()
    {
        _window.clear(sf::Color::Black);
    }

    /**
     * It refreshes the window
     */
    void SFML::refresh()
    {
        _window.display();
    }

    /**
     * If the object is a rectangle, draw it as a rectangle, if it's a text, draw
     * it as a text, if it's a circle, draw it as a circle
     *
     * @param object The object to draw
     */
    void SFML::draw(std::shared_ptr<IObject> object)
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
    void SFML::drawRectangle(Arcade::Rectangle *rectangle)
    {
        sf::Texture         texture;
        sf::RectangleShape  rect(sf::Vector2f((float)rectangle->getWidth() * SQUARE_SIZE, (float)rectangle->getHeight() * SQUARE_SIZE));

        rect.setPosition((float)rectangle->getPos().first * SQUARE_SIZE, (float)rectangle->getPos().second * SQUARE_SIZE);
        if (rectangle->getTexture().has_value() && (rectangle->getTexture().value().c_str(), F_OK ) != -1 && texture.loadFromFile(rectangle->getTexture().value()))
            rect.setTexture(&texture);
        else
            rect.setFillColor(arcadeColorToSFMLColor(rectangle->getColor()));
        _window.draw(rect);
    }

    /**
     * It draws a text on the screen
     *
     * @param text The text to draw
     */
    void SFML::drawText(Arcade::Text *text)
    {
        sf::Text    sfText;
        sf::Font    font;

        sfText.setString(text->getText());
        sfText.setPosition((float)text->getPos().first * SQUARE_SIZE, (float)text->getPos().second * SQUARE_SIZE);
        sfText.setCharacterSize((unsigned int)text->getSize());
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
    void SFML::drawCircle(Arcade::Circle *circle)
    {
        sf::Texture     texture;
        sf::CircleShape sfCircle((float)circle->getRadius() * SQUARE_SIZE / 2);

        sfCircle.setPosition((float)circle->getPos().first * SQUARE_SIZE, (float)circle->getPos().second * SQUARE_SIZE);
        if (circle->getTexture().has_value() && access(circle->getTexture().value().c_str(), F_OK ) != -1 && texture.loadFromFile(circle->getTexture().value()))
            sfCircle.setTexture(&texture);
        else
            sfCircle.setFillColor(arcadeColorToSFMLColor(circle->getColor()));
        _window.draw(sfCircle);
    }

    /**
     * It converts an Arcade::Color to a sf::Color
     *
     * @param color The color of the text
     *
     * @return A sf::Color
     */
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

    /**
     * The function checks if a certain amount of time has passed and returns true
     * if it has.
     *
     * @return The function `doLoop()` returns a boolean value. If the elapsed
     * time since the last loop iteration is less than a certain delay (in
     * milliseconds), the function returns `false`, indicating that the loop
     * should not continue. Otherwise, the function returns `true`, indicating
     * that the loop should continue.
     */
    bool SFML::doLoop()
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
    return (new Arcade::SFML());
}