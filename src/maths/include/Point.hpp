/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** Point class declaration
*/

#pragma once

#include <array>
#include <cstddef>
#include "Vector.hpp"

template <std::size_t N, typename T = double>
class Point {
public:
    using Iterator      = std::array<T, N>::iterator;
    using ConstIterator = std::array<T, N>::const_iterator;

    Point();

    explicit Point(std::array<T, N> data) noexcept;

    T &operator[](std::size_t idx);

    const T &operator[](std::size_t idx) const;

    bool operator==(const Point &other) const;

    bool operator!=(const Point &other) const;

    bool operator++();

    bool operator--();

    Vector<N, T, false> toVector() const;

    Iterator begin() noexcept;

    ConstIterator begin() const noexcept;

    ConstIterator cbegin() const noexcept;

    Iterator end() noexcept;

    ConstIterator end() const noexcept;

    ConstIterator cend() const noexcept;

    // const Point rotate(double angle);
    // const Point rotate2D(double angle);
    //
    // const Point translate(double translateX, double translateY);
    // const Point translate2D(double translateX, double translateY);
    //
    // const Point scale(double scaleX, double scaleY);
    // const Point scale2D(double scaleX, double scaleY);
    //
    // const Point shear(double shearX, double shearY);
    // const Point shear2D(double shearX, double shearY);
    //
    // const Point reflect(bool reflectX, bool reflectY);
    // const Point reflect2D(bool reflectX, bool reflectY);

private:
    std::array<T, N> _data;
};

template <std::size_t N, typename T, bool PrecomputeNorm>
Vector<N, T, PrecomputeNorm> operator+(const Point<N, T> &lhs,
    const Vector<N, T, PrecomputeNorm> &rhs);

using Point2f = Point<2, float>;
using Point3f = Point<3, float>;
using Point2d = Point<2>;
using Point3d = Point<3>;

#include "Point.tpp"
