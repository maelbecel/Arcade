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
    lib->clear();
    lib->refresh();
    lib->draw(nullptr);
    return (0);
}
