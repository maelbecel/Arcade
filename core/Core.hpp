/*
** EPITECH PROJECT, 2023
** Arcade
** File description:
** Core
*/

#ifndef CORE_HPP_
    #define CORE_HPP_

    #include "../IDisplayModule.hpp"
    #include "../IGameModule.hpp"

    namespace Arcade {
        class Core {
            public:
                Core(std::string path): _displaypath(path), _gamepath("") {};
                ~Core() = default;

                void setDisplayPath(std::string path) { _displaypath = path; };
                void setGamePath(std::string path) { _gamepath = path; };
                std::string getDisplayPath() { return _displaypath; };
                std::string getGamePath() { return _gamepath; };

                void setDisplay(IDisplayModule *display) { _display = display; };
                void setGame(IGameModule *game) { _game = game; };
                IDisplayModule *getDisplay() { return _display; };
                IGameModule *getGame() { return _game; };

            protected:
            private:
                std::string _displaypath;
                std::string _gamepath;
                IDisplayModule *_display;
                IGameModule *_game;
        };
    };

#endif /* !CORE_HPP_ */
