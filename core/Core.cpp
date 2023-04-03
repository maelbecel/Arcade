/*
** EPITECH PROJECT, 2023
** Arcade
** File description:
** Core
*/

#include "Core.hpp"

namespace Arcade {
    /**
     * It clears the display, gets the objects from the game, draws them on the
     * display and refreshes the display
     */
    void Core::mainLoop()
    {
        std::vector<std::shared_ptr<Arcade::IObject>> objects;
        Input input;
        _game->start();
        getLibs();
        int score;

        while (true) {
            if (_display->doLoop()) {
                _display->clear();
                input = _display->getLastInput();
                if (!handleInput(input))
                    break;
                objects = _game->loop(input);
                for (auto &object : objects) {
                    _display->draw(object);
                }
                _display->refresh();
                score = _game->getScore();
                Score scoreHandler;
                if (score > scoreHandler.getScore(_gamePath.substr(_gamePath.find_last_of("/") + 1))) {
                    scoreHandler.setScore(_gamePath.substr(_gamePath.find_last_of("/") + 1), score, scoreHandler.getCurrentPlayer());
                }
            }
        }
    }

    std::string Core::nextLib()
    {
        std::string path = "lib/";

        int i = 0;
        for (auto &lib : _displayLibs) {
            if ((path + lib) == _displayPath) {
                if (i == (int)_displayLibs.size() - 1)
                    return path + _displayLibs[0];
                return path + _displayLibs[i + 1];
            }
            i++;
        }
        return path + _displayLibs[0];
    }

    std::string Core::prevLib()
    {
        std::string path = "lib/";

        int i = 0;
        for (auto &lib : _displayLibs) {
            if ((path + lib) == _displayPath) {
                if (i == 0) {
                    return path + _displayLibs[_displayLibs.size() - 1];
                }
                return path + _displayLibs[i - 1];
            }
            i++;
        }
        return path + _displayLibs[0];
    }

    /**
     * It handles the input from the display
     * @param input The input from the display
     * @return True if the input is not QUIT, false otherwise
     */
    bool Core::handleInput(Input input)
    {
        DLLoader<IDisplayModule> display;

        if (input == Input::ESCAPE)
            return false;
        if (input == Input::NEXT_LIB) {
            std::cout << "Lib = " << _displayPath << " Next lib = " << nextLib() << std::endl;
            _displayPath = nextLib();
            _displayLoader.close();
            _display = display.load(_displayPath);
            _display->clear();
        } else if (input == Input::PREV_LIB) {
            std::cout << "Lib = " << _displayPath << " Prev lib = " << prevLib() << std::endl;
            _displayPath = prevLib();
            _displayLoader.close();
            _display = display.load(_displayPath);
            _display->clear();
        } else if (input == Input::ENTER && _gamePath == MENU_PATH) {
            _gamePath = "lib/" + _gameLibs[_game->getScore()];
            _game = _gameLoader.load(_gamePath);
            _game->start();
        } else if (input == Input::MENU) {
            _gamePath = MENU_PATH;
            _game = _gameLoader.load(_gamePath);
            _game->start();
        }
        return true;
    }

    void Core::getLibs()
    {
        DIR *dir;
        struct dirent *ent;
        std::string path = "lib/";
        std::string extension = ".so";
        std::string file;
        DLLoader<IDisplayModule> displayLoader;
        DLLoader<IGameModule> gameLoader;

        if ((dir = opendir(path.c_str())) != nullptr) {
            while ((ent = readdir(dir)) != nullptr) {
                file = ent->d_name;

                if (file.find(extension) != std::string::npos) {
                    if (displayLoader.isDisplay(path + file)) {
                        _displayLibs.push_back(file);
                    } else if (gameLoader.isGame(path + file)) {
                        _gameLibs.push_back(file);
                    }
                }

            }
            closedir(dir);
        }
        std::cout << "Display lib: " << std::endl;
        for (auto &lib : _displayLibs) {
            std::cout << lib << std::endl;
        }
        std::cout << "Game lib: " << std::endl;
        for (auto &lib : _gameLibs) {
            std::cout << lib << std::endl;
        }
    }
}