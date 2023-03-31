/*
** EPITECH PROJECT, 2023
** Arcade
** File description:
** test
*/

#include "menu.hpp"

namespace Arcade {
    std::vector<std::shared_ptr<Arcade::IObject>> Menu::loop(Arcade::Input input)
    {
        Score score;
        updateGame(input);
        _objects.clear();
        _objects.push_back(std::make_shared<Arcade::Text>(Arcade::Text(std::make_pair(0, 0), "Arcade", Arcade::Color::WHITE, 60)));
        _objects.push_back(std::make_shared<Arcade::Text>(Arcade::Text(std::make_pair(0, 2), "User : " + score.getCurrentPlayer(), Arcade::Color::WHITE, 60)));
        for (size_t i = 0; i < _games.size(); i++) {
            if (_games[i] == _currentGame)
                _objects.push_back(std::make_shared<Arcade::Text>(Arcade::Text(std::make_pair(0, i + 4), "-", Arcade::Color::WHITE, 40)));
            else
                _objects.push_back(std::make_shared<Arcade::Text>(Arcade::Text(std::make_pair(1, i + 4), _games[i], Arcade::Color::WHITE, 40)));
            _objects.push_back(std::make_shared<Arcade::Text>(Arcade::Text(std::make_pair(1, i + 4), _games[i], Arcade::Color::WHITE, 40)));
        }
        return _objects;
    }

    int Menu::getScore()
    {
        for (size_t i = 0; i < _games.size(); i++) {
            if (_games[i] == _currentGame)
                return i;
        }
        return 0;
    }

    void Menu::start()
    {
        loadNames();
        if (_graphics.size() == 0 || _games.size() == 0)
            throw std::runtime_error("No games or graphics found");
        _currentGame = _games[0];
    }

    void Menu::updateGame(Arcade::Input input)
    {
        if (input == Arcade::Input::UP) {
            if (_currentGame == _games[0])
                _currentGame = _games[_games.size() - 1];
            else {
                for (size_t i = 0; i < _games.size(); i++)
                    if (_games[i] == _currentGame)
                        _currentGame = _games[i - 1];
            }
        }else  if (input == Arcade::Input::DOWN) {
            if (_currentGame == _games[_games.size() - 1]) {
                _currentGame = _games[0];
            } else {
                for (size_t i = 0; i < _games.size() - 1; i++) {
                    if (_games[i] == _currentGame) {
                        _currentGame = _games[i + 1];
                        break;
                    }
                }
            }
        }

    }

    void Menu::loadNames() {
        DIR *dir;
        struct dirent *ent;
        std::string path = "lib/";
        std::string extension = ".so";
        std::string file;
        Score score;
        DLLoader<IDisplayModule> displayLoader;
        DLLoader<IGameModule> gameLoader;

        if ((dir = opendir(path.c_str())) != nullptr) {
            while ((ent = readdir(dir)) != nullptr) {
                file = ent->d_name;

                if (file.find(extension) != std::string::npos && file.substr(file.find_last_of("/") + 1) != "arcade_menu.so") {
                    if (displayLoader.isDisplay(path + file)) {
                        _graphics.push_back(file);
                    } else if (gameLoader.isGame(path + file)) {
                        file =  file.substr(file.find_last_of("/") + 1) + " | " + score.getBestPlayer(file.substr(file.find_last_of("/") + 1)) + " [" + std::to_string(score.getScore(file.substr(file.find_last_of("/") + 1))) + "]";
                        _games.push_back(file);
                    }
                }

            }
            closedir(dir);
        }
    }
}

extern "C" Arcade::IGameModule *entryGamePoint()
{
    return (new Arcade::Menu());
}