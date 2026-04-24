/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** 
*/

#pragma once

#include <array>
#include <cmath>
#include <string>
#include "Vector.hpp"

template<std::size_t N, typename T, bool PrecomputeNorm>
Vector<N, T, PrecomputeNorm>::Vector(std::array<T, N> &values) : _data(values)
{
    if (PrecomputeNorm)
        loadNorm();
}

template<std::size_t N, typename T, bool PrecomputeNorm>
T& Vector<N, T, PrecomputeNorm>::operator[](std::size_t i)
{
    return _data[i];
}

template<std::size_t N, typename T, bool PrecomputeNorm>
const T& Vector<N, T, PrecomputeNorm>::operator[](std::size_t i) const
{
    return _data[i];
}

template<std::size_t N, typename T, bool PrecomputeNorm>
void Vector<N, T, PrecomputeNorm>::loadNorm() const
{
    _norm = computeNorm();
}

template<std::size_t N, typename T, bool PrecomputeNorm>
T Vector<N, T, PrecomputeNorm>::computeNorm() const
{
    T norm = 0;
    
    for (size_t i = 0; i != N; i++) {
        T value = this[i];
        norm += value * value;
    }
    return std::sqrt(norm);
}


template<std::size_t N, typename T, bool PrecomputeNorm>
T Vector<N, T, PrecomputeNorm>::getNorm() const
{
    return _norm;
}


template<std::size_t N, typename T, bool PrecomputeNorm>
Vector<N, T, PrecomputeNorm> Vector<N, T, PrecomputeNorm>::operator+(const Vector<N, T, PrecomputeNorm>& other) const
{
    std::array<T, N> array;

    for (std::size_t i = 0; i != N; i++) {
        array[i] = _data[i] + other[i]; 
    }
    return Vector(array);
}

template<std::size_t N, typename T, bool PrecomputeNorm>
Vector<N, T, PrecomputeNorm> Vector<N, T, PrecomputeNorm>::operator-(const Vector& other) const
{
    std::array<T, N> array;

    for (std::size_t i = 0; i != N; i++) {
        array[i] = _data[i] - other[i]; 
    }
    return Vector(array);

}

template<std::size_t N, typename T, bool PrecomputeNorm>
Vector<N, T, PrecomputeNorm> Vector<N, T, PrecomputeNorm>::operator*(T scalar) const
{
    std::array<T, N> array;

    for (std::size_t i = 0; i != N; i++) {
        array[i] = _data[i] * scalar; 
    }
    return Vector(array);

}

template<std::size_t N, typename T, bool PrecomputeNorm>
Vector<N, T, PrecomputeNorm> Vector<N, T, PrecomputeNorm>::operator/(T scalar) const
{
    return scalar != 0 ? this * (static_cast<T>(1) / scalar) : Vector();
}

template<std::size_t N, typename T, bool PrecomputeNorm>
Vector<N, T, PrecomputeNorm> Vector<N, T, PrecomputeNorm>::operator-() const
{
    return *this * static_cast<T>(-1);
}


template<std::size_t N, typename T, bool PrecomputeNorm>
bool Vector<N, T, PrecomputeNorm>::operator==(const Vector other) const
{
    std::size_t i = 0;

    for(; i != N; i++) {
        if (other[i] != this[i])
            break;
    }
    return i == N;
}

template<std::size_t N, typename T, bool PrecomputeNorm>
bool Vector<N, T, PrecomputeNorm>::operator!=(const Vector other) const
{
    return !(this == other);
}


template<std::size_t N, typename T, bool PrecomputeNorm>
T Vector<N, T, PrecomputeNorm>::operator*(const Vector &other) const
{
    T sum = 0;

    for (size_t i = 0; i != N; i++) {
        sum += this[i] * other[i];
    }
    return sum;
}

template<std::size_t N, typename T, bool PrecomputeNorm>
bool Vector<N, T, PrecomputeNorm>::operator<(const Vector other) const
{
    return getNorm() < other.getNorm();
}

template<std::size_t N, typename T, bool PrecomputeNorm>
bool Vector<N, T, PrecomputeNorm>::operator<=(const Vector other) const
{
    T normA = getNorm();
    T normB = other.getNorm();

    return normA < normB || normA == normB;
}

template<std::size_t N, typename T, bool PrecomputeNorm>
bool Vector<N, T, PrecomputeNorm>::operator>(const Vector other) const
{
    return getNorm() > other.getNorm();
}
template<std::size_t N, typename T, bool PrecomputeNorm>
bool Vector<N, T, PrecomputeNorm>::operator>=(const Vector other) const
{
    T normA = getNorm();
    T normB = other.getNorm();

    return normA > normB || normA == normB;
}

template<std::size_t N, typename T, bool PrecomputeNorm>
std::ostream &Vector<N, T, PrecomputeNorm>::operator<<(std::ostream &o) const
{
    o << "Vector<" << N << "> {";
    for (std::size_t i = 0; i != N; ++i) {
        o << std::to_string(_data[i]) + (i != N ? "," : "");
    }
    o << "}";
    return o;
}
