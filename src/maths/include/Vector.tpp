/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** Vector class definition
*/

#pragma once

#include <array>
#include <cmath>
#include <cstddef>
#include <stdexcept>

#include "Vector.hpp"

template <std::size_t N, typename T, bool PrecomputeNorm> Vector<N, T,
    PrecomputeNorm>::Vector()
{
    for (std::size_t itt = 0; itt < N; ++itt)
        _data[itt] = 0;
}

template <std::size_t N, typename T, bool PrecomputeNorm>
Vector<N, T, PrecomputeNorm>::Vector(std::array<T, N> &values): _data(values)
{
    if (PrecomputeNorm)
        loadLength();
}

template <std::size_t N, typename T, bool PrecomputeNorm>
Vector<N, T, PrecomputeNorm>::Vector(std::array<T, N> &&values): _data(values)
{
    if (PrecomputeNorm)
        loadLength();
}

template <std::size_t N, typename T, bool PrecomputeNorm>
UnitVector<N, T, PrecomputeNorm> Vector<N, T, PrecomputeNorm>::normalize() const
{
    T norm = length();
    if (norm == static_cast<T>(0))
        throw std::runtime_error("Division by 0");
    return *this / norm;
}

template <std::size_t N, typename T, bool PrecomputeNorm>
T Vector<N, T, PrecomputeNorm>::getLength() const
{
    return _norm;
}

template <std::size_t N, typename T, bool PrecomputeNorm>
T Vector<N, T, PrecomputeNorm>::length() const
{
    T norm = 0;

    for (size_t i = 0; i != N; i++) {
        T value = _data[i];
        norm    += value * value;
    }
    return std::sqrt(norm);
}

template <std::size_t N, typename T, bool PrecomputeNorm>
void Vector<N, T, PrecomputeNorm>::loadLength()
{
    _norm = length();
}

template <std::size_t N, typename T, bool PrecomputeNorm>
T Vector<N, T, PrecomputeNorm>::calculateAngle(const Vector<N> &other) const
{
    T otherNorm = 0;

    if (PrecomputeNorm == false)
        loadLength();
    if (other.getLength() == 0)
        otherNorm = other.length();
    if (otherNorm == 0 || _norm == 0)
        throw std::runtime_error("In angle calculation: null norm");
    return std::acos((this * other) / (_norm * otherNorm));
}

template <std::size_t N, typename T, bool PrecomputeNorm>
T &Vector<N, T, PrecomputeNorm>::operator[](std::size_t idx)
{
    return _data[idx];
}

template <std::size_t N, typename T, bool PrecomputeNorm>
const T &Vector<N, T, PrecomputeNorm>::operator[](std::size_t idx) const
{
    return _data[idx];
}

template <std::size_t N, typename T, bool PrecomputeNorm>
Vector<N, T, PrecomputeNorm> Vector<N, T, PrecomputeNorm>::operator+(
    const Vector<N, T, PrecomputeNorm> &other) const
{
    std::array<T, N> array;

    for (std::size_t i = 0; i != N; i++) {
        array[i] = (*this)[i] + other[i];
    }
    return Vector(array);
}

template <std::size_t N, typename T, bool PrecomputeNorm>
Vector<N, T, PrecomputeNorm> Vector<N, T, PrecomputeNorm>::operator-(
    const Vector &other) const
{
    std::array<T, N> array;
    for (std::size_t i = 0; i != N; i++) {
        array[i] = (*this)[i] - other[i];
    }
    return Vector(array);

}

template <std::size_t N, typename T, bool PrecomputeNorm>
T Vector<N, T, PrecomputeNorm>::operator*(
    const Vector &other) const
{
    T sum = 0;

    for (size_t i = 0; i != N; i++) {
        sum += other[i] * _data[i];
    }

    return sum;
}

template <std::size_t N, typename T, bool PrecomputeNorm>
T Vector<N, T, PrecomputeNorm>::dot(const Vector &other) const
{
    T sum = 0;

    for (size_t i = 0; i != N; i++) {
        sum += other[i] * _data[i];
    }

    return sum;
}

template <std::size_t N, typename T, bool PrecomputeNorm>
Vector<N, T, PrecomputeNorm> Vector<N, T, PrecomputeNorm>::operator*(
    T scalar) const
{
    std::array<T, N> array;

    for (std::size_t i = 0; i != N; i++) {
        array[i] = _data[i] * scalar;
    }
    return Vector(array);

}

template <std::size_t N, typename T, bool PrecomputeNorm>
Vector<N, T, PrecomputeNorm> Vector<N, T, PrecomputeNorm>::operator/(
    T scalar) const
{
    if (scalar == static_cast<T>(0))
        throw std::runtime_error("Division by 0");
    return *this * (static_cast<T>(1) / scalar);
}

template <std::size_t N, typename T, bool PrecomputeNorm>
Vector<N, T, PrecomputeNorm> Vector<N, T, PrecomputeNorm>::operator-() const
{
    return *this * static_cast<T>(-1);
}

template <std::size_t N, typename T, bool PrecomputeNorm>
bool Vector<N, T, PrecomputeNorm>::operator==(
    const Vector<N, T, PrecomputeNorm> &other) const
{
    std::size_t i = 0;

    for (; i != N; i++) {
        if (other[i] != _data[i])
            break;
    }
    return i == N;
}

template <std::size_t N, typename T, bool PrecomputeNorm>
bool Vector<N, T, PrecomputeNorm>::operator!=(
    const Vector<N, T, PrecomputeNorm> &other) const
{
    return !(*this == other);
}

template <std::size_t N, typename T, bool PrecomputeNorm>
bool Vector<N, T, PrecomputeNorm>::operator<(
    const Vector<N, T, PrecomputeNorm> &other) const
{
    return getLength() < other.getLength();
}

template <std::size_t N, typename T, bool PrecomputeNorm>
bool Vector<N, T, PrecomputeNorm>::operator<=(
    const Vector<N, T, PrecomputeNorm> &other) const
{
    T normA = getLength();
    T normB = other.getLength();

    return normA < normB || normA == normB;
}

template <std::size_t N, typename T, bool PrecomputeNorm>
bool Vector<N, T, PrecomputeNorm>::operator>(
    const Vector<N, T, PrecomputeNorm> &other) const
{
    return getLength() > other.getLength();
}

template <std::size_t N, typename T, bool PrecomputeNorm>
bool Vector<N, T, PrecomputeNorm>::operator>=(
    const Vector<N, T, PrecomputeNorm> &other) const
{
    T normA = getLength();
    T normB = other.getLength();

    return normA > normB || normA == normB;
}

template <std::size_t N, typename T, bool PrecomputeNorm>
Vector<N, T, PrecomputeNorm>::iterator Vector<N, T,
    PrecomputeNorm>::begin() noexcept
{
    return _data.begin();
}

template <std::size_t N, typename T, bool PrecomputeNorm>
Vector<N, T, PrecomputeNorm>::const_iterator Vector<N, T,
    PrecomputeNorm>::begin() const noexcept
{
    return _data.begin();
}

template <std::size_t N, typename T, bool PrecomputeNorm>
Vector<N, T, PrecomputeNorm>::const_iterator Vector<N, T,
    PrecomputeNorm>::cbegin() const noexcept
{
    return _data.cbegin();
}

template <std::size_t N, typename T, bool PrecomputeNorm>
Vector<N, T, PrecomputeNorm>::iterator Vector<N, T,
    PrecomputeNorm>::end() noexcept
{
    return _data.end();
}

template <std::size_t N, typename T, bool PrecomputeNorm>
Vector<N, T, PrecomputeNorm>::const_iterator Vector<N, T,
    PrecomputeNorm>::end() const noexcept
{
    return _data.end();
}

template <std::size_t N, typename T, bool PrecomputeNorm>
Vector<N, T, PrecomputeNorm>::const_iterator Vector<N, T,
    PrecomputeNorm>::cend() const noexcept
{
    return _data.cend();
}

template <std::size_t N, typename T, bool PrecomputeNorm>
Vector<N + 1, T, PrecomputeNorm> IncreaseDimension(
    const Vector<N, T, PrecomputeNorm> &other)
{
    std::array<T, N + 1> array;
    for (size_t i = 0; i != N; i++) {
        array[i] = other[i];
    }
    array[N + 1] = 0;
    return Vector(array);
}

template <std::size_t N, typename T, bool PrecomputeNorm>
std::ostream &operator<<(std::ostream &o,
    const Vector<N, T, PrecomputeNorm> &vector)
{
    o << "Vector<" << N << "> {";
    for (const auto &value: vector)
        o << value << value == vector.cend() - 1 ? "" : ", ";
    o << "}";
    return o;
}

Vector<3> cross(Vector<3> a, Vector<3> b)
{
    std::array<double, 3> array;

    array[0] = a[1] * b[2] - a[2] * b[1];
    array[1] = a[2] * b[0] - a[0] * b[2];
    array[2] = a[0] * b[1] - a[1] * b[0];
    return Vector(array);
}
