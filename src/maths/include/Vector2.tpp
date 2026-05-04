/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** Vector class implementation
*/

#pragma once

#include "Vector2.hpp"

namespace raytracer::maths {

template <typename T>
Vector2<T>::Vector2() : Vector<Vector2, 2, T>() {}

template <typename T>
Vector2<T>::Vector2(T x, T y) noexcept : Vector<Vector2, 2, T>() {

    this->_data[0] = x;
    this->_data[1] = y;
}

} // namespace raytracer::maths