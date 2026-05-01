/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** Normal.hpp
*/

#pragma once
#include "Vector.hpp"

template <typename T = double>
class Normal3 : public Vector<Normal3<T>> {
public:
    Normal3();
    Normal3(T x, T y, T z);

    // Explicit conversion from Vector3 only.
    // The caller must consciously decide to treat a direction as a surface normal.
    template <typename U> explicit Normal3(const Vector3<U>& v);
};

using Normal3f = Normal3<float>;