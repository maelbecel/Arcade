/*
** EPITECH PROJECT, 2023
** Arcade
** File description:
** Core
*/

#include "Score.hpp"

namespace Arcade {

    Score::Score()
    {
        if (!std::ifstream(SCORE_FILE)) {
            std::ofstream file(SCORE_FILE);
            file << "{}";
            file.close();
        }
        _games = parseFile(SCORE_FILE);
    }

    std::vector<Score::Game> Score::parseFile(std::string file) const
    {
        std::vector<Game> games;
        std::ifstream stream(file);

        if (!stream.is_open())
            return games;
        std::string line;

        while (std::getline(stream, line)) {
            if (line.empty())
                continue;
            Game game;
            game.setName(line.substr(0, line.find(":")));
            line = line.substr(line.find(":") + 1);
            game.setScore(std::atoi(line.substr(0, line.find(":")).c_str()));
            line = line.substr(line.find(":") + 1);
            game.setPlayer(line);
        }
        stream.close();
        return games;
    }

    void Score::writeInFile(std::string file, std::vector<Game> games)
    {
        std::ofstream stream(file);
        if (!stream.is_open())
            return;
        for (auto &g : games) {
            stream << g.getName() << ":" << g.getScore() << ":" << g.getPlayer() << std::endl;
        }
        stream.close();
    }

    int Score::getScore(std::string game)
    {
        for (auto &g : _games) {
            if (g.getName() == game)
                return g.getScore();
        }
        return 0;
    }

    void Score::setScore(std::string game, int score, std::string name)
    {
        for (auto &g : _games) {
            if (g.getName() == game) {
                if (g.getScore() < score) {
                    g.setScore(score);
                    g.setPlayer(name);
                }
                writeInFile(SCORE_FILE, _games);
                return;
            }
        }
        Game g;
        g.setName(game);
        g.setScore(score);
        g.setPlayer(name);
        _games.push_back(g);
        writeInFile(SCORE_FILE, _games);
    }

    std::string Score::getBestPlayer(std::string game)
    {
        for (auto &g : _games) {
            if (g.getName() == game)
                return g.getPlayer();
        }
        return "";
    }
}