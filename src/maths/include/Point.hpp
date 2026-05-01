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

template <typename T = double>
class Point2 : public Vector<Point2<T>, T> {
public:
    Point2();
    Point2(T x, T y);

    template <typename U>
    explicit Point2(const Vector2<U>& v);  // explicit: Vector -> Point

    Point2<T>  operator+(const Vector2<T>& v) const;
    Point2<T>  operator-(const Vector2<T>& v) const;
    Point2<T>& operator+=(const Vector2<T>& v);
    Point2<T>& operator-=(const Vector2<T>& v);

    // Point - Point = Vector  (displacement between two positions)
    Vector2<T> operator-(const Point2<T>& other) const;

    T x = 0.0;
    T y = 0.0;

private:
    Point2 operator+(const Vector<Point2<T>, T>& other) const = delete;
    Point2 operator*(T scalar) const = delete;
    Point2 operator/(T scalar) const = delete;
    T operator*(const Vector<Point2<T>, T>& other) const = delete;
    T dot(const Vector<Point2<T>, T>& other) const = delete;
    typename Vector<Point2<T>, T>::UnitVector normalize() const = delete;
    T length() const = delete;
    T calculateAngle(const Vector<Point2<T>, T>& other) const = delete;

};

template <typename T = double>
class Point3 : public Vector<Point3<T>, T> {
public:
    Point3();
    Point3(T x, T y, T z);

    template<typename U>
    explicit Point3(const Vector3<U>& v);

    Point3<T>  operator+(const Vector3<T>& v) const;
    Point3<T>& operator+=(const Vector3<T>& v);

    Point3<T>  operator-(const Vector3<T>& v) const;

    Vector3<T> operator-(const Point3<T>& other) const;

    T x = 0.0;
    T y = 0.0;
    T z = 0.0;

private:
    Point3 operator+(const Vector<Point3<T>, T>& other) const = delete;
    Point3 operator*(T scalar) const = delete;
    Point3 operator/(T scalar) const = delete;
    T operator*(const Vector<Point3<T>, T>& other) const = delete;
    T dot(const Vector<Point3<T>, T>& other) const = delete;
    typename Vector<Point3<T>, T>::UnitVector normalize() const = delete;
    T length() const = delete;
    T calculateAngle(const Vector<Point3<T>, T>& other) const = delete;

};

using Point2f = Point2<float>;
using Point2i = Point2<int>;
using Point3f = Point3<float>;

using Point2d = Point2<double>;
using Point3d = Point3<double>;


template <typename T> float     Distance(const Point3<T>& a, const Point3<T>& b);        // Length(b - a)
template <typename T> T         DistanceSquared(const Point3<T>& a, const Point3<T>& b); // LengthSquared(b - a)
template <typename T> Point3<T> Lerp(float t, const Point3<T>& a, const Point3<T>& b);
template <typename T> Point3<T> Min(const Point3<T>& a, const Point3<T>& b);             // component-wise, used for AABB
template <typename T> Point3<T> Max(const Point3<T>& a, const Point3<T>& b);
template <typename T> Point3<T> Abs(const Point3<T>& p);
template <typename T> Point3<T> Floor(const Point3<T>& p);
template <typename T> Point3<T> Ceil(const Point3<T>& p);
template <typename T> Point3<T> Permute(const Point3<T>& p, int x, int y, int z);

#include "Point.tpp"
