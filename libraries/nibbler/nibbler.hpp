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
    #include <vector>
    #include <fstream>
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
        class Nibbler: public IGameModule {
            class Player {
                public:
                    Player() = default;
                    ~Player() = default;
                    void move(std::vector<std::vector<Arcade::Rectangle>> map, std::string wall[12]);
                    void eat();
                    bool isEating(std::vector<std::pair<int, int>> &apple);
                    bool isDead();
                    Arcade::Rectangle getBlock(std::string direction, std::vector<std::vector<Arcade::Rectangle>> map);
                    std::vector<Arcade::Rectangle> _body;
                    Arcade::Input _direction;
                    bool _changeInput = false;
                    std::optional<std::string> getTextureDir(std::string bodyPart, int i, std::vector<Arcade::Input> direction);
                    std::optional<std::string> getTextureDir(Arcade::Input direction);
            };
            public:
                Nibbler() {};
                ~Nibbler() override = default;

                std::vector<std::shared_ptr<Arcade::IObject>> loop(Arcade::Input input) override;
                int getScore() override;
                void start() override;
            private:
                void end(std::string str, std::vector<std::shared_ptr<Arcade::IObject>> &objects);
                void initMap();
                bool win();
                std::vector<std::pair<int, int>> _apple;
                Arcade::Input _input = Arcade::Input::UNKNOWN;
                Player _player;
                std::vector<std::vector<Arcade::Rectangle>> _map;
                int _score = 0;
                int _scene = 0;
                std::string walls[12] = {
                    "0000000000000000",
                    "0121112112111210",
                    "0202010110102020",
                    "0121010110101210",
                    "0100011111100010",
                    "0112110000112110",
                    "0000010000100000",
                    "0111211111121110",
                    "0101010110101010",
                    "0201010110101020",
                    "0121111111111210",
                    "0000000000000000"
                };
        };
    }

    extern "C" Arcade::IGameModule *entryGamePoint();

#endif /* !SNAKE_HPP_ */
