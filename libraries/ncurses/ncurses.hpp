/*
** EPITECH PROJECT, 2023
** Arcade
** File description:
** test
*/

#ifndef NCURSES_HPP_
    #define NCURSES_HPP_

    #include <iostream>
    #include <memory>
    #include "../../IObject.hpp"
    #include "../../Input.hpp"
    #include "../../IDisplayModule.hpp"
    #include <ncurses.h>
    #include <math.h>

    #define SQUARE_WIDTH 4
    #define SQUARE_HEIGHT (SQUARE_WIDTH / 2)

    namespace Arcade {
        class NCurses : public Arcade::IDisplayModule {
        public:
            NCurses();
            ~NCurses();

            Arcade::Input   getLastInput() override;
            void            clear() override;
            void            refresh() override;
            void            draw(std::shared_ptr<Arcade::IObject> object) override;
            bool            doLoop() override { return true; };

        private:
            void    drawRectangle(Arcade::Rectangle *rectangle);
            void    drawText(Arcade::Text *text);
            void    drawCircle(Arcade::Circle *circle);
            void    defineColor();
        };
    }

    extern "C" Arcade::IDisplayModule *entryDisplayPoint();

#endif /* !NCURSES_HPP_ */