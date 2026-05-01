/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** point class implementation
*/

#pragma once

#include <cmath>
#include <stdexcept>
#include "Point.hpp"
#include "Vector.hpp"

// Point2 Implementation
template <typename T>
Point2<T>::Point2() : Vector<Point2, 2, T>{} {}

template <typename T>
Point2<T>::Point2(T x, T y) : Vector<Point2, 2, T>({x, y}) {}

template <typename T>
template <typename U>
Point2<T>::Point2(const Vector2<U>& v) : Vector<Point2, 2, T>({static_cast<T>(v.x()), static_cast<T>(v.y())}) {}

template <typename T>
Point2<T> Point2<T>::operator+(const Vector2<T>& v) const
{
    return Point2<T>(this->x() + v.x(), this->y() + v.y());
}

template <typename T>
Point2<T> Point2<T>::operator-(const Vector2<T>& v) const
{
    return Point2<T>(this->x() - v.x(), this->y() - v.y());
}

template <typename T>
Point2<T>& Point2<T>::operator+=(const Vector2<T>& v)
{
    this->x() += v.x();
    this->y() += v.y();
    return *this;
}

template <typename T>
Point2<T>& Point2<T>::operator-=(const Vector2<T>& v)
{
    this->x() -= v.x();
    this->y() -= v.y();
    return *this;
}

template <typename T>
Vector2<T> Point2<T>::operator-(const Point2<T>& other) const
{
    Vector2<T> result;
    result.x() = this->x() - other.x();
    result.y() = this->y() - other.y();
    return result;
}

// Point3 Implementation
template <typename T>
Point3<T>::Point3() : Vector<Point3, 3, T>() {}

template <typename T>
Point3<T>::Point3(T x, T y, T z) : Vector<Point3, 3, T>({x, y, z}) {}

template <typename T>
template <typename U>
Point3<T>::Point3(const Vector3<U>& v) :
    Vector<Point3, 3, T>({static_cast<T>(v.x()), static_cast<T>(v.y()), static_cast<T>(v.z())}) {}

template <typename T>
Point3<T> Point3<T>::operator+(const Vector3<T>& v) const
{
    return Point3<T>(this->x() + v.x(), this->y() + v.y(), this->z() + v.z());
}

template <typename T>
Point3<T> Point3<T>::operator-(const Vector3<T>& v) const
{
    return Point3<T>(this->x() - v.x(), this->y() - v.y(), this->z() - v.z());
}

template <typename T>
Point3<T>& Point3<T>::operator+=(const Vector3<T>& v)
{
    this->x() += v.x();
    this->y() += v.y();
    this->z() += v.z();
    return *this;
}

template <typename T>
Point3<T>& Point3<T>::operator-=(const Vector3<T>& v)
{
    this->x() -= v.x();
    this->y() -= v.y();
    this->z() -= v.z();
    return *this;
}

template <typename T>
Vector3<T> Point3<T>::operator-(const Point3<T>& other) const
{
    Vector3<T> result;

    result.x() = this->x() - other.x();
    result.y() = this->y() - other.y();
    result.z() = this->z() - other.z();
    return result;
}

// Utility functions
template <typename T>
float distance(const Point3<T>& a, const Point3<T>& b)
{
    return (b - a).length();
}

template <typename T>
T distanceSquared(const Point3<T>& a, const Point3<T>& b)
{
    Vector3<T> diff = b - a;
    T length        = diff.length();
    return length * length;
}

template <typename T>
Point3<T> lerp(float t, const Point3<T>& a, const Point3<T>& b)
{
    Vector3<T> diff = (b - a);
    return a + (diff * static_cast<T>(t));
}

template <typename T>
Point3<T> min(const Point3<T>& a, const Point3<T>& b)
{
    return Point3<T>(
        a.x() < b.x() ? a.x() : b.x(),
        a.y() < b.y() ? a.y() : b.y(),
        a.z() < b.z() ? a.z() : b.z()
        );
}

template <typename T>
Point3<T> max(const Point3<T>& a, const Point3<T>& b)
{
    return Point3<T>(
        a.x() > b.x() ? a.x() : b.x(),
        a.y() > b.y() ? a.y() : b.y(),
        a.z() > b.z() ? a.z() : b.z()
        );
}

template <typename T>
Point3<T> abs(const Point3<T>& p)
{
    return Point3<T>(
        std::abs(p.x()),
        std::abs(p.y()),
        std::abs(p.z())
        );
}

template <typename T>
Point3<T> floor(const Point3<T>& p)
{
    return Point3<T>(
        std::floor(static_cast<double>(p.x())),
        std::floor(static_cast<double>(p.y())),
        std::floor(static_cast<double>(p.z()))
        );
}

template <typename T>
Point3<T> ceil(const Point3<T>& p)
{
    return Point3<T>(
        std::ceil(static_cast<double>(p.x())),
        std::ceil(static_cast<double>(p.y())),
        std::ceil(static_cast<double>(p.z()))
        );
}

template <typename T>
Point3<T> permute(const Point3<T>& p, int x, int y, int z)
{
    auto getComponent = [](const Point3<T>& point, int index) -> T {
        switch (index) {
        case 0: return point.x();
        case 1: return point.y();
        case 2: return point.z();
        default: throw std::out_of_range("Invalid permutation index");
        }
    };

    return Point3<T>(
        getComponent(p, x),
        getComponent(p, y),
        getComponent(p, z)
        );
}
