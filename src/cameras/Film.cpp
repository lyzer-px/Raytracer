/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Film
*/

#include "Film.hpp"

#include <algorithm>
#include <cassert>
#include <fstream>
#include <stdexcept>

namespace raytracer::camera {
Film::Film(int width, int height):
    _width{width},
    _height{height},
    _buffer{static_cast<long unsigned int>(width * height),
        maths::Color{0.0, 0.0, 0.0}}
{
    assert(width > 0);
    assert(height > 0);
}

void Film::addSample(int x, int y, const maths::Color &color)
{
    assert(x >= 0 && x < _width);
    assert(y >= 0 && y < _height);

    _buffer[y * _width + x] = color.clamp();
}

const maths::Color &Film::getPixel(int x, int y) const
{
    assert(x >= 0 && x < _width);
    assert(y >= 0 && y < _height);

    return _buffer[y * _width + x];
}

int Film::width() const
{
    return _width;
}

int Film::height() const
{
    return _height;
}

void Film::write(const Film &film, const std::string &path)
{
    std::ofstream file(path);
    if (!file.is_open())
        throw std::runtime_error("error: cannot open file: " + path);

    file << "P3\n";
    file << film.width() << " " << film.height() << "\n";
    file << "255\n";

    for (int y = film.height() - 1; y >= 0; --y) {
        for (int x = 0; x < film.width(); ++x) {
            const maths::Color &c = film.getPixel(x, y);

            const auto r = static_cast<int>(255.0 * std::clamp(c.r, 0.0, 1.0));
            const auto g = static_cast<int>(255.0 * std::clamp(c.g, 0.0, 1.0));
            const auto b = static_cast<int>(255.0 * std::clamp(c.b, 0.0, 1.0));

            file << r << " " << g << " " << b << "\n";
        }
    }
}
} // namespace raytracer::camera
