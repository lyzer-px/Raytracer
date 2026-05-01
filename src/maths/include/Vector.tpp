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

namespace properties {

template <typename Derived>
struct VectorTraits;

template <typename T>
struct VectorTraits<Vector2<T>> {
    static constexpr std::size_t size = 2;

    static T get(const Vector2<T> &vector, std::size_t idx)
    {
        if (idx == 0)
            return vector.x;
        if (idx == 1)
            return vector.y;
        throw std::out_of_range("Vector2D index out of range");
    }

    static void set(Vector2<T> &vector, std::size_t idx, T value)
    {
        switch (idx) {
            case 0:
                vector.x = value;
                return;
            case 1:
                vector.y = value;
                return;
            default:
                throw std::out_of_range("Vector2D index out of range");
        }
    }
};

template <typename T>
struct VectorTraits<Vector3<T>> {
    static constexpr std::size_t size = 3;

    static T get(const Vector3<T> &vector, std::size_t idx)
    {
        switch (idx) {
            case 0:
                return vector.x;
            case 1:
                return vector.y;
            case 2:
                return vector.z;
            default:
                throw std::out_of_range("Vector3D index out of range");
        }
    }

    static void set(Vector3<T> &vector, std::size_t idx, T value)
    {
        switch (idx) {
            case 0:
                vector.x = value;
                return;
            case 1:
                vector.y = value;
                return;
            case 2:
                vector.z = value;
                return;
            default:
                throw std::out_of_range("Vector3D index out of range");
        }
    }
};
}

template <class Derived, typename T>
typename Vector<Derived, T>::UnitVector Vector<Derived, T>::normalize() const
{
    T norm = length();

    if (norm == static_cast<T>(0))
        throw std::runtime_error("Division by 0");
    return (*this) / norm;
}

template <class Derived, typename T>
T Vector<Derived, T>::length() const
{
    const auto &self = static_cast<const Derived &>(*this);
    T norm = static_cast<T>(0);

    for (std::size_t i = 0; i < properties::VectorTraits<Derived>::size; ++i) {
        T value = static_cast<T>(properties::VectorTraits<Derived>::get(self, i));
        norm += value * value;
    }
    return static_cast<T>(std::sqrt(norm));
}

template <class Derived, typename T>
T Vector<Derived, T>::calculateAngle(const Vector<Derived, T> &other) const
{
    T lhsNorm = length();
    T rhsNorm = other.length();

    if (lhsNorm == static_cast<T>(0) || rhsNorm == static_cast<T>(0))
        throw std::runtime_error("In angle calculation: null norm");

    T cosine = ((*this) * other) / (lhsNorm * rhsNorm);
    cosine = std::clamp(cosine, static_cast<T>(-1), static_cast<T>(1));
    return static_cast<T>(std::acos(cosine));
}

template <class Derived, typename T>
Derived Vector<Derived, T>::operator+(const Vector<Derived, T> &other) const
{
    const auto &lhs = static_cast<const Derived &>(*this);
    const auto &rhs = static_cast<const Derived &>(other);
    Derived out;

    for (std::size_t i = 0; i < properties::VectorTraits<Derived>::size; ++i) {
        properties::VectorTraits<Derived>::set(out, i,
            properties::VectorTraits<Derived>::get(lhs, i) +
            properties::VectorTraits<Derived>::get(rhs, i));
    }
    return out;
}

template <class Derived, typename T>
Derived Vector<Derived, T>::operator-(const Vector<Derived, T> &other) const
{
    const auto &lhs = static_cast<const Derived &>(*this);
    const auto &rhs = static_cast<const Derived &>(other);
    Derived out;

    for (std::size_t i = 0; i < properties::VectorTraits<Derived>::size; ++i) {
        properties::VectorTraits<Derived>::set(out, i,
            properties::VectorTraits<Derived>::get(lhs, i) -
            properties::VectorTraits<Derived>::get(rhs, i));
    }
    return out;
}

template <class Derived, typename T>
T Vector<Derived, T>::operator*(const Vector<Derived, T> &other) const
{
    const auto &lhs = static_cast<const Derived &>(*this);
    const auto &rhs = static_cast<const Derived &>(other);
    T sum = static_cast<T>(0);

    for (std::size_t i = 0; i < properties::VectorTraits<Derived>::size; ++i) {
        sum += static_cast<T>(
            properties::VectorTraits<Derived>::get(lhs, i) *
            properties::VectorTraits<Derived>::get(rhs, i));
    }

    return sum;
}

template <class Derived, typename T>
T Vector<Derived, T>::dot(const Vector<Derived, T> &other) const
{
    return (*this) * other;
}

template <class Derived, typename T>
Derived Vector<Derived, T>::operator*(T scalar) const
{
    const auto &self = static_cast<const Derived &>(*this);
    Derived out;

    for (std::size_t i = 0; i < properties::VectorTraits<Derived>::size; ++i) {
        properties::VectorTraits<Derived>::set(out, i,
            properties::VectorTraits<Derived>::get(self, i) * scalar);
    }
    return out;
}

template <class Derived, typename T>
Derived Vector<Derived, T>::operator/(T scalar) const
{
    if (scalar == static_cast<T>(0))
        throw std::runtime_error("Division by 0");
    return (*this) * (static_cast<T>(1) / scalar);
}

template <class Derived, typename T>
Derived Vector<Derived, T>::operator-() const
{
    return (*this) * static_cast<T>(-1);
}

template <class Derived, typename T = double>
bool Vector<Derived, T>::operator==(const Vector<Derived, T> &other) const
{
    const auto &lhs = static_cast<const Derived &>(*this);
    const auto &rhs = static_cast<const Derived &>(other);

    for (std::size_t i = 0; i < properties::VectorTraits<Derived>::size; ++i) {
        if (properties::VectorTraits<Derived>::get(lhs, i) !=
            properties::VectorTraits<Derived>::get(rhs, i)) {
            return false;
        }
    }
    return true;
}

template <class Derived, typename T = double>
bool Vector<Derived, T>::operator!=(const Vector<Derived, T> &other) const
{
    return !(*this == other);
}

template <class Derived, typename T = double>
bool Vector<Derived, T>::operator<(const Vector<Derived, T> &other) const
{
    return length() < other.length();
}

template <class Derived, typename T = double>
bool Vector<Derived, T>::operator<=(const Vector<Derived, T> &other) const
{
    T normA = length();
    T normB = other.length();

    return normA < normB || normA == normB;
}

template <class Derived, typename T = double>
bool Vector<Derived, T>::operator>(const Vector<Derived, T> &other) const
{
    return length() > other.length();
}

template <class Derived, typename T = double>
bool Vector<Derived, T>::operator>=(const Vector<Derived, T> &other) const
{
    T normA = length();
    T normB = other.length();

    return normA > normB || normA == normB;
}
