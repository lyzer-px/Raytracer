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

template<std::size_t N, typename T = double, bool PrecalculateNorm = false>
class Vector {
public:
    Vector() = default;
    Vector(std::array<T, N> &values);

    T getNorm() const;
    T calculateNorm() const;
    void loadNorm() const;

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

using Vector2f = Vector<2, float>;
using Vector3f = Vector<3, float>;

#include "Vector.tpp"
