/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** 
*/

#include <exception>
#include <stdlib.h>
#include "Raytracer.hpp"

constexpr int EPITECH_FAIL = 84;

int main(void)
{
    try {
        Raytracer r;
        r.run();
    } catch (const std::exception &e) {
        return EPITECH_FAIL;
    }
    return EXIT_SUCCESS;
}
