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
    #include <unistd.h>
    #include "../../IObject.hpp"
    #include "../../Input.hpp"
    #include "../../IDisplayModule.hpp"
    #include <ncurses.h>
    #include <math.h>
    #include <time.h>

    #define SQUARE_WIDTH 4
    #define KEY_ESCAPE 27
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
            bool            doLoop() override;

        private:
            void    drawRectangle(Arcade::Rectangle *rectangle);
            void    drawText(Arcade::Text *text);
            void    drawCircle(Arcade::Circle *circle);
            void    defineColor();
            clock_t _clock = clock();
        };
    }

    extern "C" Arcade::IDisplayModule *entryDisplayPoint();

#endif /* !NCURSES_HPP_ */