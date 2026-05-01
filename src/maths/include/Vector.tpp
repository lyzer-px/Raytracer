/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** Vector class implementation
*/

#pragma once

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <stdexcept>
#include "Vector.hpp"

template <template<typename> class Derived, std::size_t N, typename T>
bool Vector<Derived, N, T>::hasNaN() const
{
    for (std::size_t i = 0; i < N; ++i) {
        if (std::isnan(_data[i]))
            return true;
    }
    return false;
}

template <template<typename> class Derived, std::size_t N, typename T>
const T &Vector<Derived, N, T>::x() const
{
    return _data.at(0);
}

template <template<typename> class Derived, std::size_t N, typename T>
T &Vector<Derived, N, T>::x()
{
    return _data.at(0);
}

template <template<typename> class Derived, std::size_t N, typename T>
const T &Vector<Derived, N, T>::y() const
{
    return _data.at(1);
}

template <template<typename> class Derived, std::size_t N, typename T>
T &Vector<Derived, N, T>::y()
{
    return _data.at(1);
}

template <template<typename> class Derived, std::size_t N, typename T>
const T &Vector<Derived, N, T>::z() const requires (N >= 3)

{
    return _data.at(2);
}

template <template<typename> class Derived, std::size_t N, typename T>
T &Vector<Derived, N, T>::z() requires (N >= 3)
{
    return _data.at(2);
}

template <template<typename> class Derived, std::size_t N, typename T>
Vector<Derived, N, T>::Vector(std::initializer_list<T> values)
{
    std::copy_n(values.begin(), std::min(values.size(), N), _data.begin());
}

template <template<typename> class Derived, std::size_t N, typename T>
Derived<T> Vector<Derived, N, T>::normalize() const
{
    T norm = length();

    if (norm == static_cast<T>(0))
        throw std::runtime_error("Division by 0");
    return (*this) / norm;
}

template <template<typename> class Derived, std::size_t N, typename T>
T Vector<Derived, N, T>::length() const
{
    T norm = static_cast<T>(0);

    for (std::size_t i = 0; i < N; ++i) {
        T value = _data[i];
        norm += value * value;
    }
    return static_cast<T>(std::sqrt(norm));
}

template <template<typename> class Derived, std::size_t N, typename T>
T Vector<Derived, N, T>::calculateAngle(const Derived<T> &other) const
{
    T lhsNorm = length();
    T rhsNorm = other.length();

    if (lhsNorm == static_cast<T>(0) || rhsNorm == static_cast<T>(0))
        throw std::runtime_error("In angle calculation: null norm");

    T cosine = ((*this) * other) / (lhsNorm * rhsNorm);
    cosine = std::clamp(cosine, static_cast<T>(-1), static_cast<T>(1));
    return static_cast<T>(std::acos(cosine));
}

template <template<typename> class Derived, std::size_t N, typename T>
Derived<T> Vector<Derived, N, T>::operator+(const Derived<T> &other) const
{
    Derived<T> out;

    for (std::size_t i = 0; i < N; ++i) {
        out._data[i] = _data[i] + other._data[i];
    }
    return out;
}

template <template<typename> class Derived, std::size_t N, typename T>
Derived<T> Vector<Derived, N, T>::operator-(const Derived<T> &other) const
{
    Derived<T> out;
    for (std::size_t i = 0; i < N; ++i) {
        out._data[i] = _data[i] - other._data[i];
    }
    return out;
}

template <template<typename> class Derived, std::size_t N, typename T>
T Vector<Derived, N, T>::operator*(const Derived<T> &other) const
{
    T pdct = static_cast<T>(0);

    for (std::size_t i = 0; i < N; ++i)
        pdct += _data[i] * other._data[i];
    return pdct;
}

template <template<typename> class Derived, std::size_t N, typename T>
T Vector<Derived, N, T>::dot(const Derived<T> &other) const
{
    return (*this) * other;
}

template <template<typename> class Derived, std::size_t N, typename T>
Derived<T> Vector<Derived, N, T>::operator*(T scalar) const
{
    Derived<T> out;

    for (std::size_t i = 0; i < N; ++i)
        out._data[i] = this->_data[i] * scalar;
    return out;
}

template <template<typename> class Derived, std::size_t N, typename T>
Derived<T> Vector<Derived, N, T>::operator/(T scalar) const
{
    if (scalar == static_cast<T>(0))
        throw std::runtime_error("Division by 0");
    return (*this) * (static_cast<T>(1) / scalar);
}

template <template<typename> class Derived, std::size_t N, typename T>
Derived<T> Vector<Derived, N, T>::operator-() const
{
    return (*this) * static_cast<T>(-1);
}

template <template<typename> class Derived, std::size_t N, typename T>
bool Vector<Derived, N, T>::operator==(const Derived<T> &other) const
{
    for (std::size_t i = 0; i < N; ++i) {
        if (this->_data[i] != other._data[i])
            return false;
    }
    return true;
}

template <template<typename> class Derived, std::size_t N, typename T>
bool Vector<Derived, N, T>::operator!=(const Derived<T> &other) const
{
    return !(*this == other);
}

template <template<typename> class Derived, std::size_t N, typename T>
bool Vector<Derived, N, T>::operator<(const Derived<T> &other) const
{
    return length() < other.length();
}

template <template<typename> class Derived, std::size_t N, typename T>
bool Vector<Derived, N, T>::operator<=(const Derived<T> &other) const
{
    T normA = length();
    T normB = other.length();

    return normA < normB || normA == normB;
}

template <template<typename> class Derived, std::size_t N, typename T>
bool Vector<Derived, N, T>::operator>(const Derived<T> &other) const
{
    return length() > other.length();
}

template <template<typename> class Derived, std::size_t N, typename T>
bool Vector<Derived, N, T>::operator>=(const Derived<T> &other) const
{
    T normA = length();
    T normB = other.length();

    return normA > normB || normA == normB;
}

template <typename T>
Vector3<T>::Vector3() : Vector<Vector3, 3, T>() {}

template <typename T>
Vector2<T>::Vector2() : Vector<Vector2, 2, T>() {}

template <typename T>
Vector3<T>::Vector3(T x, T y, T z) noexcept : Vector<Vector3, 3, T>() {

    this->_data[0] = x;
    this->_data[1] = y;
    this->_data[2] = z;
}

template <typename T>
Vector2<T>::Vector2(T x, T y) noexcept : Vector<Vector2, 2, T>() {

    this->_data[0] = x;
    this->_data[1] = y;
}

template <template<typename> class Derived, std::size_t N, typename T>
Derived<T> Vector<Derived, N, T>::cross(const Derived<T> &other) const
    requires (N == 3)
{
    Derived<T> result;
    result.x() = (this->y() * other.z()) - (this->z() * other.y());
    result.y() = (this->z() * other.x()) - (this->x() * other.z());
    result.z() = (this->x() * other.y()) - (this->y() * other.x());
    return result;
}

template <template<typename> class Derived, std::size_t N, typename T>
Derived<T> Vector<Derived, N, T>::cross(Derived<T> &other) const
    requires (N == 3)
{
    Derived<T> result;
    result.x() = (this->y() * other.z()) - (this->z() * other.y());
    result.y() = (this->z() * other.x()) - (this->x() * other.z());
    result.z() = (this->x() * other.y()) - (this->y() * other.x());
    return result;
}