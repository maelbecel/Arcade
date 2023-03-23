/*
** EPITECH PROJECT, 2023
** Arcade
** File description:
** test
*/

#ifndef TEST_HPP_
#define TEST_HPP_

#include <iostream>
#include <memory>
#include <dirent.h>
#include "../../IObject.hpp"
#include "../../Input.hpp"
#include "../../IGameModule.hpp"
#include "../../IDisplayModule.hpp"
#include "../../core/DLLoader.hpp"

namespace Arcade {
    class Menu: public IGameModule {
    public:
        Menu() = default;
        ~Menu() override = default;

        std::vector<std::shared_ptr<Arcade::IObject>> loop(Arcade::Input input) override;
        int getScore() override;
        void start() override;
    private:
        void loadNames();
        void updateGame(Arcade::Input);
        std::vector<std::shared_ptr<Arcade::IObject>> _objects;
        std::string _currentGame;
        std::vector<std::string> _games;
        std::vector<std::string> _graphics;
    };
}

extern "C" Arcade::IGameModule *entryGamePoint();

#endif /* !TEST_HPP_ */