/*
** EPITECH PROJECT, 2023
** Arcade
** File description:
** test
*/

#include "sdl2.hpp"

namespace Arcade {

    SDL2::SDL2()
    {
        _window = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
        if (!_window)
            throw std::runtime_error("SDL_CreateWindow Error: " + std::string(SDL_GetError()));
        _surface = SDL_GetWindowSurface(_window);
        if (!_surface)
            throw std::runtime_error("SDL_GetWindowSurface Error: " + std::string(SDL_GetError()));
        _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
        if (!_renderer)
            throw std::runtime_error("SDL_CreateRenderer Error: " + std::string(SDL_GetError()));
    }

    SDL2::~SDL2()
    {
        SDL_FreeSurface(_surface);
        SDL_DestroyWindow(_window);
        SDL_Quit();
    }

    /**
     * It returns the last input from the user
     *
     * @return The last input from the user.
     */
    Input SDL2::getLastInput()
    {
        return (Input::UNKNOWN);
    }

    /**
     * It clears the window
     */
    void SDL2::clear()
    {
        SDL_RenderClear(_renderer);
    }

    /**
     * It refreshes the window
     */
    void SDL2::refresh()
    {
        SDL_RenderPresent(_renderer);
    }

    /**
     * If the object is a rectangle, draw it as a rectangle, if it's a text, draw
     * it as a text, if it's a circle, draw it as a circle
     *
     * @param object The object to draw
     */
    void SDL2::draw(std::shared_ptr<IObject> object)
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
    void SDL2::drawRectangle(Arcade::Rectangle *rectangle)
    {
        SDL_Rect   rect;
        rect.x = rectangle->getPos().first * SQUARE_SIZE;
        rect.y = rectangle->getPos().second * SQUARE_SIZE;
        rect.w = rectangle->getWidth() * SQUARE_SIZE;
        rect.h = rectangle->getHeight() * SQUARE_SIZE;
        RGBAColor color = rectangle->getColor();

        SDL_SetRenderDrawColor(_renderer, color._r, color._g, color._b, color._a);
        SDL_RenderFillRect(_renderer, &rect);
        SDL_RenderDrawRect(_renderer, &rect);
    }

    /**
     * It draws a text on the screen
     *
     * @param text The text to draw
     */
    void SDL2::drawText(Arcade::Text *text)
    {
        // TTF_FONT *font = TTF_OpenFont("arial.ttf", 24);
        // if (!font)
        //     throw std::runtime_error("TTF_OpenFont Error: " + std::string(TTF_GetError()));

    }

    /**
     * It draws a circle on the screen
     *
     * @param circle The circle to draw
     */
    void SDL2::drawCircle(Arcade::Circle *circle)
    {
        std::cout << __FUNCTION__ << std::endl;
    }

    SDL2::RGBAColor::RGBAColor(Arcade::Color color)
    {
        switch (color) {
            case Arcade::Color::BLACK:
                _r = 0;
                _g = 0;
                _b = 0;
                _a = 255;
                break;
            case Arcade::Color::WHITE:
                _r = 255;
                _g = 255;
                _b = 255;
                _a = 255;
                break;
            case Arcade::Color::RED:
                _r = 255;
                _g = 0;
                _b = 0;
                _a = 255;
                break;
            case Arcade::Color::GREEN:
                _r = 0;
                _g = 255;
                _b = 0;
                _a = 255;
                break;
            case Arcade::Color::BLUE:
                _r = 0;
                _g = 0;
                _b = 255;
                _a = 255;
                break;
            case Arcade::Color::YELLOW:
                _r = 255;
                _g = 255;
                _b = 0;
                _a = 255;
                break;
            case Arcade::Color::MAGENTA:
                _r = 255;
                _g = 0;
                _b = 255;
                _a = 255;
                break;
            case Arcade::Color::CYAN:
                _r = 0;
                _g = 255;
                _b = 255;
                _a = 255;
                break;
            default:
                _r = 0;
                _g = 0;
                _b = 0;
                _a = 255;
                break;
        }
    }

}

/**
 * @brief Get a pointer to the SDL2 class
 *
 * @return pointer to SDL2 class
 */
extern "C" Arcade::IDisplayModule *entryDisplayPoint()
{
    return (new Arcade::SDL2());
}