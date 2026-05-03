/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** Normal.hpp
*/

#pragma once

#include "Vector.hpp"

template <typename T = double>
class Normal3: public Vector<Normal3, 3, T> {
public:
    Normal3();

    Normal3(T x, T y, T z);

    template <typename U>
    explicit Normal3(const Vector3<U> &);
};

using Normal3d = Normal3<double>;

#include "Normal.tpp"
