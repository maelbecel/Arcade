/*
** EPITECH PROJECT, 2023
** Arcade
** File description:
** test
*/

#ifndef SNAKE_HPP_
    #define SNAKE_HPP_

    #include <iostream>
#include <memory>
#include <unistd.h>
    #include "../../IObject.hpp"
    #include "../../Input.hpp"
    #include "../../IGameModule.hpp"

    #define SIZE_MAP_X 5
    #define SIZE_MAP_Y 5

    namespace Arcade {
        class Snake: public IGameModule {
            class Player {
                public:
                    Player() = default;
                    ~Player() = default;
                    void move();
                    void eat();
                    bool isEating(std::pair<int, int> apple);
                    bool isDead();
                    bool win();
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
                void initMap();
                std::pair<int, int> _apple;
                Arcade::Input _input = Arcade::Input::UNKNOWN;
                Player _player;
                std::vector<std::vector<Arcade::Rectangle>> _map;
                int _score = 0;
        };
    }

    extern "C" Arcade::IGameModule *entryGamePoint();

#endif /* !SNAKE_HPP_ */
