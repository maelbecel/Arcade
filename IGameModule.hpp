/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-arcade-jason.lagoute [WSL: Ubuntu-22.04]
** File description:
** IGameModule
*/

#ifndef IGAMEMODULE_HPP_
#define IGAMEMODULE_HPP_

#include <vector>
#include <memory>
#include "IObject.hpp"
#include "Input.hpp"

namespace Arcade {
    class IGameModule {
        public:
            virtual ~IGameModule() = 0;

            /**
             * Loop of the game
             * @param input last input get by the graphic library
             * @return vector of IObject to draw
             */
            virtual std::vector<std::shared_ptr<Arcade::IObject>> loop(Arcade::Input input) = 0;

            /**
             * @brief Get the score of the game
             * @return int
             */
            virtual int getScore() = 0;

            /**
             * @brief Start the game (same call for restart)
             */
            virtual void start() = 0;
    };
}

#endif /* !IGAMEMODULE_HPP_ */
