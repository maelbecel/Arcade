/*
** EPITECH PROJECT, 2023
** Arcade
** File description:
** test
*/

#include "sdl2.hpp"

namespace Arcade {

    /**
     * It initializes SDL2 and creates a window
     */
    SDL2::SDL2()
    {
        TTF_Init();
        if (SDL_Init(SDL_INIT_VIDEO) != 0)
            throw std::runtime_error("SDL_Init Error: " + std::string(SDL_GetError()));
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

    /**
     * It destroys the window, quits the TTF library, and quits SDL
     */
    SDL2::~SDL2()
    {
        SDL_DestroyWindow(_window);
        TTF_Quit();
        SDL_Quit();
    }

    /**
     * It returns the last input from the user
     *
     * @return The last input from the user.
     */
    Input SDL2::getLastInput()
    {
        SDL_Event   event = {};

        while(SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    exit(0);
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_F5)
                        return (Input::MENU);
                    if (event.key.keysym.sym == SDLK_KP_ENTER)
                        return (Input::ENTER);
                    if (event.key.keysym.sym == SDLK_UP)
                        return (Input::UP);
                    if (event.key.keysym.sym == SDLK_DOWN)
                        return (Input::DOWN);
                    if (event.key.keysym.sym == SDLK_LEFT)
                        return (Input::LEFT);
                    if (event.key.keysym.sym == SDLK_RIGHT)
                        return (Input::RIGHT);
                    if (event.key.keysym.sym == SDLK_F1) {
                        SDL_DestroyWindow(_window);
                        SDL_Quit();
                        return (Input::PREV_LIB);
                    }
                    if (event.key.keysym.sym == SDLK_F2) {
                        SDL_FreeSurface(_surface);
                        SDL_DestroyWindow(_window);
                        SDL_Quit();
                        return (Input::NEXT_LIB);
                    } if (event.key.keysym.sym == SDLK_a)
                        return (Input::A);
                    if (event.key.keysym.sym == SDLK_b)
                        return (Input::B);
                    if (event.key.keysym.sym == SDLK_c)
                        return (Input::C);
                    if (event.key.keysym.sym == SDLK_d)
                        return (Input::D);
                    if (event.key.keysym.sym == SDLK_e)
                        return (Input::E);
                    if (event.key.keysym.sym == SDLK_f)
                        return (Input::F);
                    if (event.key.keysym.sym == SDLK_g)
                        return (Input::G);
                    if (event.key.keysym.sym == SDLK_h)
                        return (Input::H);
                    if (event.key.keysym.sym == SDLK_i)
                        return (Input::I);
                    if (event.key.keysym.sym == SDLK_j)
                        return (Input::J);
                    if (event.key.keysym.sym == SDLK_k)
                        return (Input::K);
                    if (event.key.keysym.sym == SDLK_l)
                        return (Input::L);
                    if (event.key.keysym.sym == SDLK_m)
                        return (Input::M);
                    if (event.key.keysym.sym == SDLK_n)
                        return (Input::N);
                    if (event.key.keysym.sym == SDLK_o)
                        return (Input::O);
                    if (event.key.keysym.sym == SDLK_p)
                        return (Input::P);
                    if (event.key.keysym.sym == SDLK_q)
                        return (Input::Q);
                    if (event.key.keysym.sym == SDLK_r)
                        return (Input::R);
                    if (event.key.keysym.sym == SDLK_s)
                        return (Input::S);
                    if (event.key.keysym.sym == SDLK_t)
                        return (Input::T);
                    if (event.key.keysym.sym == SDLK_u)
                        return (Input::U);
                    if (event.key.keysym.sym == SDLK_v)
                        return (Input::V);
                    if (event.key.keysym.sym == SDLK_w)
                        return (Input::W);
                    if (event.key.keysym.sym == SDLK_x)
                        return (Input::X);
                    if (event.key.keysym.sym == SDLK_y)
                        return (Input::Y);
                    if (event.key.keysym.sym == SDLK_z)
                        return (Input::Z);
                    if (event.key.keysym.sym == SDLK_BACKSPACE)
                        return (Input::BACKSPACE);
            }
        }
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
        TTF_Font    *font = TTF_OpenFont(FONT, text->getSize());
        RGBAColor   color = text->getColor();
        if (!font)
            throw std::runtime_error("TTF_OpenFont Error: " + std::string(TTF_GetError()));
        SDL_Surface *surface = TTF_RenderText_Solid(font, text->getText().c_str(), {(Uint8)color._r, (Uint8)color._g, (Uint8)color._b, (Uint8)color._a});
        if (!surface)
            throw std::runtime_error("TTF_RenderText_Solid Error: " + std::string(TTF_GetError()));
        SDL_Texture *texture = SDL_CreateTextureFromSurface(_renderer, surface);
        if (!texture)
            throw std::runtime_error("SDL_CreateTextureFromSurface Error: " + std::string(SDL_GetError()));
        SDL_Rect    rect;
        rect.x = text->getPos().first * SQUARE_SIZE;
        rect.y = text->getPos().second * SQUARE_SIZE;
        rect.w = text->getSize() * (text->getText().size() / 2);
        rect.h = text->getSize() ;
        SDL_RenderCopy(_renderer, texture, NULL, &rect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
        TTF_CloseFont(font);
    }

    /**
     * It draws a circle on the screen
     *
     * @param circle The circle to draw
     */
    void SDL2::drawCircle(Arcade::Circle *circle)
    {
        RGBAColor   color   = circle->getColor();
        int         radius  = circle->getRadius() * SQUARE_SIZE / 2;
        int         x       = circle->getPos().first * SQUARE_SIZE + radius;
        int         y       = circle->getPos().second * SQUARE_SIZE + radius;

        SDL_SetRenderDrawColor(_renderer, color._r, color._g, color._b, color._a);
        for (int i = 0; i < radius; i++) {
            for (int j = 0; j < radius; j++) {
                if (i * i + j * j <= radius * radius) {
                    SDL_RenderDrawPoint(_renderer, x + i, y + j);
                    SDL_RenderDrawPoint(_renderer, x - i, y + j);
                    SDL_RenderDrawPoint(_renderer, x + i, y - j);
                    SDL_RenderDrawPoint(_renderer, x - i, y - j);
                }
            }
        }

    }

    /**
     * It converts an Arcade::Color to an SDL2::RGBAColor
     *
     * @param color The color to convert to RGBAColor
     */
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

    bool SDL2::doLoop()
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
 * @brief Get a pointer to the sdl2 class
 *
 * @return pointer to sdl2 class
 */
extern "C" Arcade::IDisplayModule *entryDisplayPoint()
{
    return (new Arcade::SDL2());
}