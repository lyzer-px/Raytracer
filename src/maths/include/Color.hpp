/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** color struct declaration
*/

#pragma once

namespace raytracer::maths {

constexpr auto MAX_RGB_VALUE = 255.0;

struct Color {
    double r, g, b;

    Color();

    explicit Color(double r, double g, double b);

    Color operator+(const Color &other) const;
    Color operator*(const Color &other) const;
    Color operator*(double scalar) const;
    Color operator/(double scalar) const;

    // Clamps the color components to the range [0, 1]
    Color clamp() const;
    Color toRgb() const;
};

} // namespace raytracer::maths
