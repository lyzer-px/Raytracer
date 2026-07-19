/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** Bounds2.hpp
*/

#pragma once

#include <array>

#include "Point.hpp"
#include "Ray.hpp"
#include "Vector.hpp"

namespace raytracer::maths {
template <typename T = double> class Bounds2 {
public:
    // Constructors
    Bounds2();
    explicit Bounds2(const Point2<T> &p1, const Point2<T> &p2);
    explicit Bounds2(const Point2<T> &p);

    const Point2<T> &operator[](int i) const;
    Point2<T> &operator[](int i);

    // All 8 corners of the box
    Point2<T> corner(int i) const; // i in [0, 3] -- bit mask: x=bit0, y=bit1

    // Geometric properties
    Vector2<T> diagonal() const; // pMax - pMin
    T surfaceArea() const;       // 2*(dx*dy) -- used by SAH
    T volume() const;            // dx * dy
    [[nodiscard]] int
        maxDimension() const; // index of the longest axis (0=x, 1=y)

    Point2<T> centroid() const; // (pMin + pMax) / 2 -- used by BVH build

    bool operator==(const Bounds2<T> &other) const;
    bool operator!=(const Bounds2<T> &other) const;

    // Fast ray-AABB intersection test
    // Returns true if ray hits the box in [tMin, tMax]
    // Updates tHitNear and tHitFar with the hit interval
    bool intersectP(const Ray &ray, T tMax, T *tHitNear, T *tHitFar) const;

    // Optimized version using precomputed ray reciprocals (used inside BVH
    // traversal)
    bool intersectP(const Ray &ray, const Vector2<T> &invDir,
        const std::array<int, 2> &dirIsNeg) const;
    Point2<T> pMin;
    Point2<T> pMax;

    // hello 
};
} // namespace raytracer::maths
using Bounds2f = raytracer::maths::Bounds2<double>;
using Bounds2i = raytracer::maths::Bounds2<int>;

#include "Bounds2.tpp"
