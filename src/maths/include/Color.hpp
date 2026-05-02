/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** color struct declaration
*/

#pragma once

constexpr auto MAX_RGB_VALUE = 255.0;


struct Color {
    double r, g, b;

    Color();

    explicit Color(double r = 0, double g = 0, double b = 0);

    Color operator+(const Color& other) const;
    Color operator*(const Color& other) const;
    Color operator*(double scalar) const;
    Color operator/(double scalar) const;

    // Clamps the color components to the range [0, 1]
    Color clamp() const;
    Color toRgb() const;
};
