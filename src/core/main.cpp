/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** 
*/

#include <iostream>

constexpr int EPITECH_FAIL = 84;

int main(void)
{
    try {
         Raytracer r;
         r.run();
    } catch (const std::exception &e) {
        return EPITECH_FAIL;
    }
    std::cout << "Hello world!" << std::endl;
    return EXIT_SUCCESS;
}
