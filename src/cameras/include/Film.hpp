/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Film
*/

#pragma once
#include <string>
#include <vector>

#include "Color.hpp"

namespace raytracer::camera {
class Film {
public:
    Film(int width, int height);

    void addSample(int x, int y, const maths::Color &color);

    const maths::Color &getPixel(int x, int y) const;

    int width() const;

    int height() const;

    static void write(const Film& film, const std::string& path);

private:
    int _width;
    int _height;
    std::vector<maths::Color> _buffer;
};
} // namespace raytracer::camera
