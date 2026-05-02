/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** color struct declaration
*/

#pragma once

constexpr float MAX_RGB_VALUE = 255.0f;


struct Color {
    float r, g, b;

    Color();

    explicit Color(float r = 0, float g = 0, float b = 0);

    Color operator+(const Color& other) const;
    Color operator*(const Color& other) const;
    Color operator*(float scalar) const;
    Color operator/(float scalar) const;

    // Clamps the color components to the range [0, 1]
    Color clamp() const;
    Color toRgb() const;
};

#include "Color.tpp"