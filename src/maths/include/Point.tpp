/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** point class implementation
*/

#include "Point.hpp"
#include "Vector.hpp"
#include "Transform.hpp"

template<std::size_t N, typename T>
Point<N, T>::Point(std::array<T, N> data) noexcept : _data(data) {}

template<std::size_t N, typename T>
typename Point<N, T>::iterator Point<N, T>::begin() noexcept
{
    return _data.begin();
}

template<std::size_t N, typename T>
typename Point<N, T>::const_iterator Point<N, T>::begin() const noexcept
{
    return _data.begin();
}

template<std::size_t N, typename T>
typename Point<N, T>::const_iterator Point<N, T>::cbegin() const noexcept
{
    return _data.cbegin();
}

template<std::size_t N, typename T>
typename Point<N, T>::iterator Point<N, T>::end() noexcept
{
    return _data.end();
}

template<std::size_t N, typename T>
typename Point<N, T>::const_iterator Point<N, T>::end() const noexcept
{
    return _data.end();
}

template<std::size_t N, typename T>
typename Point<N, T>::const_iterator Point<N, T>::cend() const noexcept
{
    return _data.cend();
}

template<std::size_t N, typename T>
T& Point<N, T>::operator[](std::size_t i)
{
    return _data[i];
}

template<std::size_t N, typename T>
const T& Point<N, T>::operator[](std::size_t i) const
{
    return _data[i];
}

template<std::size_t N, typename T>
bool Point<N, T>::operator==(const Point& other) const
{
    auto otherIt = other.begin();

    for (const auto &value : _data) {
        if (value != *otherIt)
            return false;
        ++otherIt;
    }
    return true;
}

template<std::size_t N, typename T>
bool Point<N, T>::operator!=(const Point& other) const
{
    return !(*this == other);
}

template<std::size_t N, typename T>
bool Point<N, T>::operator++()
{
    for (auto &value : _data)
        ++value;
    return true;
}

template<std::size_t N, typename T>
bool Point<N, T>::operator--()
{
    for (auto &value : _data)
        --value;
    return true;
}

template<std::size_t N, typename T>
Vector<N, T> Point<N, T>::toVector() const
{
    std::array<T, N> array;
    auto outIt = array.begin();

    for (const auto &value : _data) {
        *outIt = value;
        ++outIt;
    }
    return Vector(array);
}

template<>
const Point<3> Point<3>::rotate(double angle)
{
    return Transform::rotationMatrix3D(angle) * (*this);
}

template<>
const Point<2> Point<2>::rotate2D(double angle)
{
    return Transform::rotationMatrix2D(angle) * (*this);
}



template<>
const Point<3> Point<3>::translate(double translateX, double translateY)
{
    return Transform::translationMatrix3D(translateX, translateY) * (*this);
}

template<>
const Point<2> Point<2>::translate2D(double translateX, double translateY)
{
    return Transform::translationMatrix2D(translateX, translateY) * (*this);
}



template<>
const Point<3> Point<3>::scale(double scaleX, double scaleY)
{
    return Transform::scalingMatrix3D(scaleX, scaleY) * (*this);
}

template<>
const Point<2> Point<2>::scale2D(double scaleX, double scaleY)
{
    return Transform::scalingMatrix2D(scaleX, scaleY) * (*this);
}



template<>
const Point<3> Point<3>::shear(double shearX, double shearY)
{
    return Transform::shearingMatrix3D(shearX, shearY) * (*this);
}

template<>
const Point<2> Point<2>::shear2D(double shearX, double shearY)
{
    return Transform::shearingMatrix2D(shearX, shearY) * (*this);
}


template<>
const Point<3> Point<3>::reflect(bool reflectX, bool reflectY)
{
    return Transform::reflectionMatrix3D(reflectX, reflectY) * (*this);
}

template<>
const Point<2> Point<2>::reflect2D(bool reflectX, bool reflectY)
{
    return Transform::reflectionMatrix2D(reflectX, reflectY) * (*this);
}

