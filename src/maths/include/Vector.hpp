/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** vector class declaration
*/

#pragma once

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <stdexcept>

#include "Point.hpp"

namespace raytracer::maths {

template <template <typename> class Derived, std::size_t N, typename T = double>
class Vector {
public:
    Vector() = default;

    Vector(std::initializer_list<T> values);

    [[nodiscard]] bool hasNaN() const;

    const T &x() const;

    T &x();

    const T &y() const;

    T &y();

    const T &z() const
        requires(N >= 3);

    T &z()
        requires(N >= 3);

    [[nodiscard]] Derived<T> normalize() const;

    Derived<T> cross(const Derived<T> &other) const
        requires(N == 3); // cross product only defined for 3D vectors
    Derived<T> cross(Derived<T> &other) const
        requires(N == 3);

    [[nodiscard]] T length() const;

    [[nodiscard]] T calculateAngle(const Derived<T> &other) const;

    Derived<T> operator+(const Derived<T> &other) const;

    Derived<T> operator-(const Derived<T> &other) const;

    // dot product
    T operator*(const Derived<T> &other) const;

    T dot(const Derived<T> &other) const;

    // scalar multiplication
    Derived<T> operator*(T scalar) const;

    Derived<T> operator/(T scalar) const;

    // multiply by -1
    Derived<T> operator-() const;

    // comparison by values
    bool operator==(const Derived<T> &other) const;

    bool operator!=(const Derived<T> &other) const;

    // norm comparaison
    bool operator<(const Derived<T> &other) const;

    bool operator<=(const Derived<T> &other) const;

    bool operator>(const Derived<T> &other) const;

    bool operator>=(const Derived<T> &other) const;

    const std::array<T, N> &data() const;

protected:
    std::array<T, N> _data;
};

} // namespace raytracer::maths

#include "Vector.tpp"
