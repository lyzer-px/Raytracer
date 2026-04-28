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

template <std::size_t N, typename T = double, bool PrecomputeNorm = false>
class Vector {
public:
    using iterator       = typename std::array<T, N>::iterator;
    using const_iterator = typename std::array<T, N>::const_iterator;

    Vector();

    explicit Vector(std::array<T, N> &values);

    explicit Vector(std::array<T, N> &&values);

    using UnitVector = Vector;

    [[nodiscard]] UnitVector normalize() const;

    [[nodiscard]] T getLength() const;

    T length() const;

    void loadLength();

    [[nodiscard]] T calculateAngle(const Vector<N> &other) const;

    T &operator[](std::size_t idx);

    const T &operator[](std::size_t idx) const;

    Vector operator+(const Vector &other) const;

    Vector operator-(const Vector &other) const;

    // dot product
    T operator*(const Vector &other) const;
    [[nodiscard]] T dot(const Vector &other) const;

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

private:
    std::array<T, N> _data;
    T _norm;
};

template <std::size_t N, typename T, bool PrecomputeNorm>
using UnitVector = Vector<N, T, PrecomputeNorm>;

using Vector2f    = Vector<2, float>;
using Vector3f    = Vector<3, float>;
using UnitVector2 = Vector<2>;
using UnitVector3 = Vector<3>;

template <typename T>
Vector<3> cross(Vector<3> a, Vector<3> b);

template <std::size_t N, typename T, bool PrecomputeNorm>
Vector<N + 1, T, PrecomputeNorm> IncreaseDimension(
    const Vector<N, T, PrecomputeNorm> &a);

template <std::size_t N, typename T, bool PrecomputeNorm>
std::ostream &operator<<(std::ostream &o,
    const Vector<N, T, PrecomputeNorm> &vector);

template <std::size_t N, typename T, bool PrecomputeNorm>
bool operator==(const Vector<N, T, PrecomputeNorm> &lhs,
    const Vector<N, T, PrecomputeNorm> &rhs)
{
    return lhs.operator==(rhs);
}

template <std::size_t N, typename T, bool PrecomputeNorm>
bool operator!=(const Vector<N, T, PrecomputeNorm> &lhs,
    const Vector<N, T, PrecomputeNorm> &rhs)
{
    return lhs.operator!=(rhs);
}

template <std::size_t N, typename T, bool PrecomputeNorm>
bool operator<(const Vector<N, T, PrecomputeNorm> &lhs,
    const Vector<N, T, PrecomputeNorm> &rhs)
{
    return lhs.operator<(rhs);
}

template <std::size_t N, typename T, bool PrecomputeNorm>
bool operator>(const Vector<N, T, PrecomputeNorm> &lhs,
    const Vector<N, T, PrecomputeNorm> &rhs)
{
    return lhs.operator>(rhs);
}

template <std::size_t N, typename T, bool PrecomputeNorm>
bool operator<=(const Vector<N, T, PrecomputeNorm> &lhs,
    const Vector<N, T, PrecomputeNorm> &rhs)
{
    return lhs.operator<=(rhs);
}

template <std::size_t N, typename T, bool PrecomputeNorm>
bool operator>=(const Vector<N, T, PrecomputeNorm> &lhs,
    const Vector<N, T, PrecomputeNorm> &rhs)
{
    return lhs.operator>=(rhs);
}

#include "Vector.tpp"
