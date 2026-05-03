/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Film
*/

#ifndef RAYTRACER_FILM_HPP
#define RAYTRACER_FILM_HPP
#include <string>
#include <vector>

#include "Color.hpp"

namespace raytracer {
namespace camera {
class Film {
public:
    Film(int width, int height);

    void addSample(int x, int y, const Color &color);

    const Color &getPixel(int x, int y) const;

    int width() const;

    int height() const;

    static void write(const Film& film, const std::string& path);

private:
    int _width;
    int _height;
    std::vector<Color> _buffer;
};
} // camera
} // raytracer

#endif //RAYTRACER_FILM_HPP
