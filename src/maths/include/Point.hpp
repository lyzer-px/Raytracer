/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** Point class declaration
*/

#pragma once

#include <array>
#include <cmath>
#include <cstddef>
#include <stdexcept>

namespace raytracer::maths {

template <template <typename> class Derived, std::size_t N, typename T>
class Vector;

template <typename T> class Vector3;

template <typename T> class Vector2;

template <typename T = double> class Point2: public Vector<Point2, 2, T> {
public:
    Point2();
    Point2(T x, T y);

    template <typename U>
    explicit Point2(const Vector2<U> &v); // explicit: Vector -> Point

    Point2<T> operator+(const Vector2<T> &v) const;
    Point2<T> operator-(const Vector2<T> &v) const;
    Point2<T> &operator+=(const Vector2<T> &v);
    Point2<T> &operator-=(const Vector2<T> &v);

    // Point - Point = Vector (displacement between two positions)
    Vector2<T> operator-(const Point2<T> &other) const;

    Point2 operator+(const Point2 &other) const = delete;
    Point2 operator*(T scalar) const            = delete;
    Point2 operator/(T scalar) const            = delete;
    T operator*(const Point2 &other) const      = delete;
    T dot(const Point2 &other) const            = delete;
    Point2 normalize() const                    = delete;
    T length() const                            = delete;
    T calculateAngle(const Point2 &other) const = delete;
};

template <typename T = double> class Point3: public Vector<Point3, 3, T> {
public:
    Point3();
    Point3(T x, T y, T z);

    template <typename U>
    explicit Point3(const Vector3<U> &v); // explicit: Vector -> Point

    Point3<T> operator+(const Vector3<T> &v) const;
    Point3<T> operator-(const Vector3<T> &v) const;
    Point3<T> &operator+=(const Vector3<T> &v);
    Point3<T> &operator-=(const Vector3<T> &v);

    // Point - Point = Vector (displacement between two positions)
    Vector3<T> operator-(const Point3<T> &other) const;

    Point3 operator+(const Point3 &other) const;
    Point3 operator*(T scalar) const            = delete;
    Point3 operator/(T scalar) const            = delete;
    T operator*(const Point3 &other) const      = delete;
    T dot(const Point3 &other) const            = delete;
    Point3 normalize() const                    = delete;
    T length() const                            = delete;
    T calculateAngle(const Point3 &other) const = delete;
};

using Point2f = Point2<float>;
using Point2i = Point2<int>;
using Point3f = Point3<float>;

using Point2d = Point2<double>;
using Point3d = Point3<double>;

template <typename T>
float distance(const Point3<T> &a, const Point3<T> &b); // Length(b - a)
template <typename T>
T distanceSquared(
    const Point3<T> &a, const Point3<T> &b); // LengthSquared(b - a)
template <typename T>
Point3<T> lerp(float t, const Point3<T> &a, const Point3<T> &b);
template <typename T>
Point3<T> min(
    const Point3<T> &a, const Point3<T> &b); // component-wise, used for AABB
template <typename T> Point3<T> max(const Point3<T> &a, const Point3<T> &b);
template <typename T> Point3<T> abs(const Point3<T> &p);
template <typename T> Point3<T> floor(const Point3<T> &p);
template <typename T> Point3<T> ceil(const Point3<T> &p);
template <typename T>
Point3<T> permute(const Point3<T> &p, int x, int y, int z);

} // namespace raytracer::maths

#include "Point.tpp"
