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

template<std::size_t N, typename T = double>
class Vector {
public:
    Vector() = default;
    Vector(std::array<T, N> &values);

    T& operator[](std::size_t i);
    const T& operator[](std::size_t i) const;


    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;
    Vector operator*(T scalar) const;
    Vector operator/(T scalar) const;
    Vector operator-() const;

    std::ostream &operator<<(std::ostream &o) const;

private:
    std::array<T, N> _data;
};

using Vector2f = Vector<2, float>;
using Vector3f = Vector<3, float>;

#include "Vector.tpp"
