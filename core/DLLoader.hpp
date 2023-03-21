/*
** EPITECH PROJECT, 2023
** Arcade
** File description:
** DLLoader
*/

#ifndef DLLOADER_HPP_
    #define DLLOADER_HPP_

    #include <iostream>
    #include <dlfcn.h>

    namespace Arcade {
        template <class Type>
            class DLLoader {
                public:
                    DLLoader() = default;
                    ~DLLoader() = default;

                    static Type *load(std::string path);

                protected:
                private:
            };

        template <typename Type>
        inline Type *DLLoader<Type>::load(std::string path) {
            typedef Type *(*entryPoint_t)();
            void *handle = dlopen(path.c_str(), RTLD_LAZY);
            if (!handle)
                throw std::runtime_error("Failed to open library: " + std::string(dlerror()));

            entryPoint_t entryPoint = (entryPoint_t)dlsym(handle, "entryPoint");
            if (!entryPoint)
                throw std::runtime_error("Failed to find entryPoint: " + std::string(dlerror()));
            Type *lib = entryPoint();
            return lib;
        }
    }

#endif /* !DLLOADER_HPP_ */
