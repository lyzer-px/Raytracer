/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** Normal.tpp
*/

#pragma once

#include "Normal.hpp"

namespace raytracer::maths {

template <typename T>
Normal3<T>::Normal3() : Vector<Normal3, 3, T>() {}

template <typename T>
Normal3<T>::Normal3(T x, T y, T z) : Vector<Normal3, 3, T>(x, y, z) {}

template <typename T>
template <typename U>
Normal3<T>::Normal3(const Vector3<U>& v) :
    Vector<Normal3, 3, T>({(v.x()), (v.y()), (v.z())}) {}

} // namespace raytracer::maths