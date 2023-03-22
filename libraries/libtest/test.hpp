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
#include "../../IDisplayModule.hpp"

namespace Arcade {
    class TestLib : public Arcade::IDisplayModule {
    public:
        TestLib() = default;
        ~TestLib() = default;

        Arcade::Input getLastInput() override;
        void clear() override;
        void refresh() override;
        void draw(std::shared_ptr<Arcade::IObject> object) override;
        bool doLoop() override { return true; };
    };
}

extern "C" Arcade::IDisplayModule *entryDisplayPoint();

#endif /* !TEST_HPP_ */