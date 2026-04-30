/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** point class implementation
*/

#pragma once

#include "Point.hpp"
#include "Vector.hpp"

template <std::size_t N, typename T>
Point<N, T>::Point()
{
    for (std::size_t i = 0; i < N; ++i)
        _data[i] = static_cast<T>(0);
}

template <std::size_t N, typename T>
Point<N, T>::Point(std::array<T, N> data) noexcept: _data(data)
{}

template <std::size_t N, typename T>
T &Point<N, T>::operator[](std::size_t idx)
{
    return _data[idx];
}

template <std::size_t N, typename T>
const T &Point<N, T>::operator[](std::size_t idx) const
{
    return _data[idx];
}

template <std::size_t N, typename T>
bool Point<N, T>::operator==(const Point &other) const
{
    auto otherIt = other.begin();

    for (const auto &value: _data) {
        if (value != *otherIt)
            return false;
        ++otherIt;
    }
    return true;
}

template <std::size_t N, typename T>
bool Point<N, T>::operator!=(const Point &other) const
{
    return !(*this == other);
}

template <std::size_t N, typename T>
bool Point<N, T>::operator++()
{
    for (auto &value: _data)
        ++value;
    return true;
}

template <std::size_t N, typename T>
bool Point<N, T>::operator--()
{
    for (auto &value: _data)
        --value;
    return true;
}

template <std::size_t N, typename T>
Vector<N, T> Point<N, T>::toVector() const
{
    std::array<T, N> array;
    auto outIt = array.begin();

    for (const auto &value: _data) {
        *outIt = value;
        ++outIt;
    }
    return Vector(array);
}

template <std::size_t N, typename T>
Point<N, T>::Iterator Point<N, T>::begin() noexcept
{
    return _data.begin();
}

template <std::size_t N, typename T>
Point<N, T>::ConstIterator Point<N, T>::begin() const noexcept
{
    return _data.begin();
}

template <std::size_t N, typename T>
Point<N, T>::ConstIterator Point<N, T>::cbegin() const noexcept
{
    return _data.cbegin();
}

template <std::size_t N, typename T>
Point<N, T>::Iterator Point<N, T>::end() noexcept
{
    return _data.end();
}

template <std::size_t N, typename T>
Point<N, T>::ConstIterator Point<N, T>::end() const noexcept
{
    return _data.end();
}

template <std::size_t N, typename T>
Point<N, T>::ConstIterator Point<N, T>::cend() const noexcept
{
    return _data.cend();
}

template <std::size_t N, typename T, bool PrecomputeNorm>
Vector<N, T, PrecomputeNorm> operator+(const Point<N, T> &lhs,
    const Vector<N, T, PrecomputeNorm> &rhs)
{
    Vector<N, T> res;
    for (std::size_t idx = 0; idx < N; ++idx)
        res[idx] += lhs[idx] + rhs[idx];

    return res;
}

// template<>
// const Point<3> Point<3>::rotate(double angle)
// {
//     return Transform::rotationMatrix3D(angle) * (*this);
// }
//
// template<>
// const Point<2> Point<2>::rotate2D(double angle)
// {
//     return Transform::rotationMatrix2D(angle) * (*this);
// }
//
//
//
// template<>
// const Point<3> Point<3>::translate(double translateX, double translateY)
// {
//     return Transform::translationMatrix3D(translateX, translateY) * (*this);
// }
//
// template<>
// const Point<3> Point<3>::scale(double scaleX, double scaleY)
// {
//     return Transform::scalingMatrix3D(scaleX, scaleY) * (*this);
// }
//
// template<>
// const Point<2> Point<2>::scale2D(double scaleX, double scaleY)
// {
//     return Transform::scalingMatrix2D(scaleX, scaleY) * (*this);
// }
//
//
//
// template<>
// const Point<3> Point<3>::shear(double shearX, double shearY)
// {
//     return Transform::shearingMatrix3D(shearX, shearY) * (*this);
// }
//
// template<>
// const Point<2> Point<2>::shear2D(double shearX, double shearY)
// {
//     return Transform::shearingMatrix2D(shearX, shearY) * (*this);
// }
//
//
// template<>
// const Point<3> Point<3>::reflect(bool reflectX, bool reflectY)
// {
//     return Transform::reflectionMatrix3D(reflectX, reflectY) * (*this);
// }
//
// template<>
// const Point<2> Point<2>::reflect2D(bool reflectX, bool reflectY)
// {
//     return Transform::reflectionMatrix2D(reflectX, reflectY) * (*this);
// }
