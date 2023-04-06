/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-arcade-jason.lagoute [WSL : Ubuntu-22.04]
** File description:
** IDisplayModule
*/

#ifndef IDISPLAYMODULE_HPP_
    #define IDISPLAYMODULE_HPP_

    #include <memory>
    #include "IObject.hpp"
    #include "Input.hpp"

    namespace Arcade {
        class IDisplayModule {
            public:
                virtual ~IDisplayModule() = default;

                /**
                 * @brief Get last input get by the graphic library
                 * @return Arcade::Input
                */
                virtual Arcade::Input getLastInput() = 0;

                /**
                 * @brief Clear the screen
                 */
                virtual void clear() = 0;

                /**
                 * @brief Refresh the screen
                 */
                virtual void refresh() = 0;

                /**
                 * @brief Draw an object on the screen
                 * @param Arcade::IObject
                 */
                virtual void draw(std::shared_ptr<Arcade::IObject> object) = 0;

                /**
                 * @brief Return true if display loop is good
                 */
                virtual bool doLoop() = 0;
        };
    }

#endif /* !IDISPLAYMODULE_HPP_ */
