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
#include "../../IObject.hpp"
#include "../../Input.hpp"
#include "../../IGameModule.hpp"

namespace Arcade {
    class GameLib: public IGameModule {
        public:
            GameLib() = default;
            ~GameLib() override = default;

            std::vector<std::shared_ptr<Arcade::IObject>> loop(Arcade::Input input) override;
            int getScore() override;
            void start() override;
        private:
            std::vector<std::shared_ptr<Arcade::IObject>> _objects;
    };
}

extern "C" Arcade::IGameModule *entryPoint();

#endif /* !TEST_HPP_ */
