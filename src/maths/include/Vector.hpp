/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** vector class declaration
*/

#pragma once

#include <cstddef>

template <class Derived, typename T = double>
class Vector {
public:
    Vector() = default;

    using UnitVector = Derived;

    [[nodiscard]] UnitVector normalize() const;

    [[nodiscard]] T length() const;

    [[nodiscard]] T calculateAngle(const Vector &other) const;

    Derived operator+(const Vector &other) const;

    Derived operator-(const Vector &other) const;

    // dot product
    T operator*(const Vector &other) const;

    T dot(const Vector &other) const;

    // scalar multiplication
    Derived operator*(T scalar) const;

    Derived operator/(T scalar) const;

    // multiply by -1
    Derived operator-() const;

    // comparison by values
    bool operator==(const Vector &other) const;

    bool operator!=(const Vector &other) const;

    // norm comparaison
    bool operator<(const Vector &other) const;

    bool operator<=(const Vector &other) const;

    bool operator>(const Vector &other) const;

    bool operator>=(const Vector &other) const;

};

template<typename T>
class Vector3 : public Vector<Vector3<T>, T> {
public:
    Vector3() = default;
    T x = 0.0;
    T y = 0.0;
    T z = 0.0;
};

template<typename T>
class Vector2: public Vector<Vector2<T>, T> {
public:
    Vector2() = default;
    T x = 0.0;
    T y = 0.0;
};

using UnitVector2 = Vector2<double>;
using UnitVector3 = Vector3<double>;
using Vector2d = Vector2<double>;
using Vector3d = Vector3<double>;

#include "Vector.tpp"
