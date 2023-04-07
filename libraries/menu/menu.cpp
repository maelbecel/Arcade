/*
** EPITECH PROJECT, 2023
** Arcade
** File description:
** test
*/

#include "menu.hpp"

namespace Arcade {

    /* Defining a static constant vector of pairs, where each pair contains an
    Input enum value and its corresponding character representation. This
    vector is used in the Menu class to handle user input. */
    static const std::vector<std::pair<Input, char>> InputArray = {
        {Input::A, 'a'},
        {Input::B, 'b'},
        {Input::C, 'c'},
        {Input::D, 'd'},
        {Input::E, 'e'},
        {Input::F, 'f'},
        {Input::G, 'g'},
        {Input::H, 'h'},
        {Input::I, 'i'},
        {Input::J, 'j'},
        {Input::K, 'k'},
        {Input::L, 'l'},
        {Input::M, 'm'},
        {Input::N, 'n'},
        {Input::O, 'o'},
        {Input::P, 'p'},
        {Input::Q, 'q'},
        {Input::R, 'r'},
        {Input::S, 's'},
        {Input::T, 't'},
        {Input::U, 'u'},
        {Input::V, 'v'},
        {Input::W, 'w'},
        {Input::X, 'x'},
        {Input::Y, 'y'},
        {Input::Z, 'z'}
    };

    /**
     * The function "getInput" returns the corresponding character value for a
     * given input from an array of input-value pairs.
     *
     * @param input The parameter `input` is of type `Input`, which is likely an
     * enumeration or a class representing some kind of input option or command.
     * It is used to search for a corresponding character value in the
     * `InputArray` data member of the `Menu` class.
     *
     * @return The function `getInput` returns a character value. If the input
     * parameter matches with any of the keys in the `InputArray`, then the
     * corresponding value is returned. Otherwise, `-1` is returned.
     */
    char Menu::getInput(Input input)
    {
        for (auto &i : InputArray) {
            if (i.first == input)
                return (i.second);
        }
        return (-1);
    }

    /**
     * The function removes the "arcade_" prefix and ".so" suffix from a given
     * string.
     *
     * @param inputString The input string that needs to be cleaned up by removing
     * the "arcade_" prefix and ".so" suffix (if present).
     *
     * @return The modified input string with the "arcade_" prefix removed and the
     * ".so" suffix removed, if present.
     */
    std::string Menu::cleanName(std::string inputString) {
        if (inputString.substr(0, 7) == "arcade_") {
            inputString.erase(0, 7);
        }
        if (inputString.length() > 3 && inputString.substr(inputString.length() - 3, 3) == ".so") {
            inputString.erase(inputString.length() - 3, 3);
        }

        // return the modified string
        return inputString;
    }

    /**
     * It creates a vector of shared pointers to IObjects, and returns it
     *
     * @param input The input from the user.
     *
     * @return A vector of shared pointers to IObjects.
     */
    std::vector<std::shared_ptr<Arcade::IObject>> Menu::loop(Arcade::Input input)
    {
        Score score;
        updateGame(input);
        if (getInput(input) != -1) {
            score.setCurrentPlayer(score.getCurrentPlayer() + getInput(input));
        } if (input == Input::BACKSPACE && !score.getCurrentPlayer().empty()) {
            std::string s = score.getCurrentPlayer();
            s.pop_back();
            score.setCurrentPlayer(s);
        }
        size_t x = this->getScore();

        _objects.clear();
        _objects.push_back(std::make_shared<Arcade::Text>(Arcade::Text(std::make_pair(0, 0), "Games:", Arcade::Color::RED, 50)));
        _objects.push_back(std::make_shared<Arcade::Text>(Arcade::Text(std::make_pair(8, 0), "User : ", Arcade::Color::RED, 50)));
        _objects.push_back(std::make_shared<Arcade::Text>(Arcade::Text(std::make_pair(12, 0), score.getCurrentPlayer(), Arcade::Color::WHITE, 50)));
        _objects.push_back(std::make_shared<Arcade::Text>(Arcade::Text(std::make_pair(8, 3), "Highscore : ", Arcade::Color::RED, 50)));
        _objects.push_back(std::make_shared<Arcade::Text>(Arcade::Text(std::make_pair(5, 9), "Graphics : ", Arcade::Color::RED, 50)));
        for (size_t i = 0; i < _games.size(); i++) {
            _objects.push_back(std::make_shared<Arcade::Text>(Arcade::Text(std::make_pair(0, i  + 2), cleanName(_games[i]), (i == x) ? Arcade::Color::GREEN : Arcade::Color::WHITE, 40)));
        }
        _objects.push_back(std::make_shared<Arcade::Text>(Arcade::Text(std::make_pair(8, 5), std::to_string(score.getScore(_games[x])) , Arcade::Color::WHITE, 40)));
        _objects.push_back(std::make_shared<Arcade::Text>(Arcade::Text(std::make_pair(10, 5), "|" , Arcade::Color::WHITE, 40)));
        _objects.push_back(std::make_shared<Arcade::Text>(Arcade::Text(std::make_pair(11, 5), score.getBestPlayer(_games[x]) , Arcade::Color::WHITE, 40)));

        std::string graphics;
        for (size_t i = 0; i < _graphics.size(); i++) {
            graphics += cleanName(_graphics[i]) + "  ";
        }
        _objects.push_back(std::make_shared<Arcade::Text>(Arcade::Text(std::make_pair((20 - graphics.size() / 2) * 8 / 20, 11), graphics, Arcade::Color::WHITE, 40)));
        return _objects;
    }

    /**
     * It returns the index of the current game in the vector of games
     *
     * @return The index of the current game in the vector of games.
     */
    int Menu::getScore()
    {
        for (size_t i = 0; i < _games.size(); i++) {
            if (_games[i] == _currentGame)
                return i;
        }
        return 0;
    }

    /**
     * It loads the names of the games and graphics, and if there are none, it
     * throws an exception
     */
    void Menu::start()
    {
        loadNames();
        if (_graphics.size() == 0 || _games.size() == 0)
            throw std::runtime_error("No games or graphics found");
        _currentGame = _games[0];
    }

    /**
     * It update the game using the player input
     *
     * @param input The input that the user has given.
     */
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

    /**
     * It loads the names of the games and the graphics libraries
     */
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
                        file =  file.substr(file.find_last_of("/") + 1);
                        _games.push_back(file);
                    }
                }

            }
            closedir(dir);
        }
    }
}

/* A function that returns a pointer to a new instance of the Menu class. */
extern "C" Arcade::IGameModule *entryGamePoint()
{
    return (new Arcade::Menu());
}