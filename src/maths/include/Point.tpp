/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** point class implementation
*/

#pragma once

#include "Point.hpp"
#include "Vector.hpp"
#include <cmath>

// Point2 Implementation
template <typename T>
Point2<T>::Point2() : x(static_cast<T>(0)), y(static_cast<T>(0)) {}

template <typename T>
Point2<T>::Point2(T x, T y) : x(x), y(y)
{
}

template <typename T>
template <typename U>
Point2<T>::Point2(const Vector2<U>& v) : x(static_cast<T>(v.x)), y(static_cast<T>(v.y))
{
}

template <typename T>
Point2<T> Point2<T>::operator+(const Vector2<T>& v) const
{
    return Point2<T>(x + v.x, y + v.y);
}

template <typename T>
Point2<T> Point2<T>::operator-(const Vector2<T>& v) const
{
    return Point2<T>(x - v.x, y - v.y);
}

template <typename T>
Point2<T>& Point2<T>::operator+=(const Vector2<T>& v)
{
    x += v.x;
    y += v.y;
    return *this;
}

template <typename T>
Point2<T>& Point2<T>::operator-=(const Vector2<T>& v)
{
    x -= v.x;
    y -= v.y;
    return *this;
}

template <typename T>
Point2<T> Point2<T>::operator-(const Vector2<T>& v) const
{
    return Point2<T>(x - v.x, y - v.y);
}

template <typename T>
Vector2<T> Point2<T>::operator-(const Point2<T>& other) const
{
    Vector2<T> result;
    result.x = x - other.x;
    result.y = y - other.y;
    return result;
}

// Point3 Implementation
template <typename T>
Point3<T>::Point3() : x(static_cast<T>(0)), y(static_cast<T>(0)), z(static_cast<T>(0))
{
}

template <typename T>
Point3<T>::Point3(T x, T y, T z) : x(x), y(y), z(z) {}

template <typename T>
template <typename U>
Point3<T>::Point3(const Vector3<U>& v) : x(static_cast<T>(v.x)), y(static_cast<T>(v.y)), z(static_cast<T>(v.z)) {}

template <typename T>
Point3<T> Point3<T>::operator+(const Vector3<T>& v) const
{
    return Point3<T>(x + v.x, y + v.y, z + v.z);
}

template <typename T>
Point3<T>& Point3<T>::operator+=(const Vector3<T>& v)
{
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

template <typename T>
Point3<T> Point3<T>::operator-(const Vector3<T>& v) const
{
    return Point3<T>(x - v.x, y - v.y, z - v.z);
}

template <typename T>
Vector3<T> Point3<T>::operator-(const Point3<T>& other) const
{
    return Vector3<T>(x - other.x, y - other.y, z - other.z);
}

// Utility functions
template <typename T>
float Distance(const Point3<T>& a, const Point3<T>& b)
{
    return (b - a).length();
}

template <typename T>
T DistanceSquared(const Point3<T>& a, const Point3<T>& b)
{
    Vector3<T> diff = b - a;
    return diff.dot(diff);
}

template <typename T>
Point3<T> Lerp(float t, const Point3<T>& a, const Point3<T>& b)
{
    Vector3<T> diff = b - a;
    return a + (diff * static_cast<T>(t));
}

template <typename T>
Point3<T> Min(const Point3<T>& a, const Point3<T>& b)
{
    return Point3<T>(
        a.x < b.x ? a.x : b.x,
        a.y < b.y ? a.y : b.y,
        a.z < b.z ? a.z : b.z
    );
}

template <typename T>
Point3<T> Max(const Point3<T>& a, const Point3<T>& b)
{
    return Point3<T>(
        a.x > b.x ? a.x : b.x,
        a.y > b.y ? a.y : b.y,
        a.z > b.z ? a.z : b.z
    );
}

template <typename T>
Point3<T> Abs(const Point3<T>& p)
{
    return Point3<T>(
        std::abs(p.x),
        std::abs(p.y),
        std::abs(p.z)
    );
}

template <typename T>
Point3<T> Floor(const Point3<T>& p)
{
    return Point3<T>(
        std::floor(static_cast<double>(p.x)),
        std::floor(static_cast<double>(p.y)),
        std::floor(static_cast<double>(p.z))
    );
}

template <typename T>
Point3<T> Ceil(const Point3<T>& p)
{
    return Point3<T>(
        std::ceil(static_cast<double>(p.x)),
        std::ceil(static_cast<double>(p.y)),
        std::ceil(static_cast<double>(p.z))
    );
}

template <typename T>
Point3<T> Permute(const Point3<T>& p, int x, int y, int z)
{
    auto getComponent = [](const Point3<T>& point, int index) -> T {
        switch (index) {
            case 0: return point.x;
            case 1: return point.y;
            case 2: return point.z;
            default: throw std::out_of_range("Invalid permutation index");
        }
    };

    return Point3<T>(
        getComponent(p, x),
        getComponent(p, y),
        getComponent(p, z)
    );
}