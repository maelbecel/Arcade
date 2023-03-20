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

    void TestLib::draw(std::shared_ptr<IObject> object)
    {
        Text *text = dynamic_cast<Text *>(object.get());
        if (text != nullptr)
            std::cout << "Draw at (" << text->getPos().first << "," << text->getPos().second << "): " << text->getText() << std::endl;
        Rectangle *rectangle = dynamic_cast<Rectangle *>(object.get());
        if (rectangle != nullptr)
            std::cout << "Draw at (" << rectangle->getPos().first << "," << rectangle->getPos().second << "): " << rectangle->getTexture() << std::endl;
        Circle *circle = dynamic_cast<Circle *>(object.get());
        if (circle != nullptr)
            std::cout << "Draw at (" << circle->getPos().first << "," << circle->getPos().second << "): " << circle->getTexture() << std::endl;
    }
}

extern "C" Arcade::IDisplayModule *entryPoint()
{
    return (new Arcade::TestLib());
}