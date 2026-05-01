/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** Normal.tpp
*/

#include "Normal.hpp"

template <typename T>
Normal3<T>::Normal3() : Vector<Normal3<T>, T>() {}

template <typename T>
Normal3<T>::Normal3(T x, T y, T z) : Vector<Normal3<T>, T>(x, y, z) {}

template <typename T>
template <typename U>
Normal3<T>::Normal3(const Vector3<U>& v) :
    Vector<Normal3<T>, T>
    (static_cast<T>(v.x), static_cast<T>(v.y), static_cast<T>(v.z)) {}