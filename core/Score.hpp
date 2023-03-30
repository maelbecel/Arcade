/*
** EPITECH PROJECT, 2023
** Arcade
** File description:
** Core
*/

#include <iostream>
#include <fstream>
#include <vector>

#ifndef ARCADE_SCORE_H
    #define ARCADE_SCORE_H

    #define SCORE_FILE "score.txt"

    namespace Arcade {

        class Score {
            public:
                class Game {
                    public:
                        Game() = default;
                        ~Game() = default;
                        std::string getName() const { return _name; };
                        void setName(const std::string &name) { _name = name; };
                        int getScore() const { return _score; };
                        void setScore(int score) { _score = score; };
                        const std::string &getPlayer() const { return _player; };
                        void setPlayer(const std::string &player) { _player = player; };
                    private:
                        std::string _name;
                        int _score;
                        std::string _player;
                };

                Score();
                ~Score() = default;

                int getScore(std::string game);
                void setScore(std::string game, int score, std::string name);
                std::string getBestPlayer(std::string game);

            private:
                std::vector<Game> parseFile(std::string file) const;
                void writeInFile(std::string file, std::vector<Game> games);
                std::vector<Game> _games;

        };

    } // Arcade

#endif //ARCADE_SCORE_H
