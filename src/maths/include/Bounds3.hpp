/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** Bounds.hpp
*/

#pragma once

#include <array>

#include "Point.hpp"
#include "Ray.hpp"

namespace raytracer::maths {

template <typename T = double> class Bounds3 {
public:
    // Constructors
    Bounds3();
    explicit Bounds3(const Point3<T> &p1, const Point3<T> &p2);
    explicit Bounds3(const Point3<T> &p);

    Bounds3<T> boundsUnion(const Point3<T> &other) const;  // union of two boxes
    Bounds3<T> boundsUnion(const Bounds3<T> &other) const; // union of two boxes

    const Point3<T> &operator[](int i) const;
    Point3<T> &operator[](int i);

    // All 8 corners of the box
    Point3<T> corner(
        int i) const; // i in [0, 7] -- bit mask: x=bit0, y=bit1, z=bit2

    // Geometric properties
    Vector3<T> diagonal() const; // pMax - pMin
    T surfaceArea() const;       // 2*(dx*dy + dx*dz + dy*dz) -- used by SAH
    T volume() const;            // dx * dy * dz
    [[nodiscard]] int
        maxDimension() const; // index of the longest axis (0=x, 1=y, 2=z)

    Point3<T> centroid() const; // (pMin + pMax) / 2 -- used by BVH build

    bool operator==(const Bounds3<T> &other) const;
    bool operator!=(const Bounds3<T> &other) const;

    // Fast ray-AABB intersection test
    // Returns true if ray hits the box in [tMin, tMax]
    // Updates tHitNear and tHitFar with the hit interval
    bool intersectP(const Ray &ray, T tMax, T *tHitNear, T *tHitFar) const;

    // Optimized version using precomputed ray reciprocals (used inside BVH
    // traversal)
    bool intersectP(const Ray &ray, const Vector3<T> &invDir,
        const std::array<int, 3> &dirIsNeg) const;
    Point3<T> pMin;
    Point3<T> pMax;
};
} // namespace raytracer::maths
// Common aliases
using Bounds3d = raytracer::maths::Bounds3<double>;
using Bounds3i = raytracer::maths::Bounds3<int>;

#include "Bounds3.tpp"
