/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** 
*/

#pragma once

#include <cstddef>
#include <array>
#include <iostream>

template<std::size_t N, typename T = double, bool PrecomputeNorm = false>
class Vector {
public:

    Vector() = default;
    Vector(std::array<T, N> &values);
    
    using UnitVector = Vector<N, T, PrecomputeNorm>;
    UnitVector normalize() const;

    T getNorm() const;
    T computeNorm() const;
    void loadNorm() const;

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

    bool operator==(const Vector other) const;
    bool operator!=(const Vector other) const;

    // norm comparaison
    bool operator<(const Vector other) const;
    bool operator<=(const Vector other) const;
    bool operator>(const Vector other) const;
    bool operator>=(const Vector other) const;

    std::ostream &operator<<(std::ostream &o) const;

private:
    std::array<T, N> _data;
    T _norm;
};

template<std::size_t N, typename T, bool PrecomputeNorm>
using UnitVector = Vector<N, T, PrecomputeNorm>;

using Vector2f = Vector<2, float>;
using Vector3f = Vector<3, float>;

template<typename T>
Vector<3> cross(Vector<3> a, Vector<3> b);


template<std::size_t N, typename T, bool PrecomputeNorm>
Vector<N + 1, T, PrecomputeNorm> IncreaseDimension(const Vector<N, T, PrecomputeNorm> &a);

#include "Vector.tpp"
