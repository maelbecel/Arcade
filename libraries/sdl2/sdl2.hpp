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
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_ttf.h>
    #include <SDL2/SDL_image.h>
    #include <sys/stat.h>
    #include <unistd.h>
    #include <string>
    #include <fstream>
    #include <time.h>
    #include <optional>
    #include <unordered_map>

    #define FONT "assets/font.ttf"

    #define SQUARE_SIZE 50


    namespace Arcade {
        class SDL2 : public Arcade::IDisplayModule {
            public:
                SDL2();
                ~SDL2();

                Arcade::Input   getLastInput() override;
                void            clear() override;
                void            refresh() override;
                void            draw(std::shared_ptr<Arcade::IObject> object) override;
                bool            doLoop() override;

            private:
                class RGBAColor {
                    public:
                        RGBAColor() : _r(0), _g(0), _b(0), _a(0) {};
                        RGBAColor(Arcade::Color);
                        RGBAColor(int r, int g, int b, int a) : _r(r), _g(g), _b(b), _a(a) {};
                        ~RGBAColor() = default;
                        int _r;
                        int _g;
                        int _b;
                        int _a;
                };
                bool                loadTexture(std::string path);
                void                drawRectangle(Arcade::Rectangle *rectangle);
                void                drawText(Arcade::Text *text);
                void                drawCircle(Arcade::Circle *circle);
                SDL_Window          *_window;
                SDL_Surface         *_surface;
                SDL_Renderer        *_renderer;
                clock_t             _clock = clock();
                std::unordered_map<std::string, SDL_Texture *> _textures;
        };
    }

    extern "C" Arcade::IDisplayModule *entryDisplayPoint();

#endif /* !SFML_HPP_ */
