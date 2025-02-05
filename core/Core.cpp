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
                input = Input::NONE;
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

    /**
     * The function returns the path of the next library in a list of display
     * libraries.
     *
     * @return The name of the next lib
     */
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

    /**
     * The function returns the path of the previous library in a list of display
     * libraries.
     *
     * @return The name of the previous lib
     */
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
     * The function returns the path of the previous game library in a list of
     * game libraries.
     *
     * @return The function `prevGame()` returns a `std::string` which represents
     * the path to the previous game library in the `_gameLibs` vector.
     */
    std::string Core::prevGame()
    {
        std::string path = "lib/";

        int i = 0;
        for (auto &lib : _gameLibs) {
            if ((path + lib) == _gamePath) {
                if (i == 0) {
                    return path + _gameLibs[_gameLibs.size() - 1];
                }
                return path + _gameLibs[i - 1];
            }
            i++;
        }
        return path + _gameLibs[0];
    }

    /**
     * The function returns the path of the next game library in a list of game
     * libraries.
     *
     * @return A string representing the path to the next game library in the list
     * of game libraries stored in the `_gameLibs` vector. If the current game
     * library path is the last one in the list, it will return the path to the
     * first game library in the list. If the `_gameLibs` vector is empty, it will
     * return a path to a default game library in the "lib/"
     */
    std::string Core::nextGame()
    {
        std::string path = "lib/";

        int i = 0;
        for (auto &lib : _gameLibs) {
            if ((path + lib) == _gamePath) {
                if (i == (int)_gameLibs.size() - 1)
                    return path + _gameLibs[0];
                return path + _gameLibs[i + 1];
            }
            i++;
        }
        return path + _gameLibs[0];
    }

    /**
     * It handles the input from the display
     * @param input The input from the display
     * @return True if the input is not QUIT, false otherwise
     */
    bool Core::handleInput(Input input)
    {
        DLLoader<IDisplayModule> display;

        if (input == Input::ESCAPE) {
            _displayLoader.close();
            if (_display)
                delete _display;
            if (_game)
                delete _game;
            return false;
        } if (input == Input::NEXT_LIB) {
            _displayPath = nextLib();
            _displayLoader.close();
            delete _display;
            _display = display.load(_displayPath);
            _display->clear();
        } else if (input == Input::PREV_LIB) {
            _displayPath = prevLib();
            _displayLoader.close();
            delete _display;
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
        } else if (input == Input::NEXT_GAME) {
            _gamePath = nextGame();
            if (_gamePath == MENU_PATH)
                _gamePath = nextGame();
            _game = _gameLoader.load(_gamePath);
            _game->start();
        } else if (input == Input::PREV_GAME) {
            _gamePath = prevGame();
            if (_gamePath == MENU_PATH)
                _gamePath = prevGame();
            _game = _gameLoader.load(_gamePath);
            _game->start();
        } else if (input == Input::RESTART)
            _game->start();
        return true;
    }

    /**
     * The function searches for shared object files with a specific extension in
     * a directory and categorizes them as either display or game libraries using
     * DLLoader.
     */
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
    }
}