/*
** EPITECH PROJECT, 2023
** Arcade
** File description:
** test
*/

#ifndef SFML_HPP_
    #define SFML_HPP_

    #define DEBUG std::cout << "DEBUG: " << __FILE__ << ":" << __LINE__ << std::endl;


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

    #define FONT "assets/font.otf"

    #define SQUARE_SIZE 50


    namespace Arcade {
        class SFML : public Arcade::IDisplayModule {
            public:
                SFML()  : _window(sf::VideoMode(800, 600), "SFML window") {};
                ~SFML() { _window.close(); };

                Arcade::Input   getLastInput() override;
                void            clear() override;
                void            refresh() override;
                void            draw(std::shared_ptr<Arcade::IObject> object) override;
                bool            doLoop() override { return _window.isOpen(); };

            private:
                void                drawRectangle(Arcade::Rectangle *rectangle);
                void                drawText(Arcade::Text *text);
                void                drawCircle(Arcade::Circle *circle);
                static sf::Color    arcadeColorToSFMLColor(Arcade::Color color);
                sf::RenderWindow    _window;
        };
    }

    extern "C" Arcade::IDisplayModule *entryDisplayPoint();

#endif /* !SFML_HPP_ */
