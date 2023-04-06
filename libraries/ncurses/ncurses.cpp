/*
** EPITECH PROJECT, 2023
** Arcade
** File description:
** test
*/

#include "ncurses.hpp"

namespace Arcade {

    /**
     * @brief Construct a new NCurses::NCurses object
     */
    NCurses::NCurses()
    {
        initscr();
        noecho();
        keypad(stdscr, TRUE);
        nodelay(stdscr, TRUE);
        start_color();
        defineColor();
        curs_set(0);
        refresh();
    }

    /**
     * @brief Destroy the NCurses::NCurses object
     */
    NCurses::~NCurses()
    {
        endwin();
    }

    /**
     * @brief Get the last input
     * @return The last input
     */
    Input NCurses::getLastInput()
    {
        int ch = getch();

        refresh();
        switch (ch) {
            case KEY_F(5):
                return (Input::MENU);
            case KEY_F(6):
                return (Input::RESTART);
            case '\n':
                return (Input::ENTER);
            case KEY_UP:
                return (Input::UP);
            case KEY_DOWN:
                return (Input::DOWN);
            case KEY_LEFT:
                return (Input::LEFT);
            case KEY_RIGHT:
                return (Input::RIGHT);
            case KEY_F(1): {
                endwin();
                return (Input::PREV_LIB);
            }
            case KEY_F(2): {
                endwin();
                return (Input::NEXT_LIB);
            }
            case KEY_ESCAPE: {
                endwin();
                return (Input::ESCAPE);
            }
            case KEY_BACKSPACE:
                return (Input::BACKSPACE);
            case 'a':
                return (Input::A);
            case 'b':
                return (Input::B);
            case 'c':
                return (Input::C);
            case 'd':
                return (Input::D);
            case 'e':
                return (Input::E);
            case 'f':
                return (Input::F);
            case 'g':
                return (Input::G);
            case 'h':
                return (Input::H);
            case 'i':
                return (Input::I);
            case 'j':
                return (Input::J);
            case 'k':
                return (Input::K);
            case 'l':
                return (Input::L);
            case 'm':
                return (Input::M);
            case 'n':
                return (Input::N);
            case 'o':
                return (Input::O);
            case 'p':
                return (Input::P);
            case 'q':
                return (Input::Q);
            case 'r':
                return (Input::R);
            case 's':
                return (Input::S);
            case 't':
                return (Input::T);
            case 'u':
                return (Input::U);
            case 'v':
                return (Input::V);
            case 'w':
                return (Input::W);
            case 'x':
                return (Input::X);
            case 'y':
                return (Input::Y);
            case 'z':
                return (Input::Z);
            default:
                return (Input::UNKNOWN);
        }
    }

    /**
     * @brief Clear the display
     */
    void NCurses::clear()
    {
        wclear(stdscr);
    }

    /**
     * @brief Refresh the display
     */
    void NCurses::refresh()
    {
        wrefresh(stdscr);
    }

    /**
     * @brief Draw an object
     * @param object The object to draw
     */
    void NCurses::draw(std::shared_ptr<IObject> object)
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
     * @brief Draw a rectangle
     * @param rectangle The rectangle to draw
     */
    void NCurses::drawRectangle(Arcade::Rectangle *rectangle)
    {
        int x       = rectangle->getPos().first * SQUARE_WIDTH;
        int y       = rectangle->getPos().second * SQUARE_HEIGHT;
        int color   = rectangle->getColor();

        attron(COLOR_PAIR(color));
        for (int i = 0; i < rectangle->getWidth() * SQUARE_WIDTH; i++) {
            for (int j = 0; j < rectangle->getHeight() * SQUARE_HEIGHT; j++) {
                mvprintw(y + j, x + i, " ");
            }
        }
        attroff(COLOR_PAIR(color));
    }

    /**
     * @brief Draw a circle
     * @param circle The circle to draw
     */
    void NCurses::drawCircle(Circle *circle)
    {
        int x       = circle->getPos().first * SQUARE_WIDTH;
        int y       = circle->getPos().second * SQUARE_HEIGHT;
        int color   = circle->getColor();
        int radius  = circle->getRadius();

        attron(COLOR_PAIR(color));
        for (int i = 0; i < radius * SQUARE_WIDTH; i++) {
            for (int j = 0; j < radius * SQUARE_HEIGHT; j++) {
                mvprintw(y + j, x + i, " ");
            }
        }
        attroff(COLOR_PAIR(color));
    }

    /**
     * @brief Draw a text
     * @param text The text to draw
     */
    void NCurses::drawText(Text *text)
    {
        int x       = text->getPos().first * SQUARE_WIDTH;
        int y       = text->getPos().second * SQUARE_HEIGHT;
        int color   = text->getColor();

        attron(COLOR_PAIR(10 + color));
        mvprintw(y, x, text->getText().c_str());
        attroff(COLOR_PAIR(10 + color));
    }

    /**
     * @brief Define the colors
     */
    void NCurses::defineColor()
    {
        init_pair(0, COLOR_WHITE, COLOR_BLACK);
        init_pair(1, COLOR_BLACK, COLOR_RED);
        init_pair(2, COLOR_BLACK, COLOR_GREEN);
        init_pair(3, COLOR_BLACK, COLOR_YELLOW);
        init_pair(4, COLOR_BLACK, COLOR_BLUE);
        init_pair(5, COLOR_BLACK, COLOR_MAGENTA);
        init_pair(6, COLOR_BLACK, COLOR_CYAN);
        init_pair(7, COLOR_BLACK, COLOR_WHITE);
        init_pair(8, COLOR_BLACK, COLOR_WHITE);
        init_pair(10, COLOR_BLACK, COLOR_WHITE);
        init_pair(11, COLOR_RED, COLOR_BLACK);
        init_pair(12, COLOR_GREEN, COLOR_BLACK);
        init_pair(13, COLOR_YELLOW, COLOR_BLACK);
        init_pair(14, COLOR_BLUE, COLOR_BLACK);
        init_pair(15, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(16, COLOR_CYAN, COLOR_BLACK);
        init_pair(17, COLOR_WHITE, COLOR_BLACK);
        init_pair(18, COLOR_WHITE, COLOR_BLACK);
    }

    bool NCurses::doLoop()
    {
        if (clock()  - _clock >= 15000000 / 60) {
            _clock = clock();
            return (true);
        } else {
            return (false);
        }
    }
}

/**
 * @brief Get the entry point of the library
 */
extern "C" Arcade::IDisplayModule *entryDisplayPoint()
{
    return (new Arcade::NCurses());
}