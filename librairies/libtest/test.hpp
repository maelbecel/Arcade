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


    class TestLib {
        public:
            TestLib() = default;
            ~TestLib() = default;

            Arcade::Input getLastInput();
            void clear();
            void refresh();
            void draw(std::shared_ptr<Arcade::IObject> object);
    };


#endif /* !TEST_HPP_ */
