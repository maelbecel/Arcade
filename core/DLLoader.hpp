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
    #include <memory>
    #include <vector>
    #include "../IObject.hpp"
    #include "../Input.hpp"

    namespace Arcade {
        template <class Type>
            class DLLoader {
                public:
                    DLLoader() = default;
                    ~DLLoader() = default;

                    static bool isDisplay(std::string path);
                    static bool isGame(std::string path);
                    Type *load(std::string path);
                    void close() { if (_handle){dlclose(_handle);}; };

                protected:
                private:
                    void *_handle;
            };

        template <typename Type>
        /**
         * @brief load the library from the path
         *
         * @param path
         * @return Type*
         */
        inline Type *DLLoader<Type>::load(std::string path) {
            typedef Type *(*entryPoint_t)();
            _handle = dlopen(path.c_str(), RTLD_LAZY);
            if (!_handle)
                throw std::runtime_error("Failed to open library: " + std::string(dlerror()));

            entryPoint_t entryDisplayPoint = (entryPoint_t)dlsym(_handle, "entryDisplayPoint");
            entryPoint_t entryGamePoint = (entryPoint_t)dlsym(_handle, "entryGamePoint");
            if (!entryDisplayPoint && !entryGamePoint)
                throw std::runtime_error("Failed to find entryPoint: " + std::string(dlerror()));
            if (entryDisplayPoint)
                return entryDisplayPoint();
            else if (entryGamePoint)
                return entryGamePoint();
            return nullptr;
        }

        template <typename Type>
        /**
         * @brief check if the library is a display library
         *
         * @param path
         * @return bool
         */
        inline bool DLLoader<Type>::isDisplay(std::string path)
        {
            void *handle = dlopen(path.c_str(), RTLD_LAZY);
            if (!handle) {
                return false;
            }
            if (dlsym(handle, "entryDisplayPoint")) {
                // dlclose(handle);
                return true;
            }
            else {
                dlclose(handle);
                return false;
            }

        }

        template <typename Type>
        /**
         * @brief check if the library is a game library
         *
         * @param path
         * @return bool
         */
        inline bool DLLoader<Type>::isGame(std::string path)
        {
            void *handle = dlopen(path.c_str(), RTLD_LAZY);
            if (!handle) {
                std::cout << "Failed to load as Game: " << path << std::endl;
                std::cout << "\tError: " << dlerror() << std::endl;
                return false;
            }
            if (dlsym(handle, "entryGamePoint")) {
                dlclose(handle);
                return true;
            }
            else {
                std::cout << "Cannot find EntryGamePoint: " << path << std::endl;
                dlclose(handle);
                return false;
            }
        }
    }

#endif /* !DLLOADER_HPP_ */
