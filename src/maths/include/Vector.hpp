/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** vector class declaration
*/

#pragma once

#include <cstddef>
#include <array>
#include <iostream>

template<std::size_t N, typename T = double, bool PrecomputeNorm = false>
class Vector {
public:
    using iterator = typename std::array<T, N>::iterator;
    using const_iterator = typename std::array<T, N>::const_iterator;

    Vector() = default;
    Vector(std::array<T, N> &values);

    using UnitVector = Vector<N, T, PrecomputeNorm>;
    UnitVector normalize() const;

    T getNorm() const;
    T computeNorm() const;
    void loadNorm();

    T calculateAngle(const Vector<N> &other) const;

    T& operator[](std::size_t i);
    const T& operator[](std::size_t i) const;

    Vector operator+(const Vector &other) const;
    Vector operator-(const Vector &other) const;

    // dot product
    T operator*(const Vector &other) const;
    Vector operator*(T scalar) const;

    Vector operator/(T scalar) const;
    Vector operator-() const;

    bool operator==(const Vector &other) const;
    bool operator!=(const Vector &other) const;

    // norm comparaison
    bool operator<(const Vector &other) const;
    bool operator<=(const Vector &other) const;
    bool operator>(const Vector &other) const;
    bool operator>=(const Vector &other) const;

    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    const_iterator cbegin() const noexcept;

    iterator end() noexcept;
    const_iterator end() const noexcept;
    const_iterator cend() const noexcept;

    const Vector<3> rotate(double angle);
    const Vector<2> rotate2D(double angle);

    const Vector<3> translate(double translateX, double translateY);
    const Vector<2> translate2D(double translateX, double translateY);

    const Vector<3> scale(double scaleX, double scaleY);
    const Vector<2> scale2D(double scaleX, double scaleY);

    const Vector<3> shear(double shearX, double shearY);
    const Vector<2> shear2D(double shearX, double shearY);

    const Vector<3> reflect(bool reflectX, bool reflectY);
    const Vector<2> reflect2D(bool reflectX, bool reflectY);

private:
    std::array<T, N> _data;
    T _norm;
};

template<std::size_t N, typename T, bool PrecomputeNorm>
using UnitVector = Vector<N, T, PrecomputeNorm>;

using Vector2f = Vector<2, float>;
using Vector3f = Vector<3, float>;
using UnitVector2 = Vector<2>;
using UnitVector3 = Vector<3>;

template<typename T>
Vector<3> cross(Vector<3> a, Vector<3> b);


template<std::size_t N, typename T, bool PrecomputeNorm>
Vector<N + 1, T, PrecomputeNorm> increaseDimension(const Vector<N, T, PrecomputeNorm> &a);

template<std::size_t N, typename T, bool PrecomputeNorm>
std::ostream &operator<<(std::ostream &o, const Vector<N, T, PrecomputeNorm> &vector);

#include "Vector.tpp"
