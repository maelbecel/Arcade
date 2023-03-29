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
    #include <unistd.h>
    #include <dirent.h>
    #include <vector>
    #include <string>
    #include "DLLoader.hpp"

    #define MENU_PATH "lib/arcade_menu.so"

    namespace Arcade {
        class Core {
            public:
                explicit Core(std::string path): _displayPath(std::move(path)), _gamePath("libraries/menu/arcade_menu.so") {};
                ~Core() = default;

                void                        setDisplayPath(std::string path) { _displayPath = std::move(path); };
                void                        setGamePath(std::string path) { _gamePath = std::move(path); };
                void                        setDisplay(IDisplayModule *display) { _display = display; };
                void                        setDisplayLoader(DLLoader<IDisplayModule> loader) { _displayLoader = loader; };
                void                        setGameLoader(DLLoader<IGameModule> loader) { _gameLoader = loader; };
                void                        setGame(IGameModule *game) { _game = game; };
                std::string                 getGamePath() { return _gamePath; };
                std::string                 getDisplayPath() { return _displayPath; };
                IDisplayModule              *getDisplay() { return _display; };
                IGameModule                 *getGame() { return _game; };
                DLLoader<IDisplayModule>    getDisplayLoader() { return _displayLoader; };
                DLLoader<IGameModule>       getGameLoader() { return _gameLoader; };
                void                        mainLoop();
                void                        getLibs();

            private:
                std::string nextLib();
                std::string prevLib();
                bool        handleInput(Arcade::Input input);

                std::vector<std::string>    _displayLibs;
                std::vector<std::string>    _gameLibs;
                std::string                 _displayPath;
                std::string                 _gamePath;
                IDisplayModule              *_display{};
                IGameModule                 *_game{};
                DLLoader<IDisplayModule>    _displayLoader;
                DLLoader<IGameModule>       _gameLoader;
        };
    }

#endif /* !CORE_HPP_ */
