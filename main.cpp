/*
** EPITECH PROJECT, 2023
** Arcade
** File description:
** main
*/

#include <dlfcn.h>
#include "Input.hpp"
#include <iostream>
#include "IDisplayModule.hpp"
#include "./core/DLLoader.hpp"

using namespace Arcade;

int main(void)
{
    DLLoader<IDisplayModule> loader;
    IDisplayModule *lib = loader.load("./librairies/libtest/libtest.so");
    std::shared_ptr<IObject> text = std::make_shared<Text>(std::make_pair(10, 0), "Hello World", Color::WHITE, 20);
    lib->clear();
    lib->refresh();
    lib->draw(text);
    return (0);
}
