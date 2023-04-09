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
    #include <optional>
    #include <algorithm>
    #include "../../IObject.hpp"
    #include "../../Input.hpp"
    #include "../../IGameModule.hpp"

    #define SIZE_MAP_X 15
    #define SIZE_MAP_Y 11

    namespace Arcade {
        enum Scene {
            GAME,
            WIN,
            END
        };
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
                    Arcade::Input _directionTail;
                    Arcade::Input _direction;
                    std::optional<std::string> getTextureDir(std::string bodyPart, int i, std::vector<Arcade::Input> direction);
                    std::optional<std::string> getTextureDir(Arcade::Input direction);
            };
            public:
                Snake() {};
                ~Snake() override = default;
                std::vector<std::shared_ptr<Arcade::IObject>> loop(Arcade::Input input) override;
                int getScore() override;
                void start() override;
                static bool comparePos(Arcade::Rectangle rect1, Arcade::Rectangle rect2);
            private:
                void end(std::string str, std::vector<std::shared_ptr<Arcade::IObject>> &objects);
                std::pair<int, int> getNewPos();
                void initMap();
                std::pair<int, int> _apple;
                Arcade::Input _input = Arcade::Input::UNKNOWN;
                Player _player;
                std::vector<std::vector<Arcade::Rectangle>> _map;
                int _score = 0;
                int _scene = 0;
        };
    }

    extern "C" Arcade::IGameModule *entryGamePoint();

#endif /* !SNAKE_HPP_ */
