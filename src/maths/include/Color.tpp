/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** color struct definition
*/

#include <algorithm>
#include <cmath>
#include "Color.hpp"

Color::Color(): r{0}, g{0}, b{0}
{}

Color::Color(float r, float g, float b) : r(r), g(g), b(b) {}

Color Color::operator+(const Color& other) const
{
    Color c = Color(r + other.r, g + other.g, b + other.b);
    c.clamp();
    return c;
}

Color Color::operator*(const Color& other) const
{
    Color c = Color(r * other.r, g * other.g, b * other.b);
    c.clamp();
    return c;
}

Color Color::operator*(float scalar) const
{
    Color c = Color(r * scalar, g * scalar, b * scalar);
    c.clamp();
    return c;
}

Color Color::operator/(float scalar) const
{
    Color c = Color(r / scalar, g / scalar, b / scalar);
    c.clamp();
    return c;
}

Color Color::clamp() const
{
    return Color(
        std::max(0.0f, std::min(1.0f, r)),
        std::max(0.0f, std::min(1.0f, g)),
        std::max(0.0f, std::min(1.0f, b))
    );
}

Color Color::toRgb() const
{
    return Color(
        std::round(r * MAX_RGB_VALUE),
        std::round(g * MAX_RGB_VALUE),
        std::round(b * MAX_RGB_VALUE)
    );
}