/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Film
*/

#include "Film.hpp"

#include <cassert>

namespace raytracer {
namespace camera {
Film::Film(int width, int height): _width{width}, _height{height},
    _buffer{static_cast<long unsigned int>(width * height), Color{0, 0, 0}}
{
    assert(width  > 0);
    assert(height > 0);
}

void Film::addSample(int x, int y, const Color &color)
{
    assert(x >= 0 && x < _width);
    assert(y >= 0 && y < _height);

    _buffer[y * _width + x] = color.clamp();
}

const Color & Film::getPixel(int x, int y) const
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
    return  _height;
}
} // camera
} // raytracer
