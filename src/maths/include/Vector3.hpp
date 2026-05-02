/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Vector3
*/

#ifndef RAYTRACER_VECTOR3_HPP
#define RAYTRACER_VECTOR3_HPP
#include "Normal.hpp"
#include "Vector.hpp"

template <typename T>
class Vector3: public Vector<Vector3, 3, T> {
public:
    Vector3();

    Vector3(T x, T y, T z) noexcept;

    template <typename U>
    explicit Vector3(const Point3<U> &v); // conversion constructor

    template <typename U>
    explicit Vector3(const Normal3<U> &v); // conversion constructor
};

using Vector3d = Vector3<double>;

#endif //RAYTRACER_VECTOR3_HPP

#include "Vector3.tpp"
