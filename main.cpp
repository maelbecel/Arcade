/*
** EPITECH PROJECT, 2023
** Arcade
** File description:
** main
*/

#include <dlfcn.h>
#include "Input.hpp"
#include <iostream>

extern "C"
{
    int main(void)
    {
        void *handle = dlopen("./librairies/libtest/libtest.so", RTLD_LAZY);
        if (!handle) {
            std::cerr << "Cannot open library: " << dlerror() << std::endl;
            return (1);
        }
        dlerror();
        void (*clear)() = (void (*)())dlsym(handle, "clear");
        if (dlerror() != NULL) {
            std::cerr << "Cannot load symbol clear: " << dlerror() << std::endl;
            return (1);
        }
        void (*refresh)() = (void (*)())dlsym(handle, "refresh");
        if (dlerror() != NULL) {
            std::cerr << "Cannot load symbol refresh: " << dlerror() << std::endl;
            return (1);
        }
        Arcade::Input (*getLastInput)() = (Arcade::Input (*)())dlsym(handle, "getLastInput");
        if (dlerror() != NULL) {
            std::cerr << "Cannot load symbol getLastInput: " << dlerror() << std::endl;
            return (1);
        }

        clear();
        refresh();
        std::cout << getLastInput() << std::endl;

        dlclose(handle);
        return (0);
    }
}