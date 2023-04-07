/*
** EPITECH PROJECT, 2023
** Arcade
** File description:
** Core
*/

#include "Score.hpp"

namespace Arcade {

    /**
     * The Score constructor checks if a score file exists, creates one if it
     * doesn't, and parses the file to initialize the _games variable.
     */
    Score::Score()
    {
        if (!std::ifstream(SCORE_FILE)) {
            std::ofstream file(SCORE_FILE);
            file << "{}";
            file.close();
        }
        _games = parseFile(SCORE_FILE);
    }

    /**
     * This function reads and parses a file containing game scores and returns a
     * vector of Game objects.
     *
     * @param file The parameter "file" is a string that represents the name or
     * path of the file that needs to be parsed.
     *
     * @return A vector of `Score::Game` objects is being returned.
     */
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
            games.push_back(game);
        }
        stream.close();
        return games;
    }

    /**
     * The function writes game scores to a file.
     *
     * @param file The name of the file to write the scores to.
     * @param games A vector of Game objects that contains information about the
     * name of the game, the score achieved, and the player who achieved it.
     *
     */
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

    /**
     * The function returns the score of a given game by iterating through a list
     * of games and returning the score of the matching game.
     *
     * @param game game is a string parameter that represents the name of a game.
     * The function searches for a game with the same name in the `_games` vector
     * and returns its score. If no game with the given name is found, it returns
     * 0.
     *
     * @return The function `getScore` is returning an integer value, which is the
     * score of the game passed as a parameter. If the game is not found in the
     * `_games` vector, the function returns 0.
     */
    int Score::getScore(std::string game)
    {
        for (auto &g : _games) {
            if (g.getName() == game)
                return g.getScore();
        }
        return 0;
    }

    /**
     * The function sets the score and player name for a given game, and writes
     * the updated scores to a file.
     *
     * @param game A string representing the name of the game for which the score
     * is being set.
     * @param score An integer representing the score achieved in a game.
     * @param name The parameter "name" is a string variable that represents the
     * name of the player who achieved the score in a particular game.
     *
     * @return The function does not return anything (void).
     */
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

    /**
     * The function returns the name of the best player for a given game.
     *
     * @param game The parameter "game" is a string that represents the name of a
     * game. The function searches through a vector of games and returns the name
     * of the player with the highest score for the specified game.
     *
     * @return The function `getBestPlayer` returns a `std::string` representing
     * the name of the player with the highest score in the specified game. If
     * there are no scores for the specified game, an empty string is returned.
     */
    std::string Score::getBestPlayer(std::string game)
    {
        for (auto &g : _games) {
            if (g.getName() == game)
                return g.getPlayer();
        }
        return "";
    }

    /**
     * The function returns the name of the current player by reading from a file.
     *
     * @return The function `getCurrentPlayer()` returns a string that represents
     * the name of the current player. If the file `USER` cannot be opened, the
     * function returns the string "NULL".
     */
    std::string Score::getCurrentPlayer()
    {
        std::ifstream f(USER);
        std::string name;

        if (!f.is_open())
            return "NULL";
        std::getline(f, name);
        f.close();
        return name;
    }

    /**
     * This function sets the current player's name in a file.
     *
     * @param name A string representing the name of the current player. This
     * function is a member function of the Score class and it sets the current
     * player's name by writing it to a file named "USER". If the file cannot be
     * opened, the function simply returns without doing anything.
     *
     * @return If the file `USER` cannot be opened, the function returns without
     * doing anything. Otherwise, it sets the current player's name to the
     * provided `name` parameter by writing it to the file `USER`, and then closes
     * the file. No value is explicitly returned by the function.
     */
    void Score::setCurrentPlayer(std::string name)
    {
        std::ofstream f(USER);
        if (!f.is_open())
            return;
        f << name;
        f.close();
    }
}