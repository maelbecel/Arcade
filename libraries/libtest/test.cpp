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
        std::string buffer;
        std::getline(std::cin, buffer);
        if (buffer == "UP")
            return (Input::UP);
        if (buffer == "DOWN")
            return (Input::DOWN);
        if (buffer == "LEFT")
            return (Input::LEFT);
        if (buffer == "RIGHT")
            return (Input::RIGHT);
        if (buffer == "P")
            return (Input::PREV_LIB);
        if (buffer == "N")
            return (Input::NEXT_LIB);
        return (Input::UNKNOWN);
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
        Arcade::Rectangle *rectangle = dynamic_cast<Arcade::Rectangle *>(object.get());
        if (dynamic_cast<Arcade::Rectangle *>(object.get())) {
            std::cout << "Rectangle at (" << rectangle->getPos().first << "," << rectangle->getPos().second << "): " << rectangle->getTexture() << std::endl;
        }
        Text *text = dynamic_cast<Text *>(object.get());
        if (text != nullptr)
            std::cout << "Text at (" << text->getPos().first << "," << text->getPos().second << "): " << text->getText() << std::endl;
        Circle *circle = dynamic_cast<Circle *>(object.get());
        if (circle != nullptr)
            std::cout << "Circle at (" << circle->getPos().first << "," << circle->getPos().second << "): " << circle->getTexture() << std::endl;
    }
}

extern "C" Arcade::IDisplayModule *entryDisplayPoint()
{
    return (new Arcade::TestLib());
}