/*
** EPITECH PROJECT, 2023
** Arcade
** File description:
** test
*/

#ifndef SFML3D_HPP_
    #define SFML3D_HPP_

    #define DEBUG std::cout << "DEBUG: " << __FILE__ << ":" << __LINE__ << std::endl;
    #define DELAY 200

    #include <iostream>
    #include <memory>
    #include "../../IObject.hpp"
    #include "../../Input.hpp"
    #include "../../IDisplayModule.hpp"
    #include <SFML/Window.hpp>
    #include <SFML/Graphics.hpp>
    #include <sys/stat.h>
    #include <unistd.h>
    #include <string>
    #include <fstream>

    #define FONT "assets/font.ttf"

    #define SQUARE_SIZE 40
    #define PROF 20


    namespace Arcade {
        class SFML3D : public Arcade::IDisplayModule {
            public:
                SFML3D()  : _window(sf::VideoMode(800, 600), "SFML3D window") {};
                ~SFML3D() { _window.close(); };

                Arcade::Input   getLastInput() override;
                void            clear() override;
                void            refresh() override;
                void            draw(std::shared_ptr<Arcade::IObject> object) override;
                bool            doLoop() override;

            private:
                void                drawRectangle(Arcade::Rectangle *rectangle);
                void                drawText(Arcade::Text *text);
                void                drawCircle(Arcade::Circle *circle);
                static sf::Color    arcadeColorToSFMLColor(Arcade::Color color);
                void                drawLine(sf::Vector2f pos1, sf::Vector2f pos2, sf::Color color);
                sf::RenderWindow    _window;
                sf::Clock           _clock;
        };
    }

    extern "C" Arcade::IDisplayModule *entryDisplayPoint();

#endif /* !SFML3D_HPP_ */
