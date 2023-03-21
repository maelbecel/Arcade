/*
** EPITECH PROJECT, 2023
** Arcade
** File description:
** Core
*/

#ifndef CORE_HPP_
    #define CORE_HPP_

    #include <utility>
    #include "../IDisplayModule.hpp"
    #include "../IGameModule.hpp"
    #include <iostream>

    namespace Arcade {
        class Core {
            public:
                explicit Core(std::string path): _displayPath(std::move(path)), _gamePath("libraries/menu/arcade_menu.so") {};
                ~Core() = default;

                void setDisplayPath(std::string path) { _displayPath = std::move(path); };
                void setGamePath(std::string path) { _gamePath = std::move(path); };
                std::string getDisplayPath() { return _displayPath; };
                std::string getGamePath() { return _gamePath; };

                void setDisplay(IDisplayModule *display) { _display = display; };
                void setGame(IGameModule *game) { _game = game; };
                IDisplayModule *getDisplay() { return _display; };
                IGameModule *getGame() { return _game; };

                void mainLoop();

            protected:
            private:
                std::string _displayPath;
                std::string _gamePath;
                IDisplayModule *_display{};
                IGameModule *_game{};
        };
    }

#endif /* !CORE_HPP_ */
