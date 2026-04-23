/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** 
*/

#ifndef VECTOR_TPP
#define VECTOR_TPP

#include <array>

template<std::size_t N, typename T = double>
class Vector {
public:
    Vector();
    Vector(std::initializer_list<T> values);

    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;
    Vector operator*(T scalar) const;
    Vector operator/(T scalar) const;
    Vector operator-() const;
    T& operator[](std::size_t i);
    const T& operator[](std::size_t i) const;

private:
    std::array<T, N> _data;
};

// Common aliases
using Vector2f = Vector<2, float>;
using Vector3f = Vector<3, float>;

#endif
