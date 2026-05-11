/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Vector2
*/

#pragma once

#include "Vector.hpp"

namespace raytracer::maths {

template <typename T> class Vector2: public Vector<Vector2, 2, T> {
public:
    Vector2();

    Vector2(T x, T y) noexcept;

    template <typename U>
    explicit Vector2(const Point2<U> &v); // conversion constructor
};

using Vector2d = Vector2<double>;

} // namespace raytracer::maths

#include "Vector2.tpp"
