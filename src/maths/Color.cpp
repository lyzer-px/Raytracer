/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** color struct definition
*/

#include "include/Color.hpp"

#include <algorithm>
#include <cmath>

namespace raytracer::maths {

Color::Color(): r{0}, g{0}, b{0}
{}

Color::Color(double r, double g, double b): r(r), g(g), b(b)
{}

Color Color::operator+(const Color &other) const
{
    return Color(r + other.r, g + other.g, b + other.b);
}

Color Color::operator*(const Color &other) const
{
    return Color(r * other.r, g * other.g, b * other.b);
}

Color Color::operator*(double scalar) const
{
    return Color(r * scalar, g * scalar, b * scalar);
}

Color Color::operator/(double scalar) const
{
    return Color(r / scalar, g / scalar, b / scalar);
}

Color Color::clamp() const
{
    return Color(std::max(0.0, std::min(1.0, r)),
        std::max(0.0, std::min(1.0, g)), std::max(0.0, std::min(1.0, b)));
}

Color Color::toRgb() const
{
    return Color(std::round(r * MAX_RGB_VALUE), std::round(g * MAX_RGB_VALUE),
        std::round(b * MAX_RGB_VALUE));
}

} // namespace raytracer::maths
