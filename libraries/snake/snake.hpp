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

#define SIZE_MAP 10

namespace Arcade {
    class Snake: public IGameModule {
        class Player {
            public:
                Player() = default;
                ~Player() = default;
                void move();
                std::vector<Arcade::Rectangle> _body;
                Arcade::Input _direction;
        };
        public:
            Snake() {};
            ~Snake() override = default;

            std::vector<std::shared_ptr<Arcade::IObject>> loop(Arcade::Input input) override;
            int getScore() override;
            void start() override;
        private:
            std::pair<int, int> getNewPos();
            std::pair<int, int> _apple;
            Arcade::Input _input = Arcade::Input::UNKNOWN;
            Player _player;
            int _score = 0;
    };
}

extern "C" Arcade::IGameModule *entryPoint();

#endif /* !TEST_HPP_ */
