/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** vector class declaration
*/

#pragma once

#include "Point.hpp"
#include <cstddef>

template <template<typename>class Derived, std::size_t N, typename T = double>
class Vector {
public:
    Vector() = default;
    Vector(std::initializer_list<T> values);

    [[nodiscard]] bool HasNaN() const;

    T  x() const;  T& x();
    T  y() const;  T& y();
    T  z() const requires (N >= 3);
    T& z()       requires (N >= 3);

    [[nodiscard]] Derived<T> normalize() const;
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

    Derived<T> cross(const Derived<T> &other) const;

    const std::array<T, N>& data() const;

protected:
    std::array<T, N> _data;
};

template<typename T>
class Vector3 : public Vector<Vector3, 3, T> {
public:
    Vector3();
    Vector3(T x, T y, T z) noexcept;

    template<typename U>
    explicit Vector3(const Point3<U>& v); // conversion constructor
};

template<typename T>
class Vector2: public Vector<Vector2, 2, T> {
public:
    Vector2();
    Vector2(T x, T y) noexcept;

    template<typename U>
    explicit Vector2(const Point2<U>& v); // conversion constructor
};

using UnitVector2 = Vector2<double>;
using UnitVector3 = Vector3<double>;
using Vector2d = Vector2<double>;
using Vector3d = Vector3<double>;

#include "Vector.tpp"
