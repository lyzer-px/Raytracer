/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** Point class declaration
*/

#pragma once

#include <array>
#include <cstddef>

template<std::size_t N, typename T = double>
class Point {
public:
    using iterator = typename std::array<T, N>::iterator;
    using const_iterator = typename std::array<T, N>::const_iterator;

    Point() = default;
    explicit Point(std::array<T, N> data) noexcept;

    T& operator[](std::size_t i);
    const T& operator[](std::size_t i) const;

    bool operator==(const Point& other) const;
    bool operator!=(const Point& other) const;

    bool operator++();
    bool operator--();

    Vector<N, T> toVector() const;

    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    const_iterator cbegin() const noexcept;

    iterator end() noexcept;
    const_iterator end() const noexcept;
    const_iterator cend() const noexcept;

private:
    std::array<T, N> _data;
};

using Point2f = Point<2, float>;
using Point3f = Point<3, float>;

#include "Point.tpp"