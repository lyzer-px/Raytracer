/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Vector3
*/

#pragma once

#include <optional>
#include <random>

#include "Normal.hpp"
#include "Vector.hpp"

namespace raytracer::maths {

template <typename T>
class Vector3: public Vector<Vector3, 3, T> {
public:
    Vector3();

    Vector3(T x, T y, T z) noexcept;

    template <typename U>
    explicit Vector3(const Point3<U> &v); // conversion constructor

    template <typename U>
    explicit Vector3(const Normal3<U> &v); // conversion constructor

    static Vector3 randomUnitVector() noexcept;

    Vector3 reflect(const Normal3<T> &normal) const;

    Vector3 refract(const Vector3 &normal, const double &ratio);

    std::optional<Vector3> refraction(const Vector3 &normal,
        const double &ratio) const;

    using Vector<Vector3, 3, T>::operator+;
    using Vector<Vector3, 3, T>::operator-;
    using Vector<Vector3, 3, T>::dot;

    double dot(const Normal3<T> &normal) const;

    // double dot(const Vector3 &other) const;

    Vector3 operator+(const Normal3<T> &normal) const noexcept;

    Vector3 operator-(const Normal3<T> &normal) const noexcept;
};

using Vector3d = Vector3<double>;

} // namespace raytracer::maths

#include "Vector3.tpp"
