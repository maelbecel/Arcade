/*
** EPITECH PROJECT, 2023
** Arcade
** File description:
** test
*/

#include "test.hpp"

namespace Arcade {

    Input TestLib::getLastInput()
    {
        return (Arcade::Input::UNKNOWN);
    }

    void TestLib::clear()
    {
        std::cout << "Clear" << std::endl;
    }

    void TestLib::refresh()
    {
        std::cout << "Refresh" << std::endl;
    }

    void TestLib::draw(__attribute__((unused)) std::shared_ptr<IObject> object)
    {
        std::cout << "Draw" << std::endl;
    }
}

extern "C" Arcade::IDisplayModule *entryPoint()
{
    return (new Arcade::TestLib());
}